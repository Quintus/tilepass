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
  m_draw_area.signal_draw().connect(sigc::mem_fun(*this, &TilesetImage::on_area_draw));
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

  mp_pixbuf = Gdk::Pixbuf::create_from_file(filename);
  m_draw_area.set_size_request(mp_pixbuf->get_width(), mp_pixbuf->get_height());
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
