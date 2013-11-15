#ifndef TILEPASS_ARROW_TILE_HPP
#define TILEPASS_ARROW_TILE_HPP
#include "main.hpp"

class ArrowTile: public Gtk::DrawingArea
{
public:
  ArrowTile();
  virtual ~ArrowTile();

  /// Change the current tile, resetting the arrow information to 0
  /// (no arrows are active).
  void set_tile(Glib::RefPtr<Gdk::Pixbuf> p_pixbuf);
  /// Change the current tile, resetting the arrow information to the
  /// given bit-OR’ed value of the ArrowDirection enum.
  void set_tile_with_directions(Glib::RefPtr<Gdk::Pixbuf> p_pixbuf, uint16_t directions);

  // Return the current tile.
  Glib::RefPtr<Gdk::Pixbuf> get_tile();

  // Show or hide one of the arrows. `direction' can be taken
  // from the ArrowDirection enum.
  void show_arrow(uint16_t direction);
  void hide_arrow(uint16_t direction);
  void toggle_arrow(uint16_t direction);
  // Check whether an arrow of the given direction is active.
  bool is_active(uint16_t direction);
  // Returns the entire direction mask; a bit-OR’ed combination
  // of the values in the ArrowDirection enum.
  uint16_t get_directions();

protected:
  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cc);
  virtual bool on_button_released(GdkEventButton* p_event);

private:
  void setup_signal_handlers();

  Glib::RefPtr<Gdk::Pixbuf> mp_tile;
  Glib::RefPtr<Gdk::Pixbuf> mp_uparrow;
  Glib::RefPtr<Gdk::Pixbuf> mp_downarrow;
  Glib::RefPtr<Gdk::Pixbuf> mp_rightarrow;
  Glib::RefPtr<Gdk::Pixbuf> mp_leftarrow;

  // Bit-OR’ed value of the ArrowDirection enum describing
  // which arrows to show.
  uint16_t m_show_directions;
};

#endif
