////////////////////////////////////////////////////////////////////////////
//
// terrain - system.cpp
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


void SYSTEM::initialize(int const& argc, const char *argv[]) {
  // Initialize SDL
  if(SDL_Init(SDL_INIT_VIDEO) != 0) {
    DEBUG("SDL_INIT_ERROR: ", SDL_GetError());
    return;
  }

  if((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
    DEBUG("SDL_IMG_INIT_ERROR: ", IMG_GetError());
    return;
  }

  if(TTF_Init() != 0) {
    DEBUG("[SDL_TTF_INIT_ERROR]: ", TTF_GetError());
    return;
  }

  // Parse the command line data
  CLIPARSE parser(argc, argv);
  parse(parser);

  // Allocate memory for the state components
  state.window        = std::make_shared<WINDOW>();
  state.io            = std::make_shared<IO>();
  state.timer         = std::make_shared<TIMER>();
  state.profiler      = std::make_shared<PROFILER>();
  state.worldviewer   = std::make_shared<WORLDVIEWER>();
  state.sdlinterface  = std::make_shared<SDLINTERFACE>();

  // First load the application configuration
  if(!state.io->load_json("./asset/init.json", state.config))
    use_default_config();

  // Initialize the state components
  state.window->initialize(state);
  state.worldviewer->initialize(state);
  state.status  = STATUS::RUN;

  initialized   = true;
}


void SYSTEM::execute() {
  if(!initialized || !state.run)
    return;

  state.timer->start();

  double rate    = 0.01;
  double elapsed = 0.0;

  while(state.status != STATUS::EXIT) {
    // Update the timer and seek delta
    state.timer->update();
    double delta = state.timer->delta();

    if(delta > 0.60) delta = 0.60;
    elapsed += delta;

    // Fix the timestep
    while(elapsed >= rate) {
      state.window->update();          // Refresh the display
      state.sdlinterface->poll(state); // poll events
      state.worldviewer->update(state);
      state.profiler->fps();           // Profile the FPS
      elapsed -= rate;
    }

    state.profiler->ups();      // Profile the UPS
    state.profiler->update(state.timer->delta());   // Update the profiler
  };

}


void SYSTEM::finalize() {
  if(!initialized || !state.run)
    return;

  initialized = false;

  // Free the shared pointers
  state.worldviewer->finalize();
  state.window->finalize();

  state.sdlinterface = nullptr;
  state.worldviewer  = nullptr;
  state.profiler     = nullptr;
  state.timer        = nullptr;
  state.io           = nullptr;
  state.window       = nullptr;
}


/////////////////////////////////////////////////////////////
// Private SYSTEM class methods
//

void SYSTEM::parse(CLIPARSE& p) {
  if(p.using_opt("h")) {
    std::cout << _APP_NAME << " [v" << _APP_VERSION << "] copyright (c) " << _APP_AUTHOR << std::endl;
    return;
  }

  if(p.size() >= 3) {
    // Fetch seed data
    std::string seedstr  = p.using_opt_value("-s");
    if(!seedstr.empty())
      state.seed = static_cast<unsigned int>(std::stoul(seedstr));
  }

  state.run = true;
}


void SYSTEM::use_default_config() {
  // Initialize the default configuration
  state.config["INIT"]["APP_WIDTH"]     = 1080;
  state.config["INIT"]["APP_HEIGHT"]    = 720;
  state.config["TILES"]["TILE_WIDTH"]   = 16;
  state.config["TILES"]["TILE_HEIGHT"]  = 16;
  state.config["TILES"]["TILE_PATH"]    = "./asset/gfx/tiles.png";
  state.config["WORLD"]["WORLD_WIDTH"]  = 128;
  state.config["WORLD"]["WORLD_HEIGHT"] = 128;
  state.config["WORLD"]["WORLD_RES"]    = 5;
}
