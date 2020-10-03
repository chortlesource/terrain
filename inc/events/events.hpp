////////////////////////////////////////////////////////////////////////////
//
// terrain - events.hpp
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

#ifndef _EVENTS_HPP
#define _EVENTS_HPP


/////////////////////////////////////////////////////////////
// EVENTTYPE Enumeration
//
// Used to define the type of events that the EVENT struct can
// containt

enum class EVENTTYPE {
  SYSTEM
};


/////////////////////////////////////////////////////////////
// SYSTEM_EVENT Struct

struct SYSTEM_EVENT {
  enum class TYPE { NONE, HALT, ERROR };
  const TYPE type;

  SYSTEM_EVENT() : type(TYPE::NONE) {};
  SYSTEM_EVENT(TYPE const& t) : type(t) {};
};


/////////////////////////////////////////////////////////////
// EVENT Struct
//
// The main EVENT struct which contains essential information

struct EVENT {
  const EVENTTYPE type;
  const SYSTEM_EVENT system_event;

  EVENT(EVENTTYPE const& t) : type(t), system_event() {};
  EVENT(EVENTTYPE const& t, SYSTEM_EVENT const& e) : type(t), system_event(e) {};
};


#endif // _EVENTS_HPP
