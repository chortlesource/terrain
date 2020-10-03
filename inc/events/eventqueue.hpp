////////////////////////////////////////////////////////////////////////////
//
// terrain - eventqueue.hpp
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

#ifndef _EVENTQUEUE_HPP
#define _EVENTQUEUE_HPP


/////////////////////////////////////////////////////////////
// DEPENDENCIES
//

// Standard Libraries
#include <queue>
#include <mutex>


/////////////////////////////////////////////////////////////
// EVENTQUEUE Class
//
// The EVENTQUEUE is a threadsafe wrapper for std::queue and
// is used by the EVENTMANAGER to manage events.


template<typename T>
class EVENTQUEUE {

private:
  mutable std::mutex mute;
  std::queue<T> queue;

public:
  EVENTQUEUE() {};
  EVENTQUEUE(EVENTQUEUE const& rhs) : queue(rhs.queue) {};
  EVENTQUEUE(EVENTQUEUE&& rhs) noexcept {
    std::scoped_lock<std::mutex> lock(mute);
    std::scoped_lock<std::mutex> lock_rhs(rhs.mute);

    std::swap(queue, rhs.queue);
  };

  ~EVENTQUEUE() {};


  EVENTQUEUE& operator=(EVENTQUEUE const& rhs) {
    std::scoped_lock<std::mutex> lock(mute);

    queue = rhs.queue;
    return *this;
  }


  EVENTQUEUE& operator=(EVENTQUEUE&& rhs) noexcept {
    std::scoped_lock<std::mutex> lock(mute);
    std::scoped_lock<std::mutex> lock_rhs(rhs.mute);

    std::swap(queue, rhs.queue);
    return *this;
  }


  void emplace(T const& value) {
    std::scoped_lock<std::mutex> lock(mute);
    queue.emplace(value);
  }


  bool empty() const {
    return queue.empty();
  }


  T& front() {
    std::scoped_lock<std::mutex> lock(mute);
    return queue.front();
  }


  T const& front() const {
    return queue.front();
  }


  T& back() {
    std::scoped_lock<std::mutex> lock(mute);
    return queue.back();
  }


  T const& back() const {
    return queue.back();
  }


  void pop() {
    std::scoped_lock<std::mutex> lock(mute);
    queue.pop();
  }


  void push(T const& value) {
    std::scoped_lock<std::mutex> lock(mute);
    queue.push(value);
  }


  std::size_t const& size() {
    std::scoped_lock<std::mutex> lock(mute);
    return queue.size();
  }


  void swap(EVENTQUEUE& value) {
    std::scoped_lock<std::mutex> lock(mute);
    std::scoped_lock<std::mutex> lock_value(value.mute);

    queue.swap(value.queue);
  }

};


#endif // _EVENTQUEUE_HPP
