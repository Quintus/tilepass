#ifndef TILEPASS_TILESET_IMAGE_HPP
#define TILEPASS_TILESET_IMAGE_HPP
#include "main.hpp"

class TilesetImage: public Gtk::ScrolledWindow
{
public:
  TilesetImage();
  virtual ~TilesetImage();

  /// Load the given tileset file into the widget.
  void set_filename(Glib::ustring filename);
  /// Returns the path to the image file
  Glib::ustring get_filename();
  // Returns the Gdk::Pixbuf created from the image file.
  Glib::RefPtr<Gdk::Pixbuf> get_pixbuf();

protected:
  virtual bool on_area_draw(const Cairo::RefPtr<Cairo::Context>& cc);

  void create_layout();
  void setup_event_handlers();

  Gtk::DrawingArea m_draw_area;
  Glib::ustring m_filename;
  Glib::RefPtr<Gdk::Pixbuf> mp_pixbuf;
};

#endif
