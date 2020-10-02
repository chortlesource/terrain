////////////////////////////////////////////////////////////////////////////
//
// terrain - sdlinterface.hpp
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

#ifndef _SDLINTERFACE_HPP
#define _SDLINTERFACE_HPP


/////////////////////////////////////////////////////////////
// DEPENDENCIES
//

// Standard Libraries


/////////////////////////////////////////////////////////////
// SDLINTERFACE Class
//
// The SDLINTERFACE interprets SDL Events and does something
// about them


class SDLINTERFACE {
private:
  // Private SDLINTERFACE attributes
  SDL_Event event;

public:
  // Public SDLINTERFACE methods
  void poll(STATE& state) {
    if(SDL_PollEvent(&event)) {
      switch(event.type) {
        case SDL_WINDOWEVENT:
          switch(event.window.event) {
            case SDL_WINDOWEVENT_CLOSE:
              state.status = STATUS::EXIT;
              break;
            default:
              break;
          };
        default:
          break;
      };
    }
  }
};


#endif // _SDLINTERFACE_HPP
