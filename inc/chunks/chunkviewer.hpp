////////////////////////////////////////////////////////////////////////////
//
// terrain - chunkviewer.hpp
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

#ifndef _CHUNKVIEWER_HPP
#define _CHUNKVIEWER_HPP


/////////////////////////////////////////////////////////////
// CHUNKVIEWER Class
//
// The CHUNKVIEWER class contains all chunks and renders them to
// the main chunk texture as required


class CHUNKVIEWER {

public:
  CHUNKVIEWER() {};
  ~CHUNKVIEWER() {};

  void initialize(STATE const& state);
  void update(STATE const& state);
  void finalize();

private:
  bool        initialized;
  CHUNK_PTR   chunk;

};


#endif // _CHUNKVIEWER_HPP
