////////////////////////////////////////////////////////////////////////////
//
// terrain - window.hpp
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

#ifndef _WINDOW_HPP
#define _WINDOW_HPP


/////////////////////////////////////////////////////////////
// WINDOW Class
//
// The WINDOW Class is a container for the SDL_Window and
// SDL_Renderer for garbage collection and convenience


class WINDOW {

public:
  // Public WINDOW methods
  void initialize();
  void update();
  void finalize();

  SDL_Window*   get_window();
  SDL_Renderer* get_render();

private:
  // Private WINDOW attributes
  bool          initialized;
  SDLWINDOW_PTR windowptr;
  SDLRENDER_PTR renderptr;

};


#endif // _WINDOW_HPP
