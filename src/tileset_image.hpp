#ifndef TILEPASS_TILESET_IMAGE_HPP
#define TILEPASS_TILESET_IMAGE_HPP
#include "main.hpp"

class TilesetImage: public Gtk::ScrolledWindow
{
public:
  TilesetImage();
  virtual ~TilesetImage();

  /// Load the given tileset file into the widget. `tileedge` is
  /// the length of the tile's edges (it must be quadratic).
  void load_tileset(Glib::ustring filename, int tileedge);
  /// Returns the path to the image file
  Glib::ustring get_filename();
  /// Returns the Gdk::Pixbuf created from the image file.
  Glib::RefPtr<Gdk::Pixbuf> get_pixbuf();

  // Advance the current tile as requested and return the Pixbuf
  // for that tile.
  Glib::RefPtr<Gdk::Pixbuf> prev_tile();
  Glib::RefPtr<Gdk::Pixbuf> next_tile();
  Glib::RefPtr<Gdk::Pixbuf> get_current_tile();

  // Number of tiles in a column of the current tileset.
  int rows();
  // Number of tiles in a row of the current tileset.
  int columns();
  // Number of all tiles of the current tileset.
  int tiles_count();
  // The number of the current tile, 0-based.
  int get_current_tilenum();

protected:
  virtual bool on_area_draw(const Cairo::RefPtr<Cairo::Context>& cc);

  void create_layout();
  void setup_event_handlers();

  Gtk::DrawingArea m_draw_area;
  Glib::ustring m_filename;
  Glib::RefPtr<Gdk::Pixbuf> mp_pixbuf;

  // Length of the tile edge in pixels
  int m_tileedge;
  // Current (X|Y) coordinate of the tile we are working with,
  // **in tiles** and 0-based, starting at the top-left. Multiply
  // with m_tileedge to retrieve the pixel position.
  int m_current_x;
  int m_current_y;
};

#endif
