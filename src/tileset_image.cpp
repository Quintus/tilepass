#include "tileset_image.hpp"

/***************************************
 * Constructors & Destructors
 ***************************************/

TilesetImage::TilesetImage()
  : ScrolledWindow()
{
  // Always show the scrollbars to prevet changing the size of
  // the draw area on larger images
  set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);

  create_layout();
  setup_event_handlers();

  show_all_children();
}

TilesetImage::~TilesetImage()
{
  //
}

/***************************************
 * Helper methods
 ***************************************/

void TilesetImage::create_layout()
{
 add(m_draw_area);
}

void TilesetImage::setup_event_handlers()
{
  m_draw_area.add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);

  m_draw_area.signal_draw().connect(sigc::mem_fun(*this, &TilesetImage::on_area_draw));
  m_draw_area.signal_button_release_event().connect(sigc::mem_fun(*this, &TilesetImage::on_area_button_released));
}

/***************************************
 * Methods
 ***************************************/

void TilesetImage::load_tileset(Glib::ustring filename, int tileedge)
{
  m_filename  = filename;
  m_tileedge  = tileedge;
  m_current_x = 0;
  m_current_y = 0;
  mp_pixbuf   = Gdk::Pixbuf::create_from_file(filename);

  m_directions.assign(tiles_count(), 0);

  // Redraw the drawingarea with the new tileset
  m_draw_area.set_size_request(mp_pixbuf->get_width(), mp_pixbuf->get_height());
}

void TilesetImage::clear()
{
  m_filename  = "";
  m_tileedge  = 0;
  m_current_x = 0;
  m_current_y = 0;
  mp_pixbuf.reset();
  m_directions.clear();
  m_draw_area.set_size_request(0, 0);
}

void TilesetImage::load_tileset_with_directions(Glib::ustring tileset_filename, Glib::ustring csv_filename, int tileedge)
{
  m_filename  = tileset_filename;
  m_tileedge  = tileedge;
  m_current_x = 0;
  m_current_y = 0;
  mp_pixbuf   = Gdk::Pixbuf::create_from_file(tileset_filename);

  // Clear list of directions for now (we fill in later)
  m_directions.clear();

  // Read the directions from the CSV file line-by-line
  std::ifstream file(Glib::filename_from_utf8(csv_filename).c_str());
  while (!file.eof()) {
    std::string line;
    size_t lastpos = 0;
    size_t curpos = 0;

    // Grab one line
    std::getline(file, line);

    // Extract all directions from the current line
    while ((curpos = line.find(",", lastpos)) != std::string::npos) {
      std::string number = line.substr(lastpos, curpos - lastpos);

      // Convert our entry to integer and add it to the direction list.
      m_directions.push_back(atoi(number.c_str()));

      lastpos = curpos + 1;
    }
  }

  // Redraw the drawingarea with the new tileset
  m_draw_area.set_size_request(mp_pixbuf->get_width(), mp_pixbuf->get_height());
}

void TilesetImage::store_directions(Glib::ustring filename)
{
  std::ofstream file(Glib::filename_from_utf8(filename).c_str());

  if (!file)
    throw(std::runtime_error("Could not open CSV file."));

  std::vector<uint16_t>::const_iterator iter; // shorthand
  int ncolumns = columns(); // shorthand
  int i;
  for(iter=m_directions.begin(), i=0; iter != m_directions.end(); iter++, i++) {
    file << *iter;

    if(div(i + 1, ncolumns).rem == 0) // (i + 1) mod ncolumns == 0
      file << std::endl;
    else
      file << ",";
  }

  file.close();
}

Glib::ustring TilesetImage::get_filename()
{
  return m_filename;
}

Glib::RefPtr<Gdk::Pixbuf> TilesetImage::get_pixbuf()
{
  return mp_pixbuf;
}

Glib::RefPtr<Gdk::Pixbuf> TilesetImage::prev_tile()
{
  m_current_x -= 1;

  // If we go before the start of the row, return to the previous row
  if (m_current_x < 0) {
    m_current_x = columns() - 1;
    m_current_y -= 1;
  }

  // If we go before the first row, ignore.
  if (m_current_y < 0)
    m_current_y = 0;

  m_draw_area.queue_draw();
  return get_current_tile();
}

Glib::RefPtr<Gdk::Pixbuf> TilesetImage::next_tile()
{
  m_current_x += 1;

  // If we go past the end of a row, advance to the next row
  if (m_current_x >= columns()) {
    m_current_x = 0;
    m_current_y += 1;
  }

  // If we go past the last row, ignore.
  if (m_current_y >= rows())
    m_current_y -= 1;

  m_draw_area.queue_draw();
  return get_current_tile();
}

Glib::RefPtr<Gdk::Pixbuf> TilesetImage::set_current_tile(int x, int y)
{
  m_current_x = x;
  m_current_y = y;

  // Fix X values out of range
  if (m_current_x < 0)
    m_current_x = 0;
  else if (m_current_x >= columns())
    m_current_x = columns() - 1;

  // Fix Y values out of range
  if (m_current_y < 0)
    m_current_y = 0;
  else if (m_current_y >= rows())
    m_current_y = rows() - 1;

  m_draw_area.queue_draw();
  return get_current_tile();
}

Glib::RefPtr<Gdk::Pixbuf> TilesetImage::get_current_tile()
{
  return Gdk::Pixbuf::create_subpixbuf(mp_pixbuf,
                                       m_current_x * m_tileedge,
                                       m_current_y * m_tileedge,
                                       m_tileedge,
                                       m_tileedge);
}

int TilesetImage::rows()
{
  return mp_pixbuf->get_height() / m_tileedge;
}

int TilesetImage::columns()
{
  return mp_pixbuf->get_width() / m_tileedge;
}

int TilesetImage::tiles_count()
{
  return rows() * columns();
}

int TilesetImage::get_current_tilenum()
{
  return m_current_y * columns() + m_current_x; // All tiles of previous rows plus the number of tiles in the current row
}

uint16_t TilesetImage::get_current_directions()
{
  return m_directions[get_current_tilenum()];
}

void TilesetImage::set_current_directions(uint16_t dir)
{
  m_directions[get_current_tilenum()] = dir;
}

std::vector<uint16_t> TilesetImage::get_directions()
{
  return m_directions;
}

void TilesetImage::set_directions(int index, uint16_t directions)
{
  m_directions[index] = directions;
}

/***************************************
 * Signal handlers
 ***************************************/

bool TilesetImage::on_area_draw(const Cairo::RefPtr<Cairo::Context>& cc)
{
  if (!m_filename.empty()) {
    // Paint the tileset itself
    Gdk::Cairo::set_source_pixbuf(cc, mp_pixbuf, 0, 0);
    cc->paint();

    // Highlight the currently selected tile
    cc->set_source_rgb(0, 0, 0);
    cc->rectangle(m_current_x * m_tileedge, m_current_y * m_tileedge, m_tileedge, m_tileedge);
    cc->set_line_width(6);
    cc->stroke();
    cc->set_source_rgb(1, 1, 1);
    cc->rectangle(m_current_x * m_tileedge, m_current_y * m_tileedge, m_tileedge, m_tileedge);
    cc->set_line_width(4);
    cc->stroke();

    return true;
  }
  else
    return false;
}

TilesetImage::type_signal_selected TilesetImage::signal_selected()
{
  return m_signal_selected;
}

bool TilesetImage::on_area_button_released(GdkEventButton* p_event)
{
  int x = p_event->x / 32;
  int y = p_event->y / 32;
  int oldtilenum = get_current_tilenum();

  set_current_tile(x, y);

  m_signal_selected.emit(oldtilenum);
  return true;
}
