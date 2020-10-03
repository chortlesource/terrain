////////////////////////////////////////////////////////////////////////////
//
// [APP] - listener.hpp
//
// Copyright (c) 2020 Christopher M. Short
//
// This file is part of [APP].
//
// [APP] is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// [APP] is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with [APP]. If not, see <https://www.gnu.org/licenses/>.
//
////////////////////////////////////////////////////////////////////////////

#ifndef _LISTENER_HPP
#define _LISTENER_HPP


/////////////////////////////////////////////////////////////
// DEPENDENCIES
//

// Standard Libraries
#include <cstdint>
#include <functional>


/////////////////////////////////////////////////////////////
// LISTENER Class
//
// The LISTENER Class is a delegate that handles the callback
// function for classes that are added to the event system


class LISTENER {
  using CALLBACK = std::function<void(EVENT const&)>;

private:
  // Private LISTENER attributes
  std::uint64_t id;
  EVENTTYPE type;
  CALLBACK callback;


public:
  // Public LISTENER methods
  LISTENER(std::uint64_t const& i, EVENTTYPE const& t, CALLBACK c) : id(i), type(t), callback(c) {};
  ~LISTENER() {};


  void operator()(EVENT const& event) const {
    // Execure the delegate function by us of ();
    callback(event);
  };


  bool operator==(LISTENER const& rhs) const noexcept {
    // Compare delegates to see if the pointers match
    return (id == rhs.id) && (type == rhs.type);
  };


  EVENTTYPE const& get_type() const noexcept {
    return type;
  };


  std::uint64_t const& get_id() const noexcept {
    return id;
  };

};


#endif // _LISTENER_HPP
