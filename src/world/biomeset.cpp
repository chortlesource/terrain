////////////////////////////////////////////////////////////////////////////
//
// terrain - biomeset.cpp
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
// Public BIOMESET methods
//


void BIOMESET::initialize(STATE const& state) {
  if(initialized)
    finalize();

  // Load the Json Data into the class
  const Json::Value b = state.biomecfg["BIOMES"];
  const Json::Value e = state.biomecfg["ELEVATION"];
  const Json::Value t = state.biomecfg["TEMPERATURE"];

  for(auto &it: b) {
    // Helper variables
    const double value  = it["VALUE"].asDouble();
    const Json::Value l = it["RANGE"];
    BIOMELIST& list     = rangemap[value];

    // Store the value
    ranges.push_back(value);

    // Store the range data
    for(auto &itr: l)
      list.push_back(std::make_tuple(itr["VALUE"].asDouble(), itr["DESC"].asString()));

  }

  for(auto &it: e)
    elev.push_back(std::make_tuple(it["VALUE"].asDouble(), it["DESC"].asString()));

  for(auto &it: t)
    temp.push_back(std::make_tuple(it["VALUE"].asDouble(), it["DESC"].asString()));

  initialized = true;
}


std::string const& BIOMESET::get(double const& b, double const& m) {
  if(!initialized)
    return "";

  // First check the elevation list
  for(auto &it: elev) {
    if(b < std::get<0>(it))
      return std::get<1>(it);
  }

  // Secondly check the range map
  for(auto &it: ranges) {
    if(b >= it) {
      BIOMELIST& list = rangemap[it];

      for(auto &itr: list) {
        if(m < std::get<0>(itr))
          return std::get<1>(itr);
      }
    }
  }

  // Lastly check the temperature list
  for(auto &it: temp) {
    if(m < std::get<0>(it))
      return std::get<1>(it);
  }

  return "";
}


void BIOMESET::finalize() {
  if(!initialized)
    return;

  initialized = false;
  rangemap.clear();
  elev.clear();
  temp.clear();
}
