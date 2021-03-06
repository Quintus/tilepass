#ifndef TILEPASS_TILESET_IMAGE_HPP
#define TILEPASS_TILESET_IMAGE_HPP
#include "main.hpp"

class TilesetImage: public Gtk::ScrolledWindow
{
public:
  TilesetImage();
  virtual ~TilesetImage();

  /// Selection signal, containing the index in the
  /// directions vector from *before* the switch.
  typedef sigc::signal<void, int> type_signal_selected;

  /// Load the given tileset file into the widget. `tileedge` is
  /// the length of the tile's edges (it must be quadratic).
  void load_tileset(Glib::ustring filename, int tileedge);
  /// Linke load_tileset(), but also loads direction specifications
  /// from the given CSV file, which is produced by store_directions().
  void load_tileset_with_directions(Glib::ustring tileset_filename, Glib::ustring csv_filename, int tileedge);
  /// Store the defined directions in the given file as CSV. It can be re-loaded
  /// with load_tileset_with_directions().
  void store_directions(Glib::ustring filename);
  /// Returns the path to the image file
  Glib::ustring get_filename();
  /// Returns the Gdk::Pixbuf created from the image file.
  Glib::RefPtr<Gdk::Pixbuf> get_pixbuf();
  /// Unload the tileset image and clear all direction definitions.
  void clear();

  // Advance the current tile as requested and return the Pixbuf
  // for that tile.
  Glib::RefPtr<Gdk::Pixbuf> prev_tile();
  Glib::RefPtr<Gdk::Pixbuf> next_tile();
  Glib::RefPtr<Gdk::Pixbuf> get_current_tile();
  Glib::RefPtr<Gdk::Pixbuf> set_current_tile(int x, int y);

  // Number of tiles in a column of the current tileset.
  int rows();
  // Number of tiles in a row of the current tileset.
  int columns();
  // Number of all tiles of the current tileset.
  int tiles_count();
  // The number of the current tile, 0-based.
  int get_current_tilenum();

  // Get/Set the direction of the current tile. See the ArrowDirection
  // enum for possible values -- you may bit-OR or bit-AND them.
  uint16_t get_current_directions();
  void set_current_directions(uint16_t dir);

  /**
   * Get the list of all direction specifications. Each entry correspods
   * to one field on the tileset, starting with 0 at the upper-left corner,
   * ignoring row ends (the index just gets incremented further).
   * The ArrowDirection enum can be used to retrieve actual directions from
   * the values by means of bitwise AND.
   */
  std::vector<uint16_t> get_directions();
  /// Set the direction of the tile with the given index.
  void set_directions(int index, uint16_t directions);

  /// Signal emitted when a specific tile is selected
  /// by the user.
  type_signal_selected signal_selected();

protected:
  virtual bool on_area_draw(const Cairo::RefPtr<Cairo::Context>& cc);
  virtual bool on_area_button_released(GdkEventButton* p_event);

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

  std::vector<uint16_t> m_directions;

  type_signal_selected m_signal_selected;
};

#endif
