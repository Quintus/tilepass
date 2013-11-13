#ifndef TILEPASS_ARROW_TILE_HPP
#define TILEPASS_ARROW_TILE_HPP
#include "main.hpp"

class ArrowTile: public Gtk::DrawingArea
{
public:
  ArrowTile();
  virtual ~ArrowTile();

  void set_tile(Glib::RefPtr<Gdk::Pixbuf> p_pixbuf);
  Glib::RefPtr<Gdk::Pixbuf> get_tile();

protected:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cc);

private:
  Glib::RefPtr<Gdk::Pixbuf> mp_tile;
  Glib::RefPtr<Gdk::Pixbuf> mp_uparrow;
  Glib::RefPtr<Gdk::Pixbuf> mp_downarrow;
  Glib::RefPtr<Gdk::Pixbuf> mp_rightarrow;
  Glib::RefPtr<Gdk::Pixbuf> mp_leftarrow;
};

#endif
