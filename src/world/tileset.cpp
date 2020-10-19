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

#include "terrain.hpp"


/////////////////////////////////////////////////////////////
// Public WORLD methods
//

void TILESET::initialize(STATE const& state) {
  // Load the relevant Json Data
  tilew   = state.tilecfg["TILE_WIDTH"].asInt();
  tileh   = state.tilecfg["TILE_HEIGHT"].asInt();
  size    = state.tilecfg["TILE_NUM"].asUInt();
  tilesrc = state.tilecfg["TILE_SRC"].asString();

  // Create a record in the map of the tile coordinates
  for(unsigned int i = 0; i < size; i++) {
    SDL_Rect rect = { tilew * state.tilecfg["TILE_SET"][i]["X"].asInt(), tileh * state.tilecfg["TILE_SET"][i]["Y"].asInt(), tilew, tileh };
    tilemap[state.tilecfg["TILE_SET"][i]["DESC"].asString()] = rect;
  }

  // Load the tilesheet
  SDLTEXTURE_PTR ttemp(IMG_LoadTexture(state.window->get_render(), tilesrc.c_str()), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  tiles = ttemp;

  initialized = true;
}


void TILESET::draw(SDL_Renderer *render, SDL_Rect *dest, std::string const& desc) {
  if(!initialized)
    return;

  SDL_Rect src;

  // Attempt to find the relevant tilesheet
  try {
    src = tilemap.at(desc);
  } catch(std::out_of_range& ex) {
    ERROR("Unable to find tile: ", desc);
    return; // Don't draw
  }

  // Draw the relevant tile to the screen
  SDL_RenderCopy(render, tiles.get(), &src, dest);
}


void TILESET::finalize() {
  if(!initialized)
    return;

  initialized = false;
  tilew       = 0;
  tileh       = 0;
  size        = 0;
  tilesrc.clear();
  tiles       = nullptr;
  tilemap.clear();
}
