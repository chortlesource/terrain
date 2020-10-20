////////////////////////////////////////////////////////////////////////////
//
// terrain - biomeset.hpp
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

#ifndef _BIOMESET_HPP
#define _BIOMESET_HPP


/////////////////////////////////////////////////////////////
// BIOMESET Class
//
// The BIOMESET class processes values to clarify what biome
// should be rendered thereby returning the name of the biome


class BIOMESET {
public:
  // Public BIOMESET methods
  void initialize(STATE const& state);
  std::string const& get(double const& b, double const& m);
  void finalize();

private:
  // Private BIOMESET attributes
  bool                                         initialized;
  std::vector<double>                          ranges;
  std::map<double, BIOMELIST>                  rangemap;
  std::vector<std::tuple<double, std::string>> elev;
  std::vector<std::tuple<double, std::string>> temp;

};


#endif // _BIOMESET_HPP
