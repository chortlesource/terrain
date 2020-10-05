////////////////////////////////////////////////////////////////////////////
//
// terrain - chunkviewer.cpp
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
// Public CHUNKVIEWER class methods
//

void CHUNKVIEWER::initialize(STATE const& state) {
  chunk = std::make_shared<CHUNK>(state, 0, 0);
  chunk->initialize(state);

  initialized = true;
}


void CHUNKVIEWER::update(STATE const& state) {
  if(!initialized)
    return;

  int chunkw  = state.config["CHUNK"]["CHUNK_WIDTH"].asInt();
  int chunkh = state.config["CHUNK"]["CHUNK_HEIGHT"].asInt();
  int tilew = state.config["TILES"]["TILE_HEIGHT"].asInt();
  int tileh = state.config["TILES"]["TILE_HEIGHT"].asInt();

  SDL_Rect dest { state.pos_x, state.pos_y, chunkw * tilew + state.zoom, chunkh * tileh + state.zoom };
  chunk->draw(&dest, state.window->get_render());
}


void CHUNKVIEWER::finalize() {
  initialized = false;

  chunk->finalize();
  chunk = nullptr;
}
