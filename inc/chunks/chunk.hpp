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

//static const std::string _TILE_PATH   = "./asset/tiles16x16.png";
//static const int _TILE_HEIGHT  = 16;
//static const int _TILE_WIDTH   = 16;
//static const int _CHUNK_RES    = 5;
//static const int _CHUNK_HEIGHT = 128;
//static const int _CHUNK_WIDTH  = 128;

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
  BASECHUNK(STATE const& state, int const& gx, int const& gy) {
    int chunkw  = state.config["CHUNK"]["CHUNK_WIDTH"].asInt();
    int chunkh = state.config["CHUNK"]["CHUNK_HEIGHT"].asInt();
    int chunkres    = state.config["CHUNK"]["CHUNK_RES"].asInt();

    global_x = chunkw * gx;
    global_y = chunkh * gx;

    PERLIN perlin(state.seed);

    // Configure our vectors
    biome.resize(chunkh);
    temps.resize(chunkh);
    for(auto &it: biome) it.resize(chunkw);
    for(auto &it: temps) it.resize(chunkw);

    // Populate the noise maps
    for(int y = 0; y < chunkh; y++) {
      for(int x = 0; x < chunkw; x++) {
        double dx = ((chunkw / 2) - x) * ((chunkw / 2) - x);
        double dy = ((chunkw / 2) - y) * ((chunkw / 2) - y);
        double d = sqrt(dx + dy) / chunkw;

        double nx = 1.0 /chunkw;
        double ny = 1.0 /chunkh;

        double elev = perlin.octave_noise_0_1((x + global_x) * nx * chunkres, (y + global_y) * ny * chunkres, 0.1, 20);
        double temp = perlin.octave_noise_0_1((x + global_x) * nx * chunkres, (y + global_y) * ny * chunkres, 1, 3);

        biome[y][x] = elev - d;
        temps[y][x] = temp;
      }
    }
  }

  virtual ~BASECHUNK() {};

protected:
  // Protected BASECHUNK attributes
  std::vector<std::vector<double>> biome;
  std::vector<std::vector<double>> temps;
  //double *biome[_CHUNK_HEIGHT][_CHUNK_WIDTH];
  //double *temps[_CHUNK_HEIGHT][_CHUNK_WIDTH];

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
  CHUNK(STATE const& state, int const& gx, int const& gy)
    : BASECHUNK(state, gx, gy), initialized(false), tiles(nullptr), chunk(nullptr) {};
  ~CHUNK() {};

  // Public CHUNK methods
  void initialize(STATE const& state);
  void draw(SDL_Rect *rect, SDL_Renderer *render);
  void finalize();

private:
  bool initialized;
  SDLTEXTURE_PTR tiles;
  SDLTEXTURE_PTR chunk;

  BIOME get_biome(double const& b, double const& m);
};


#endif // _CHUNK_HPP
