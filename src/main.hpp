#ifndef TILEPASS_MAIN_HPP
#define TILEPASS_MAIN_HPP
#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <gtkmm.h>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

/**
 * Specifies the different possible directions a tile can be
 * bassed. A tile’s direction is stored as an unsigned 16-bit
 * (4 byte) integer like this:
 *
 *   ↑→↓←
 *
 * That is, each bit indicated whether the tile is passable in
 * a specific direction. Examples:
 *
 *     ↑→↓←  | Decimal | Directions
 * 0b  1000  |       8 | Up
 *     1010  |      10 | Up and down
 *     0011  |       3 | Down and left
 *     1111  |      15 | All directions
 *
 * OR’ing the values in this enum gives you the possibility
 * to specify more than one direction.
 */
enum ArrowDirection {
  DIRECTION_LEFT  = 1 << 0,
  DIRECTION_DOWN  = 1 << 1,
  DIRECTION_RIGHT = 1 << 2,
  DIRECTION_UP    = 1 << 3
};

#endif
