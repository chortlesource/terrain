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
// STATE Enumeration
//
// Used to indicate the current state of the application

enum class STATE {
  INIT, RUN, EXIT
};

/////////////////////////////////////////////////////////////
// SYSTEM Class
//
// The SYSTEM class is the main container class used to
// initialize and finalize the application components

class SYSTEM {
  using TIMER_PTR     = std::shared_ptr<TIMER>;
  using PROFILER_PTR  = std::shared_ptr<PROFILER>;

public:
  // Public SYSTEM class methods
  SYSTEM() : initialized(false), timer(nullptr), profiler(nullptr) {};
  ~SYSTEM() {};

  void initialize();
  void execute();
  void finalize();

private:
  // Private SYSTEM class attributes
  bool          initialized;
  
  STATE         state;
  TIMER_PTR     timer;
  PROFILER_PTR  profiler;

};


#endif // _SYSTEM_HPP
