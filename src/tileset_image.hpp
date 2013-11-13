#ifndef TILEPASS_TILESET_IMAGE_HPP
#define TILEPASS_TILESET_IMAGE_HPP
#include "main.hpp"

class TilesetImage: public Gtk::ScrolledWindow
{
public:
  TilesetImage();
  virtual ~TilesetImage();

  void set_filename(Glib::ustring filename);
  Glib::ustring get_filename();
  Glib::RefPtr<Gdk::Pixbuf> get_pixbuf();

protected:
  virtual bool on_area_draw(const Cairo::RefPtr<Cairo::Context>& cc);

  Gtk::DrawingArea* mp_draw_area;
  Glib::ustring m_filename;
  Glib::RefPtr<Gdk::Pixbuf> mp_pixbuf;
};

#endif
