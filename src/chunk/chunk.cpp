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

void CHUNK::initialize(STATE const& state) {
  // Load the tiles
  SDL_Renderer *render = state.window->get_render();
  int chunkw  = state.config["CHUNK"]["CHUNK_WIDTH"].asInt();
  int chunkh = state.config["CHUNK"]["CHUNK_HEIGHT"].asInt();
  int tilew = state.config["TILES"]["TILE_HEIGHT"].asInt();
  int tileh = state.config["TILES"]["TILE_HEIGHT"].asInt();
  std::string tilep = state.config["TILES"]["TILE_PATH"].asString();

  const SDL_Rect tile_map[9] = {
    { 0 * tilew, 0, tilew, tileh },
    { 1 * tilew, 0, tilew, tileh },
    { 2 * tilew, 0, tilew, tileh },
    { 3 * tilew, 0, tilew, tileh },
    { 4 * tilew, 0, tilew, tileh },
    { 5 * tilew, 0, tilew, tileh },
    { 6 * tilew, 0, tilew, tileh },
    { 7 * tilew, 0, tilew, tileh },
    { 8 * tilew, 0, tilew, tileh }
  };

  SDLTEXTURE_PTR temp(IMG_LoadTexture(render, tilep.c_str()), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  tiles = temp;

  // Create our new texture
  SDLTEXTURE_PTR ch(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888,
  SDL_TEXTUREACCESS_TARGET, chunkw * tilew, chunkh * tileh)
  , [=](SDL_Texture *t){SDL_DestroyTexture(t);});
  chunk = ch;

  // Configure to draw to our chunk
  SDL_SetRenderTarget(render, chunk.get());

  for(int y = 0; y < chunkh; y++) {
     for(int x = 0; x < chunkw; x++) {
       // Get the biome in use
       BIOME b = get_biome(biome[y][x], temps[y][x]);
       SDL_Rect dst {x * tilew, y * tileh, tilew, tileh };

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


void CHUNK::draw(SDL_Rect *rect, SDL_Renderer *render) {
  if(!initialized)
    return;

  SDL_RenderCopy(render, chunk.get(), NULL, rect);
}


void CHUNK::finalize() {
  initialized = false;
  tiles       = nullptr;
  chunk       = nullptr;
}


/////////////////////////////////////////////////////////////
// Private CHUNK class methods
//


BIOME CHUNK::get_biome(double const& b, double const& m) {
  if (b < 0.2)    return BIOME::WATER;
  if (b < 0.27)  return BIOME::BEACH;

  if(b > 0.6) {
    if(m < 0.3)   return BIOME::ROCKY;
    if(m < 0.5)   return BIOME::MOUNTAIN;
    if(m < 0.85)  return BIOME::TUNDRA;
    return BIOME::MOUNTAIN;
  }

  if (b > 0.5) {
    if (m < 0.30) return BIOME::GRASSLAND;
    if (m < 0.50) return BIOME::SHRUBLAND;
    if (m < 0.80)  return BIOME::WATER;
    return BIOME::MOORLAND;
  }

  if (b >= 0.3) {
    if (m < 0.30) return BIOME::DIRT;
    if (m < 0.40) return BIOME::GRASSLAND;
    if (m < 0.50) return BIOME::SHRUBLAND;
    if (m > 0.9)  return BIOME::WATER;
    return BIOME::MOORLAND;
  }

  if (m < 0.30)   return BIOME::DIRT;
  if (m < 0.33)   return BIOME::GRASSLAND;
  if (m < 0.66)   return BIOME::SHRUBLAND;
  return BIOME::MOORLAND;
}
