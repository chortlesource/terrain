////////////////////////////////////////////////////////////////////////////
//
// terrain - types.hpp
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

#ifndef _TYPES_HPP
#define _TYPES_HPP


/////////////////////////////////////////////////////////////
// FORWARDS
//

class SYSTEM;
class WINDOW;
class IO;
class TIMER;
class PROFILER;
class TILESET;
class WORLD;
class WORLDVIEWER;
class SDLINTERFACE;


/////////////////////////////////////////////////////////////
// Type definitions
//
// Used in an effort to make code more readable but perhaps
// this just makes things more opaque...

using SYSTEM_PTR        = std::unique_ptr<SYSTEM>;
using WINDOW_PTR        = std::shared_ptr<WINDOW>;
using IO_PTR            = std::shared_ptr<IO>;
using JSON_PTR          = std::shared_ptr<Json::Value>;
using TIMER_PTR         = std::shared_ptr<TIMER>;
using PROFILER_PTR      = std::shared_ptr<PROFILER>;
using WORLD_PTR         = std::shared_ptr<WORLD>;
using WORLDVIEWER_PTR   = std::shared_ptr<WORLDVIEWER>;
using SDLINTER_PTR      = std::shared_ptr<SDLINTERFACE>;
using SDLWINDOW_PTR     = std::shared_ptr<SDL_Window>;
using SDLTEXTURE_PTR    = std::shared_ptr<SDL_Texture>;
using SDLRENDER_PTR     = std::shared_ptr<SDL_Renderer>;
using NOISEMAP          = std::vector<std::vector<double>>;
using TILEMAP           = std::map<std::string, SDL_Rect>;


/////////////////////////////////////////////////////////////
// STATUS Enumeration
//
// Used to indicate the current status of the application

enum class STATUS { INIT, RUN, EXIT };


#endif // _TYPES_HPP
