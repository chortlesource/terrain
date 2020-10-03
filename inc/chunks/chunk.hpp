////////////////////////////////////////////////////////////////////////////
//
// terrain - chunk.hpp
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

#ifndef _CHUNK_HPP
#define _CHUNK_HPP

/////////////////////////////////////////////////////////////
// DEPENDENCIES
//

// Standard Libraries
#include <memory>
#include <array>
#include <string>


/////////////////////////////////////////////////////////////
// CHUNK Contants
//

static const std::string _TILE_PATH   = "./asset/tiles.png";
static const int _TILE_HEIGHT  = 32;
static const int _TILE_WIDTH   = 32;
static const int _CHUNK_RES    = 10;
static const int _CHUNK_HEIGHT = 64;
static const int _CHUNK_WIDTH  = 64;


enum class BIOME {
  GRASSLAND, SHRUBLAND, MOORLAND, BEACH,
  DIRT, TUNDRA, ROCKY, MOUNTAIN, WATER
};


/////////////////////////////////////////////////////////////
// BASECHUNK Class
//
// The BASECHUNK class procedurally generates data from noise
// This is later rendered in the CHUNK class


class BASECHUNK {
public:
  BASECHUNK(int const& gx, int const& gy) {
    global_x = _CHUNK_WIDTH * gx;
    global_y = _CHUNK_HEIGHT * gx;

    PERLIN perlin;

    // Populate the noise maps
    for(int y = 0; y <_CHUNK_HEIGHT; y++) {
      for(int x = 0; x <_CHUNK_WIDTH; x++) {
        double nx = 1.0 /_CHUNK_WIDTH;
        double ny = 1.0 /_CHUNK_HEIGHT;

        double elev = perlin.octave_noise_0_1((x + global_x) * nx * _CHUNK_RES, (y + global_y) * ny * _CHUNK_RES, 0.1, 8);
        double temp = perlin.octave_noise_0_1((x + global_x) * nx * _CHUNK_RES, (y + global_y) * ny * _CHUNK_RES, 1, 3);

        biome[y][x] = elev;
        temps[y][x] = temp;
      }
    }
  }

  virtual ~BASECHUNK() {};

protected:
  // Protected BASECHUNK attributes
  double biome[_CHUNK_HEIGHT][_CHUNK_WIDTH];
  double temps[_CHUNK_HEIGHT][_CHUNK_WIDTH];

  int global_x;
  int global_y;
};


/////////////////////////////////////////////////////////////
// CHUNK Class
//
// The CHUNK class procedurally generates chunks and displays
// them to the screen


class CHUNK : public BASECHUNK {
  using TEXTURE_PTR = std::shared_ptr<SDL_Texture>;
  using RENDER_PTR = std::shared_ptr<SDL_Renderer>;

public:
  CHUNK(int const& gx, int const& gy) : BASECHUNK(gx, gy), initialized(false), tiles(nullptr), chunk(nullptr) {};
  ~CHUNK() {};

  // Public CHUNK methods
  void initialize(RENDER_PTR& render);
  void draw(RENDER_PTR& render);
  void finalize();

private:
  bool initialized;
  TEXTURE_PTR tiles;
  TEXTURE_PTR chunk;

  std::array<SDL_Rect, 9> tile_src;

  BIOME get_biome(double const& b, double const& m);
};


#endif // _CHUNK_HPP
