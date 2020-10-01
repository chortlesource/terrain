////////////////////////////////////////////////////////////////////////////
//
// terrain - system.cpp
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

#include "terrain.hpp"


/////////////////////////////////////////////////////////////
// Public SYSTEM class methods
//


void SYSTEM::initialize() {
  // Initialize the SYSTEM components
  timer       = std::make_shared<TIMER>();
  profiler    = std::make_shared<PROFILER>();

  state       = STATE::RUN;
  initialized = true;
}


void SYSTEM::execute() {
  timer->start();

  double rate    = 0.01;
  double elapsed = 0;

  while(state != STATE::EXIT) {
    // Update the timer and seek delta
    timer->update();
    double delta = timer->delta();

    if(delta > 0.60) delta = 0.60;
    elapsed += delta;

    // Fix the timestep
    while(elapsed >= rate) {
      profiler->fps();    // Profile the FPS
      elapsed -= rate;
    }

    profiler->ups();      // Profile the UPS
    profiler->update(timer->delta());   // Update the profiler
  };

}


void SYSTEM::finalize() {
  initialized = false;

  // Free the shared pointers
  profiler = nullptr;
  timer    = nullptr;
}
