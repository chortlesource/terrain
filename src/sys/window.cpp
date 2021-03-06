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

void WINDOW::initialize(STATE const& state) {
  // Initialize the window
  std::string title       = _APP_NAME + " - " + _APP_VERSION;
  const int window_width  = state.config["INIT"]["APP_WIDTH"].asInt();
  const int window_height = state.config["INIT"]["APP_HEIGHT"].asInt();

  SDLWINDOW_PTR tempwin(SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
    window_width, window_height, SDL_WINDOW_SHOWN), [=](SDL_Window *window){ SDL_DestroyWindow(window); });

  windowptr = tempwin;
  if(windowptr == nullptr) {
    ERROR("[SDL_WINDOW_ERROR]: ", SDL_GetError());
    return;
  }

  // Initialize the renderer
  SDLRENDER_PTR temprender(SDL_CreateRenderer(windowptr.get(), -1, SDL_RENDERER_ACCELERATED |
    SDL_RENDERER_PRESENTVSYNC), [=](SDL_Renderer *render) { SDL_DestroyRenderer(render); });

  renderptr = temprender;
  if(renderptr == nullptr) {
    DEBUG("[SDL_RENDER_ERROR]: ", SDL_GetError());
    windowptr = nullptr;
    return;
  }

  SDLTEXTURE_PTR temptex(IMG_LoadTexture(renderptr.get(), "./asset/gfx/scanline.png"), [=](SDL_Texture *t){ SDL_DestroyTexture(t); });
  scanline = temptex;

  SDL_SetTextureBlendMode(scanline.get(), SDL_BLENDMODE_BLEND);
  SDL_SetTextureAlphaMod(scanline.get(), 30);


  SDL_RenderSetLogicalSize(renderptr.get(), window_width, window_height);
  SDL_SetRenderDrawColor(renderptr.get(), 255, 255, 255, 255);
  SDL_RenderClear(renderptr.get());
  SDL_RenderPresent(renderptr.get());

  initialized = true;
}


void WINDOW::update() {
  if(!initialized)
    return;

  SDL_RenderCopy(renderptr.get(), scanline.get(), NULL, NULL);
  SDL_RenderPresent(renderptr.get());
  SDL_SetRenderDrawColor(renderptr.get(), 0, 0, 0, 255);
  SDL_RenderClear(renderptr.get());
}


void WINDOW::finalize() {
  initialized = false;

  renderptr = nullptr;
  windowptr = nullptr;
}


SDL_Window*   WINDOW::get_window() { return windowptr.get(); }
SDL_Renderer* WINDOW::get_render() { return renderptr.get(); }
