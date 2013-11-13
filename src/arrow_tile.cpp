#include "arrow_tile.hpp"
#include "resource_manager.hpp"

/***************************************
 * Constructors & Destructors
 ***************************************/

ArrowTile::ArrowTile()
  : Gtk::DrawingArea()
{
  mp_uparrow = gp_resource_manager->get_image("go-up.png");
  mp_downarrow = gp_resource_manager->get_image("go-down.png");
  mp_leftarrow = gp_resource_manager->get_image("go-previous.png");
  mp_rightarrow = gp_resource_manager->get_image("go-next.png");

  // TODO: Make fixed size of 32px for tile configurable
  set_size_request(86, 86);
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
    Gdk::Cairo::set_source_pixbuf(cc, mp_tile, 0, 0);
    cc->paint();

    return true;
  }
  else
    return false;
}
