////////////////////////////////////////////////////////////////////////////
//
// terrain - world.hpp
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

#ifndef _WORLD_HPP
#define _WORLD_HPP


/////////////////////////////////////////////////////////////
// BIOME Enumeration
//
// A list of the various biomes currently available

enum class BIOME {
  GRASSLAND, SHRUBLAND, MOORLAND, BEACH,
  DIRT, TUNDRA, ROCKY, MOUNTAIN, WATER
};


/////////////////////////////////////////////////////////////
// BASEWORLD Class
//
// The BASEWORLD class procedurally generates data from noise
// This is later rendered in the WORLD class


class BASEWORLD {

protected:
  // Private BASEWORLD attributes
  std::string tile_path;
  int         tilew;
  int         tileh;
  int         worldw;
  int         worldh;
  int         world_res;

  NOISEMAP    biome;
  NOISEMAP    temps;

public:
  // Public BASEWORLD methods
  BASEWORLD(STATE const& state) {
    // Initialize our variables
    tile_path = state.config["TILE"]["TILE_PATH"].asString();
    tilew     = state.config["TILE"]["TILE_WIDTH"].asInt();
    tileh     = state.config["TILE"]["TILE_HEIGHT"].asInt();
    worldw    = state.config["WORLD"]["WORLD_WIDTH"].asInt();
    worldh    = state.config["WORLD"]["WORLD_HEIGHT"].asInt();
    world_res = state.config["WORLD"]["WORLD_RES"].asInt();

    // Initialize the Perlin generator
    PERLIN perlin(state.seed);

    // Configure our vectors
    biome.resize(worldh);
    temps.resize(worldh);
    for(auto &it: biome) it.resize(worldw);
    for(auto &it: temps) it.resize(worldw);

    // Populate the noise maps
    for(int y = 0; y < worldh; y++) {
      for(int x = 0; x < worldw; x++) {
        double dx = ((worldw / 2) - x) * ((worldw / 2) - x);
        double dy = ((worldw / 2) - y) * ((worldw / 2) - y);
        double d = sqrt(dx + dy) / worldw;

        double nx = 1.0 / worldw;
        double ny = 1.0 / worldh;

        double elev = perlin.octave_noise_0_1(x * nx * world_res, y * ny * world_res, 0.1, 20);
        double temp = perlin.octave_noise_0_1(x * nx * world_res, y * ny * world_res, 1, 3);

        biome[y][x] = elev - d;
        temps[y][x] = temp;
      }
    }
  }

  int const& width()  { return worldw; }
  int const& height() { return worldh; }
  int const& tile_w() { return tilew;  }
  int const& tile_h() { return tileh;  }

};


/////////////////////////////////////////////////////////////
// WORLD Class
//
// The WORLD class renders the generated world data to the
// display.


class WORLD : public BASEWORLD {

public:
  // Public WORLD methods
  WORLD(STATE const& state) : BASEWORLD(state), initialized(false), tiles(nullptr), world(nullptr) {};

  void initialize(STATE const& state);
  void draw(SDL_Renderer *render, SDL_Rect *rect);
  void finalize();

private:
  // Private WORLD attributes
  bool initialized;
  SDLTEXTURE_PTR tiles;
  SDLTEXTURE_PTR world;

  // Private WORLD methods
  BIOME get_biome(double const& b, double const& m);

};


#endif // _WORLD_HPP
