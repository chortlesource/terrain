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
// DEPENDENCIES
//

// Standard Libraries
#include <memory>


/////////////////////////////////////////////////////////////
// STATUS Enumeration
//
// Used to indicate the current status of the application

enum class STATUS {
  INIT, RUN, EXIT
};


/////////////////////////////////////////////////////////////
// STATE Struct
//
// Used to store SYSTEM components for convenient distribution

using WINDOW_PTR    = std::shared_ptr<WINDOW>;
using TIMER_PTR     = std::shared_ptr<TIMER>;
using PROFILER_PTR  = std::shared_ptr<PROFILER>;
using SDLINTER_PTR  = std::shared_ptr<SDLINTERFACE>;

struct STATE {
  STATUS        status;
  WINDOW_PTR    window;
  TIMER_PTR     timer;
  PROFILER_PTR  profiler;
  SDLINTER_PTR  sdlinterface;

  STATE() : status(STATUS::INIT), window(nullptr), timer(nullptr), profiler(nullptr), sdlinterface(nullptr) {};
};


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

  void initialize();
  void execute();
  void finalize();

private:
  // Private SYSTEM class attributes
  bool  initialized;
  STATE state;
};


#endif // _SYSTEM_HPP
