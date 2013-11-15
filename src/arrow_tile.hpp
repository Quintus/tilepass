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

  // Show or hide one of the arrows. `direction' can be taken
  // from the ArrowDirection enum.
  void show_arrow(uint16_t direction);
  void hide_arrow(uint16_t direction);
  void toggle_arrow(uint16_t direction);

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
