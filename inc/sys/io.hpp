////////////////////////////////////////////////////////////////////////////
//
// terrain - io.hpp
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

#ifndef _IO_HPP
#define _IO_HPP


/////////////////////////////////////////////////////////////
// IO Class
//
// The IO class handles asset loading within the application.


class IO {
public:
  // Public IO methods

  bool load_json(std::string const& path, Json::Value& value) {
    if(fexist(path)) {
      std::ifstream input(path, std::ifstream::binary);
      if(input.is_open()){
        input >> value;
        input.close();
        return true;
      }
    }
    return false; // By default fail
  }

private:
  // Private IO methods

  bool fexist(std::string const& path) const noexcept {
    // Identify if file exists and return true if exists
    namespace fs = std::experimental::filesystem;
    return (fs::exists(fs::path(path)) && fs::is_regular_file(fs::path(path)));
  }

};


#endif // _IO_HPP
