////////////////////////////////////////////////////////////////////////////
//
// terrain - system.hpp
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

#ifndef _SYSTEM_HPP
#define _SYSTEM_HPP


/////////////////////////////////////////////////////////////
// SYSTEM Class
//
// The SYSTEM class is the main container class used to
// initialize and finalize the application components

class SYSTEM {

public:
  // Public SYSTEM class methods
  SYSTEM() {};
  ~SYSTEM() {};

  void initialize(int const& argc, const char *argv[]);
  void execute();
  void finalize();

private:
  // Private SYSTEM class attributes
  bool  initialized;
  STATE state;

  // Private SYSTEM class methods
  void parse(CLIPARSE& p);

};


#endif // _SYSTEM_HPP
