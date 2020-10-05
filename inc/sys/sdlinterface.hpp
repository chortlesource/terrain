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
// SDLINTERFACE Class
//
// The SDLINTERFACE interprets SDL Events


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
        case SDL_KEYDOWN:
          switch(event.key.keysym.sym) {
            case SDLK_d:
            case SDLK_RIGHT:
              state.pos_x -= 10;
              break;
            case SDLK_s:
            case SDLK_DOWN:
              state.pos_y -= 10;
              break;
            case SDLK_a:
            case SDLK_LEFT:
              state.pos_x += 10;
              break;
            case SDLK_w:
            case SDLK_UP:
              state.pos_y += 10;
              break;
            case SDLK_e:
            case SDLK_PERIOD:
              state.zoom += 10;
              break;
            case SDLK_q:
            case SDLK_COMMA:
              state.zoom -= 10;
              break;
            case SDLK_z:
            case SDLK_QUESTION:
              state.zoom = 0;
              break;
            default:
              break;
          };
          break;
        default:
          break;
      };
    }
  }
};


#endif // _SDLINTERFACE_HPP
