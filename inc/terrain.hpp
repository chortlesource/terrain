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
// DEPENDENCIES
//

// SDL Dependencies
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Standard Libraries
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <chrono>
#include <numeric>
#include <random>
#include <type_traits>
#include <fstream>
#include <experimental/filesystem>

#include <vector>
#include <string>
#include <array>
#include <mutex>


/////////////////////////////////////////////////////////////
// APPLICATION DATA
//

static const std::string _APP_NAME    = "terrain";
static const std::string _APP_VERSION = "0.0.1-ALPHA";
static const std::string _APP_AUTHOR  = "C. M. Short";
static const std::string _APP_SOURCE  = "http://www.github.com/chortlesoft/terrain";


/////////////////////////////////////////////////////////////
// LOCAL INCLUDES
//

// Utilities
#include "lib/json.hpp"

#include "util/debug.hpp"
#include "util/cliparse.hpp"
#include "util/perlin.hpp"
#include "util/timer.hpp"
#include "util/profiler.hpp"
#include "util/types.hpp"
#include "util/state.hpp"

#include "chunks/chunk.hpp"
#include "chunks/chunkviewer.hpp"

#include "sys/io.hpp"
#include "sys/sdlinterface.hpp"
#include "sys/system.hpp"
#include "sys/window.hpp"


#endif // _TERRAIN_HPP
