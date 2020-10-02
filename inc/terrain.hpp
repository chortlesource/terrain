////////////////////////////////////////////////////////////////////////////
//
// terrain - terrain.hpp
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

#ifndef _TERRAIN_HPP
#define _TERRAIN_HPP


/////////////////////////////////////////////////////////////
// DEPENDENCIES / STANDARD LIBS
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string>


/////////////////////////////////////////////////////////////
// APPLICATION DATA
//

static const std::string _APP_NAME    = "terrain";
static const std::string _APP_VERSION = "0.0.1-ALPHA";
static const std::string _APP_AUTHOR  = "C. M. Short";
static const std::string _APP_SOURCE  = "http://www.github.com/chortlesoft/terrain";
static const int _APP_WIDTH  = 800;
static const int _APP_HEIGHT = 600;


/////////////////////////////////////////////////////////////
// FORWARDS
//

class SYSTEM;
class TIMER;
class PROFILER;
class WINDOW;
class SDLINTERFACE;

/////////////////////////////////////////////////////////////
// LOCAL INCLUDES
//

// Utilities
#include "util/debug.hpp"
#include "util/cliparse.hpp"
#include "util/timer.hpp"
#include "util/profiler.hpp"

#include "system.hpp"
#include "window.hpp"

#include "events/sdlinterface.hpp"


#endif // _TERRAIN_HPP
