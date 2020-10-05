////////////////////////////////////////////////////////////////////////////
//
// terrain - worldviewer.cpp
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
// Public WORLDVIEWER methods
//


void WORLDVIEWER::initialize(STATE const& state) {
  // Initialize the world
  world = std::make_shared<WORLD>(state);
  world->initialize(state);

  initialized = true;
}


void WORLDVIEWER::update(STATE const& state) {
  if(!initialized)
    return;

  int width  = world->width() * world->tile_w() + state.zoom;
  int height = world->height() * world->tile_h() + state.zoom;

  SDL_Rect dest { state.pos_x, state.pos_y, width, height };
  world->draw(state.window->get_render(), &dest);
}


void WORLDVIEWER::finalize() {
  initialized = false;
  world->finalize();
  world = nullptr;
}
