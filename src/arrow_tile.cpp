#include "arrow_tile.hpp"
#include "resource_manager.hpp"

/****************************************
Explanation of the widget’s pixel-layout:

              /\     22px (arrow edge)
              --      5px (distance between arrow and tile)
           <  []  >  32px (tile edge, asummed)
              --      5px (distance between arrow and tile)
              \/      22px (arrow edge)

Note the widget is perfectly symmetrical, so the values
are the same for horizontal and vertical alignment.
 ****************************************/

// Pixel distances as layout out above
static int s_tileedge      = 32; //px
static int s_arrowedge     = 22; //px
static int s_arrowdistance = 5;  //px

/***************************************
 * Constructors & Destructors
 ***************************************/

ArrowTile::ArrowTile()
  : Gtk::DrawingArea()
{
  mp_uparrow    = gp_resource_manager->get_image("go-up.png");
  mp_downarrow  = gp_resource_manager->get_image("go-down.png");
  mp_leftarrow  = gp_resource_manager->get_image("go-previous.png");
  mp_rightarrow = gp_resource_manager->get_image("go-next.png");

  setup_signal_handlers();

  // TODO: Make fixed size of 32px for tile configurable
  int totaledge = s_tileedge + 2 * (s_arrowdistance + s_arrowedge);
  set_size_request(totaledge, totaledge);
}

ArrowTile::~ArrowTile()
{
  //
}

/***************************************
 * GUI helpers
 ***************************************/

void ArrowTile::setup_signal_handlers()
{
  // Gtk::DrawingArea does not receive many events by default. We
  // however want to handle clicks, so add that to the event mask.
  add_events(Gdk::BUTTON_PRESS_MASK | Gdk::BUTTON_RELEASE_MASK);

  /////// Actual signal handlers ///////
  signal_button_release_event().connect(sigc::mem_fun(*this, &ArrowTile::on_button_released));
}

/***************************************
 * Methods
 ***************************************/

void ArrowTile::set_tile(Glib::RefPtr<Gdk::Pixbuf> p_pixbuf)
{
  mp_tile = p_pixbuf;
  m_show_directions = 0;
  queue_draw();
}

void ArrowTile::set_tile_with_directions(Glib::RefPtr<Gdk::Pixbuf> p_pixbuf, uint16_t directions)
{
  mp_tile = p_pixbuf;
  m_show_directions = directions;
  queue_draw();
}

Glib::RefPtr<Gdk::Pixbuf> ArrowTile::get_tile()
{
  return mp_tile;
}

void ArrowTile::show_arrow(uint16_t direction)
{
  m_show_directions |= direction;
  queue_draw();
}

void ArrowTile::hide_arrow(uint16_t direction)
{
  m_show_directions &= ~direction;
  queue_draw();
}

void ArrowTile::toggle_arrow(uint16_t direction)
{
  m_show_directions ^= direction;
  queue_draw();
}

bool ArrowTile::is_active(uint16_t direction)
{
  return (m_show_directions & direction) == direction;
}

uint16_t ArrowTile::get_directions()
{
  return m_show_directions;
}

/***************************************
 * Signal handlers
 ***************************************/

bool ArrowTile::on_draw(const Cairo::RefPtr<Cairo::Context>& cc)
{
  if (mp_tile) {
    // Draw the tile itself
    Gdk::Cairo::set_source_pixbuf(cc, mp_tile, s_arrowedge + s_arrowdistance, s_arrowedge + s_arrowdistance);
    cc->paint();

    // Up arrow
    Gdk::Cairo::set_source_pixbuf(cc, mp_uparrow, s_arrowedge + 2 * s_arrowdistance, 0);
    if (m_show_directions & DIRECTION_UP)
      cc->paint();
    else
      cc->paint_with_alpha(0.2);

    // Left arrow
    Gdk::Cairo::set_source_pixbuf(cc, mp_leftarrow, 0, s_arrowedge + 2 * s_arrowdistance);
    if (m_show_directions & DIRECTION_LEFT)
      cc->paint();
    else
      cc->paint_with_alpha(0.2);

    // Right arrow
    Gdk::Cairo::set_source_pixbuf(cc, mp_rightarrow, s_arrowedge + 2 * s_arrowdistance + s_tileedge, s_arrowedge + 2 * s_arrowdistance);
    if (m_show_directions & DIRECTION_RIGHT)
      cc->paint();
    else
      cc->paint_with_alpha(0.2);

    // Down arrow
    Gdk::Cairo::set_source_pixbuf(cc, mp_downarrow, s_arrowedge + 2 * s_arrowdistance, s_arrowedge + 2 * s_arrowdistance + s_tileedge);
    if (m_show_directions & DIRECTION_DOWN)
      cc->paint();
    else
      cc->paint_with_alpha(0.2);

    return true;
  }
  else
    return false;
}

bool ArrowTile::on_button_released(GdkEventButton* p_event)
{
  // Up and down arrows share the same vertical stripe
  if (p_event->x > s_arrowedge + 2 * s_arrowdistance && p_event->x <= 2 * s_arrowedge + 2 * s_arrowdistance) {
    // Up arrow
    if (p_event->y > 0 && p_event->y <= s_arrowedge)
      toggle_arrow(DIRECTION_UP);
    // Down arrow
    else if (p_event->y > s_arrowedge + 2 * s_arrowdistance + s_tileedge && p_event->y <= 2 * s_arrowedge + 2 * s_arrowdistance + s_tileedge)
      toggle_arrow(DIRECTION_DOWN);
  }
  // Left and right arrows share the same horizontal stripe
  else if (p_event->y > s_arrowedge + 2 * s_arrowdistance && p_event->y <= 2 * s_arrowedge + 2 * s_arrowdistance) {
    // Left arrow
    if (p_event->x > 0 && p_event->x <= s_arrowedge)
      toggle_arrow(DIRECTION_LEFT);
    // Right arrow
    else if (p_event->x > s_arrowedge  + 2 * s_arrowdistance + s_tileedge && p_event->x <= 2 * s_arrowedge + 2 * s_arrowdistance + s_tileedge)
      toggle_arrow(DIRECTION_RIGHT);
  }

  return true;
}
