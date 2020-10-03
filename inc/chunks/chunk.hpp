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

/////////////////////////////////////////////////////////////
// CHUNK Class
//
// The CHUNK class procedurally generates chunks and displays
// them to the screen


class CHUNK {
  using TEXTURE_PTR = std::shared_ptr<SDL_Texture>;
  using RENDER_PTR = std::shared_ptr<SDL_Renderer>;

public:
  CHUNK() : initialized(false), tiles(nullptr), chunk(nullptr) {};
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

};


#endif // _CHUNK_HPP
