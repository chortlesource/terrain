////////////////////////////////////////////////////////////////////////////
//
// terrain - state.hpp
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

#ifndef _STATE_HPP
#define _STATE_HPP


/////////////////////////////////////////////////////////////
// STATE Struct
//
// Used to store SYSTEM components for convenient distribution


struct STATE {
  STATUS              status;
  WINDOW_PTR          window;
  IO_PTR              io;
  TIMER_PTR           timer;
  PROFILER_PTR        profiler;
  WORLDVIEWER_PTR     worldviewer;
  SDLINTER_PTR        sdlinterface;

  Json::Value         config;
  unsigned int        seed;
  bool                run;
  int                 pos_x;
  int                 pos_y;
  int                 zoom;

  STATE() : status(STATUS::INIT), window(nullptr), io(nullptr), timer(nullptr),
  profiler(nullptr), worldviewer(nullptr), sdlinterface(nullptr), config(Json::Value::null),
  seed(std::default_random_engine::default_seed), run(false), pos_x(0), pos_y(0), zoom(1) {};
};


#endif // _STATE_HPP
