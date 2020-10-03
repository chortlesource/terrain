////////////////////////////////////////////////////////////////////////////
//
// terrain - main.cpp
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

/////////////////////////////////////////////////////////////
// DEPENDENCIES
//

#include "terrain.hpp"


/////////////////////////////////////////////////////////////
// MAIN FUNCTION

int main(const int argc, const char *argv[]) {

  // Initialize the system
  std::unique_ptr<SYSTEM> system = std::make_unique<SYSTEM>();
  system->initialize(argc, argv);

  // Execute the application
  system->execute();

  // Free memory
  system->finalize();

  return 0;
}
