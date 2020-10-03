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

void CHUNK::initialize(SDL_Renderer *render) {
  // Load the tiles
  TEXTURE_PTR temp(IMG_LoadTexture(render, _TILE_PATH.c_str()), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  tiles = temp;

  // Create our new texture
  TEXTURE_PTR ch(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888,
  SDL_TEXTUREACCESS_TARGET, _CHUNK_WIDTH * _TILE_WIDTH, _CHUNK_HEIGHT * _TILE_HEIGHT)
  , [=](SDL_Texture *t){SDL_DestroyTexture(t);});
  chunk = ch;

  // Configure to draw to our chunk
  SDL_SetRenderTarget(render, chunk.get());

  for(int y = 0; y < _CHUNK_HEIGHT; y++) {
     for(int x = 0; x < _CHUNK_WIDTH; x++) {
       // Get the biome in use
       BIOME b = get_biome(biome[y][x], temps[y][x]);
       SDL_Rect dst {x * _TILE_WIDTH, y * _TILE_HEIGHT, _TILE_WIDTH, _TILE_HEIGHT };

       switch(b) {
         case BIOME::GRASSLAND:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[0], &dst);
           }
           break;
         case BIOME::SHRUBLAND:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[1], &dst);
           }
           break;
         case BIOME::MOORLAND:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[2], &dst);
           }
           break;
         case BIOME::BEACH:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[3], &dst);
           }
           break;
         case BIOME::DIRT:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[4], &dst);
           }
           break;
         case BIOME::TUNDRA:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[5], &dst);
           }
           break;
         case BIOME::ROCKY:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[6], &dst);
           }
           break;
         case BIOME::MOUNTAIN:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[7], &dst);
           }
           break;
         case BIOME::WATER:
           {
             SDL_RenderCopy(render, tiles.get(), &tile_map[8], &dst);
           }
           break;
         default:
           break;
       };
     }
   }

  // Reset to the default render target
  SDL_SetRenderTarget(render, NULL);

  initialized = true;
}


void CHUNK::draw(SDL_Renderer *render) {
  if(!initialized)
    return;

  SDL_Rect src { global_x, global_y, _APP_WIDTH, _APP_HEIGHT };
  SDL_RenderCopy(render, chunk.get(), &src, NULL);
}


void CHUNK::finalize() {
  initialized = false;
  tiles = nullptr;
  chunk = nullptr;
}


BIOME CHUNK::get_biome(double const& b, double const& m) {
  if (b < 0.25) return BIOME::WATER;
  if (b < 0.325) return BIOME::BEACH;

  if(b > 0.8) {
    if(m < 0.1) return BIOME::ROCKY;
    if(m < 0.4) return BIOME::MOUNTAIN;
    if(m < 0.65) return BIOME::TUNDRA;
    return BIOME::MOUNTAIN;
  }

  if (b > 0.6) {
    if (m < 0.30) return BIOME::GRASSLAND;
    if (m < 0.50) return BIOME::SHRUBLAND;
    return BIOME::MOORLAND;
  }

  if (b >= 0.3) {
    if (m < 0.30) return BIOME::DIRT;
    if (m < 0.50) return BIOME::GRASSLAND;
    if (m < 0.66) return BIOME::SHRUBLAND;
    return BIOME::MOORLAND;
  }

  if (m < 0.30) return BIOME::DIRT;
  if (m < 0.33) return BIOME::GRASSLAND;
  if (m < 0.66) return BIOME::SHRUBLAND;
  return BIOME::MOORLAND;
}
