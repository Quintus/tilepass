#include "tileset_image.hpp"

TilesetImage::TilesetImage()
  : ScrolledWindow()
{
  mp_draw_area = new Gtk::DrawingArea();
  add(*mp_draw_area);

  set_policy(Gtk::POLICY_ALWAYS, Gtk::POLICY_ALWAYS);

  mp_draw_area->signal_draw().connect(sigc::mem_fun(*this, &TilesetImage::on_area_draw));
  show_all_children();
}

TilesetImage::~TilesetImage()
{
  delete mp_draw_area;
}

void TilesetImage::set_filename(Glib::ustring filename)
{
  m_filename = filename;
  mp_pixbuf = Gdk::Pixbuf::create_from_file(filename);
  mp_draw_area->set_size_request(mp_pixbuf->get_width(), mp_pixbuf->get_height());
}

Glib::ustring TilesetImage::get_filename()
{
  return m_filename;
}

Glib::RefPtr<Gdk::Pixbuf> TilesetImage::get_pixbuf()
{
  return mp_pixbuf;
}

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
