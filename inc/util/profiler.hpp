////////////////////////////////////////////////////////////////////////////
//
// terrain - timer.hpp
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

#ifndef _PROFILER_HPP
#define _PROFILER_HPP


/////////////////////////////////////////////////////////////
// DEPENDENCIES
//

// Standard Libraries
#include <chrono>
#include <mutex>


/////////////////////////////////////////////////////////////
// PROFILER Class
//
// PROFILER Class is a header only class for profiling an app
// in conjunction with the TIMER class


class PROFILER {
private:
  mutable std::mutex mute;
  double accumulator;

  std::uint64_t ups_count;
  std::uint64_t fps_count;

public:
  PROFILER() : accumulator(0), ups_count(0), fps_count(0) {};
  ~PROFILER() {};

  /////////////////////////////////////////////////////////////
  // update() - Update the profiler

  void update(double const& d) {
    std::scoped_lock<std::mutex> lock(mute);
    double delta = d;

    if(delta > 1.0) delta = 1.0;
    accumulator += delta;

    if(accumulator >= 1.0) {
      INFO("UPS :: ", floor((ups_count / 1.0) / 1000), " FPS :: ", fps_count);
      ups_count = 0;
      fps_count = 0;
      accumulator -= 1.0;
    }
  }

  /////////////////////////////////////////////////////////////
  // Triggers to hook into the main loop to track UPS and FPS

  void ups() { std::scoped_lock<std::mutex> lock(mute); ++ups_count; }
  void fps() { std::scoped_lock<std::mutex> lock(mute); ++fps_count; }

};


#endif // _PROFILER_HPP
