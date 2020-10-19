////////////////////////////////////////////////////////////////////////////
//
// terrain - tileset.hpp
//
// Copyright (c) 2020 Christopher M. Short
//
// This file is part of terrain.
//
// terrain is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// terrain is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with terrain. If not, see <https://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////

#ifndef _TILESET_HPP
#define _TILESET_HPP


/////////////////////////////////////////////////////////////
// TILESET Class
//
// The TILESET class handles the tileset and enables the easy
// render of specific objects within the tilesheet using a
// simple coordinate system


class TILESET {
public:
  // Public TILESET methods
  TILESET() {};
  ~TILESET() {};

  void initialize(STATE const& state);
  void draw(SDL_Renderer *render, SDL_Rect *dest, std::string const& desc);
  void finalize();

private:
  bool           initialized;
  int            tilew;
  int            tileh;
  unsigned int   size;
  std::string    tilesrc;

  SDLTEXTURE_PTR                  tiles;
  std::map<std::string, SDL_Rect> tilemap;

};


#endif // _TILESET_HPP
