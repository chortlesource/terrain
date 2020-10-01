////////////////////////////////////////////////////////////////////////////
//
// terrain - window.cpp
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

void WINDOW::initialize() {
  // Initialize the window
  std::string title = _APP_NAME + " - " + _APP_VERSION;
  WINDOW_PTR tempwin(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    _APP_WIDTH, _APP_HEIGHT, SDL_WINDOW_SHOWN), [=](SDL_Window *window){ SDL_DestroyWindow(window); });

  windowptr = tempwin;
  if(windowptr == nullptr) {
    ERROR("[SDL_WINDOW_ERROR]: ", SDL_GetError());
    return;
  }

  // Initialize the renderer
  RENDER_PTR temprender(SDL_CreateRenderer(windowptr.get(), -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC), [=](SDL_Renderer *render) { SDL_DestroyRenderer(render); });

  renderptr = temprender;
  if(renderptr == nullptr) {
    DEBUG("[SDL_RENDER_ERROR]: ", SDL_GetError());
    windowptr = nullptr;
    return;
  }

  SDL_RenderSetLogicalSize(renderptr.get(), _APP_WIDTH, _APP_HEIGHT);
  SDL_SetRenderDrawColor(renderptr.get(), 255, 255, 255, 255);
  SDL_RenderClear(renderptr.get());
  SDL_RenderPresent(renderptr.get());
}


void WINDOW::update() {
  if(!initialized)
    return;

  SDL_RenderPresent(renderptr.get());
  SDL_SetRenderDrawColor(renderptr.get(), 255, 255, 255, 255);
  SDL_RenderClear(renderptr.get());
}


void WINDOW::finalize() {
  initialized = false;

  renderptr = nullptr;
  windowptr = nullptr;
}


SDL_Window*   WINDOW::get_window() { return windowptr.get(); }
SDL_Renderer* WINDOW::get_render() { return renderptr.get(); }
