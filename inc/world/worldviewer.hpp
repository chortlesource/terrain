////////////////////////////////////////////////////////////////////////////
//
// terrain - worldviewer.hpp
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

#ifndef _WORLDVIEWER_HPP
#define _WORLDVIEWER_HPP


/////////////////////////////////////////////////////////////
// WORLDVIEWER Class
//
// The WORLDVIEWER renders the world to the screen in the
// appropriate position


class WORLDVIEWER {

public:
  // Public WORLDVIEWER methods
  void initialize(STATE const& state);
  void update(STATE const& state);
  void finalize();

private:
  bool      initialized;
  WORLD_PTR world;

};


#endif // _WORLDVIEWER_HPP
