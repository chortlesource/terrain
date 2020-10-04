////////////////////////////////////////////////////////////////////////////
//
// [APP] - eventmanager.hpp
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

#ifndef _EVENTMANAGER_HPP
#define _EVENTMANAGER_HPP


/////////////////////////////////////////////////////////////
// DEPENDENCIES
//

// Standard Libraries
#include <cstdint>
#include <algorithm>
#include <vector>
#include <map>
#include <mutex>


/////////////////////////////////////////////////////////////
// EVENTMANAGER Class
//
// EVENTMANAGER class is a container for application events
// and delegates (LISTENERS) for the management and execution
// of events throughout the execution of the application


class EVENTMANAGER {
  using LISTENERLIST = std::vector<LISTENER>;
  using LISTENERMAP  = std::map<EVENTTYPE, LISTENERLIST>;
  using U64          = std::uint64_t;
  using MUTEX        = std::mutex;

private:
  // Private EVENTMANAGER attributes
  MUTEX               mute;
  U64                 ids;
  LISTENERMAP         listeners;
  EVENTQUEUE<EVENT>   events;

public:
  EVENTMANAGER() : ids(0), listeners(), events() {};
  ~EVENTMANAGER() {};

  /////////////////////////////////////////////////////////////
  // new_listener_id() - Obtain new LISTENER id

  U64 const& new_listener_id() {
    std::scoped_lock<std::mutex> lock(mute);
    return ++ids;
  }

  /////////////////////////////////////////////////////////////
  // add_listener(l) - Add new LISTENER

  bool add_listener(LISTENER const& l) {
    std::scoped_lock<std::mutex> lock(mute);

    // Retrieve or create the list
    LISTENERLIST& list = listeners[l.get_type()];
    // Prevent duplicates
    for(const auto &it : list)
      if(l == it) return false;

    list.push_back(l);
    return true;
  }

  /////////////////////////////////////////////////////////////
  // rem_listener(l) - Remove a LISTENER by ID

  bool rem_listener(LISTENER const& l) {
    std::scoped_lock<std::mutex> lock(mute);

    auto find_list = listeners.find(l.get_type());
    if(find_list != listeners.end()) {
      LISTENERLIST& list = find_list->second;
      for(auto it = list.begin(); it != list.end(); ++it) {
        if(l == (*it)) {
          list.erase(it);
          return true;
        }
      }
    }
    return false;
  }

  /////////////////////////////////////////////////////////////
  // trigger_event(l) - Remove a LISTENER by ID


  void trigger_event(EVENT const& event) {
    std::scoped_lock<std::mutex> lock(mute);

    // Ascertain this type of event exists
    auto find_list = listeners.find(event.type);
    if(find_list != listeners.end()) {
      const LISTENERLIST& list = find_list->second;

      // Call the method for all delegates registered
      for(const auto &it : list)
        it(event);
    }
  }

  /////////////////////////////////////////////////////////////
  // send_event(event) - Send an event with normal priority

  void send(EVENT const& event) {
    events.push(event);
  }

  /////////////////////////////////////////////////////////////
  // update() - Update the event manager

  void update() {
    std::scoped_lock<std::mutex> lock(mute);

    // We process all events until the queue is empty
    if(!events.empty()) {

      // Ascertain this type of event exists
      auto find_list = listeners.find(events.front().type);
      if(find_list != listeners.end()) {

        // Obtain the list of listeners
        const LISTENERLIST& list = find_list->second;

        // Call the method for all delegates registered
        for(const auto &it : list)
          it(events.front());

        // Pop the event from the queue
        events.pop();
      }

    }
  }

};


#endif // _EVENTMANAGER_HPP
