////////////////////////////////////////////////////////////////////////////
//
// terrain - chunk.cpp
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
// Public CHUNK class methods
//

void CHUNK::initialize(RENDER_PTR& render) {
  // Load the tiles
  TEXTURE_PTR temp(IMG_LoadTexture(render.get(), _TILE_PATH.c_str()), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  tiles = temp;

  // Create our new texture
  TEXTURE_PTR ch(SDL_CreateTexture(render.get(), SDL_PIXELFORMAT_RGBA8888,
  SDL_TEXTUREACCESS_TARGET, _APP_WIDTH, _APP_HEIGHT)
  , [=](SDL_Texture *t){SDL_DestroyTexture(t);});
  chunk = ch;

  // Populate the tile rects
  for(int i = 0; i < 9; i++)
    tile_src[i] = { i * 32, 0, 32, 32 };

  // Configure to draw to our chunk
  SDL_SetRenderTarget(render.get(), chunk.get());

  for(int i = 0; i < 9; i ++) {
   SDL_Rect dest { i * 32, i * 32, 32, 32 };
   SDL_RenderCopy(render.get(), tiles.get(), &tile_src[i], &dest);
  }

  SDL_SetRenderTarget(render.get(), NULL);

  initialized = true;
}


void CHUNK::draw(RENDER_PTR& render) {
  if(!initialized)
    return;

  SDL_RenderCopy(render.get(), chunk.get(), NULL, NULL);
}


void CHUNK::finalize() {
  initialized = false;
  tiles = nullptr;
  chunk = nullptr;
}
