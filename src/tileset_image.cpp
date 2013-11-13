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
 * Getters & Setters
 ***************************************/

void TilesetImage::set_filename(Glib::ustring filename)
{
  m_filename = filename;
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

/***************************************
 * Signal handlers
 ***************************************/

bool TilesetImage::on_area_draw(const Cairo::RefPtr<Cairo::Context>& cc)
{
  if (!m_filename.empty()) {
    Gdk::Cairo::set_source_pixbuf(cc, mp_pixbuf, 0, 0);
    cc->paint();

    return true;
  }
  else
    return false;
}
