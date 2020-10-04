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
// CHUNK Contants
//

static const std::string _TILE_PATH   = "./asset/tiles16x16.png";
static const int _TILE_HEIGHT  = 16;
static const int _TILE_WIDTH   = 16;
static const int _CHUNK_RES    = 5;
static const int _CHUNK_HEIGHT = 128;
static const int _CHUNK_WIDTH  = 128;

static const SDL_Rect tile_map[9] = {
  { 0 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT },
  { 1 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT },
  { 2 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT },
  { 3 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT },
  { 4 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT },
  { 5 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT },
  { 6 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT },
  { 7 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT },
  { 8 * _TILE_WIDTH, 0, _TILE_WIDTH, _TILE_HEIGHT }
};

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
  BASECHUNK(unsigned int const& seed, int const& gx, int const& gy) {
    global_x = _CHUNK_WIDTH * gx;
    global_y = _CHUNK_HEIGHT * gx;

    PERLIN perlin(seed);

    // Populate the noise maps
    for(int y = 0; y <_CHUNK_HEIGHT; y++) {
      for(int x = 0; x <_CHUNK_WIDTH; x++) {
        double dx = ((_CHUNK_WIDTH / 2) - x) * ((_CHUNK_WIDTH / 2) - x);
        double dy = ((_CHUNK_WIDTH / 2) - y) * ((_CHUNK_WIDTH / 2) - y);
        double d = sqrt(dx + dy) / _CHUNK_WIDTH;

        double nx = 1.0 /_CHUNK_WIDTH;
        double ny = 1.0 /_CHUNK_HEIGHT;

        double elev = perlin.octave_noise_0_1((x + global_x) * nx * _CHUNK_RES, (y + global_y) * ny * _CHUNK_RES, 0.1, 20);
        double temp = perlin.octave_noise_0_1((x + global_x) * nx * _CHUNK_RES, (y + global_y) * ny * _CHUNK_RES, 1, 3);

        biome[y][x] = elev - d;
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

public:
  CHUNK(unsigned int const& seed, int const& gx, int const& gy)
    : BASECHUNK(seed, gx, gy), initialized(false), tiles(nullptr), chunk(nullptr) {};
  ~CHUNK() {};

  // Public CHUNK methods
  void initialize(SDL_Renderer *render);
  void draw(SDL_Rect *rect, SDL_Renderer *render);
  void finalize();

private:
  bool initialized;
  SDLTEXTURE_PTR tiles;
  SDLTEXTURE_PTR chunk;

  BIOME get_biome(double const& b, double const& m);
};


#endif // _CHUNK_HPP
