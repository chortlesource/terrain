////////////////////////////////////////////////////////////////////////////
//
// terrain - world.cpp
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

void WORLD::initialize(STATE const& state) {
  // Temporary Helper variables
  SDL_Renderer *render = state.window->get_render();

  tiles.initialize(state);
  biomeset.initialize(state);

  // Create the world map texture
  SDLTEXTURE_PTR wrld(SDL_CreateTexture(render, SDL_PIXELFORMAT_RGBA8888,
  SDL_TEXTUREACCESS_TARGET, worldw * tilew, worldh * tileh)
  , [=](SDL_Texture *t){SDL_DestroyTexture(t);});
  world = wrld;

  // Configure to draw to our chunk
  SDL_SetRenderTarget(render, world.get());

  for(int y = 0; y < worldh; y++) {
     for(int x = 0; x < worldw; x++) {
       // Get the biome in use
       SDL_Rect dst {x * tilew, y * tileh, tilew, tileh };
       tiles.draw(render, &dst, biomeset.get(biome[y][x], temps[y][x]));

       /*
       BIOME b = get_biome(biome[y][x], temps[y][x]);

       switch(b) {
         case BIOME::GRASSLAND:
           {
             tiles.draw(render, &dst, "GRASSLAND");
           }
           break;
         case BIOME::SHRUBLAND:
           {
             tiles.draw(render, &dst, "SHRUBLAND");
           }
           break;
         case BIOME::MOORLAND:
           {
             tiles.draw(render, &dst, "MOORLAND");
           }
           break;
         case BIOME::BEACH:
           {
             tiles.draw(render, &dst, "BEACH");
           }
           break;
         case BIOME::DIRT:
           {
             tiles.draw(render, &dst, "DIRT");
           }
           break;
         case BIOME::TUNDRA:
           {
             tiles.draw(render, &dst, "TUNDRA");
           }
           break;
         case BIOME::ROCKY:
           {
             tiles.draw(render, &dst, "ROCKY");
           }
           break;
         case BIOME::MOUNTAIN:
           {
             tiles.draw(render, &dst, "MOUNTAIN");
           }
           break;
         case BIOME::WATER:
           {
             tiles.draw(render, &dst, "WATER");
           }
           break;
         default:
           break;
       };*/
     }
   }
  // Reset to the default render target
  SDL_SetRenderTarget(render, NULL);

  initialized = true;
}


void WORLD::draw(SDL_Renderer *render, SDL_Rect *rect) {
  if(!initialized)
    return;

  SDL_RenderCopy(render, world.get(), NULL, rect);
}


void WORLD::finalize() {
  initialized = false;
  tiles.finalize();
  world       = nullptr;

  tilew       = 0;
  tileh       = 0;
  worldw      = 0;
  worldh      = 0;
  world_res   = 0;

  biome.clear();
  temps.clear();
}


/////////////////////////////////////////////////////////////
// Private WORLD methods
//


BIOME WORLD::get_biome(double const& b, double const& m) {
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
