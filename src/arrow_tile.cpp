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

  // TODO: Make fixed size of 32px for tile configurable
  int totaledge = s_tileedge + 2 * (s_arrowdistance + s_arrowedge);
  set_size_request(totaledge, totaledge);
}

ArrowTile::~ArrowTile()
{
  //
}

/***************************************
 * Getters & Setters
 ***************************************/

void ArrowTile::set_tile(Glib::RefPtr<Gdk::Pixbuf> p_pixbuf)
{
  mp_tile = p_pixbuf;
}

Glib::RefPtr<Gdk::Pixbuf> ArrowTile::get_tile()
{
  return mp_tile;
}

/***************************************
 * Signal handlers
 ***************************************/

bool ArrowTile::on_draw(const Cairo::RefPtr<Cairo::Context>& cc)
{
  if (mp_tile) {
    Gdk::Cairo::set_source_pixbuf(cc, mp_uparrow, s_arrowedge + 2 * s_arrowdistance, 0);
    cc->paint();
    Gdk::Cairo::set_source_pixbuf(cc, mp_leftarrow, 0, s_arrowedge + 2 * s_arrowdistance);
    cc->paint();
    Gdk::Cairo::set_source_pixbuf(cc, mp_tile, s_arrowedge + s_arrowdistance, s_arrowedge + s_arrowdistance);
    cc->paint();
    Gdk::Cairo::set_source_pixbuf(cc, mp_rightarrow, s_arrowedge + 2 * s_arrowdistance + s_tileedge, s_arrowedge + 2 * s_arrowdistance);
    cc->paint();
    Gdk::Cairo::set_source_pixbuf(cc, mp_downarrow, s_arrowedge + 2 * s_arrowdistance, s_arrowedge + 2 * s_arrowdistance + s_tileedge);
    cc->paint();

    return true;
  }
  else
    return false;
}
