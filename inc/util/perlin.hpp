////////////////////////////////////////////////////////////////////////////
//
// terrain - perlin.hpp
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

#ifndef _PERLIN_HPP
#define _PERLIN_HPP


/////////////////////////////////////////////////////////////
// PERLIN Class
//
// PERLIN class is a header only file class that will generate
// perlin noise for use within applications.
//
// ATTRIBUTION
//
// This class is an implementation of the improved perlin
// function in C++ translated from the implementation in Java.
// The original implementation is copyright Ken Perlin (c) 2002
// and available at: http://mrl.nyu.edu/~perlin/noise/


template<class Double>
class BaseNoise {

public:
  // Public Decl
  using value_type = Double;

private:
  std::uint8_t p[512];

  ///////////////////////////////////////////////////////
  // NOISE CALCULATION()
  //
  // Constructor for an empty container


  static constexpr value_type fade(value_type t) noexcept {
    return t * t * t * (t * (t * 6 - 15) + 10);
  }


  static constexpr value_type lerp(value_type t, value_type a, value_type b) noexcept {
    return a + t * (b - a);
  }


  static constexpr value_type grad(std::uint8_t hash, value_type x, value_type y, value_type z) noexcept {
    const std::uint8_t h = hash & 15;
    const value_type u = h < 8 ? x : y;
    const value_type v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
  }


  static constexpr value_type weight(std::int32_t octaves) noexcept {
    value_type weight = 0;
    value_type exp = 1;

    for(std::uint32_t i = 0; i < octaves; i++) {
      weight += exp;
      exp /= 2;
    }

    return weight;
  }


public:
  BaseNoise(unsigned int _seed = std::default_random_engine::default_seed) {
    seed(_seed);
  }

  void seed(unsigned int const& _seed) {
    for(unsigned int i = 0; i < 256; ++i)
      p[i] = i;

    std::shuffle(std::begin(p), std::begin(p) + 256, std::default_random_engine(_seed));

    for(unsigned int i = 0; i < 256; ++i)
      p[256 + i] = p[i];
  }

  ///////////////////////////////////////////////////////
  // noise(x, y, z)
  //
  // Calculates noise between the ranges of -1, 1

  value_type noise(value_type x, value_type y, value_type z) const noexcept {
    const std::int32_t X = static_cast<std::int32_t>(std::floor(x)) & 255;
    const std::int32_t Y = static_cast<std::int32_t>(std::floor(y)) & 255;
    const std::int32_t Z = static_cast<std::int32_t>(std::floor(z)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    const value_type u = fade(x);
    const value_type v = fade(y);
    const value_type w = fade(z);

    const std::int32_t A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
    const std::int32_t B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z),
      grad(p[BA], x - 1, y, z)),
      lerp(u, grad(p[AB], x, y - 1, z),
      grad(p[BB], x - 1, y - 1, z))),
      lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),
      grad(p[BA + 1], x - 1, y, z - 1)),
      lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
      grad(p[BB + 1], x - 1, y - 1, z - 1))));
  }

  ///////////////////////////////////////////////////////
  // noise_0_1(x, y, z)
  //
  // Calculates noise between the ranges of 0, 1

  value_type noise_0_1(value_type x, value_type y, value_type z) const noexcept {
    return noise(x, y, z) * value_type(0.5) + value_type(0.5);
  }

  ///////////////////////////////////////////////////////
  // octave_noise(x, y, z, octaves)
  //
  // Calculate octave noise between the ranges of -1, 1

  value_type octave_noise(value_type x, value_type y, value_type z, std::uint32_t octaves) const noexcept {
    value_type result = 0;
    value_type exp = 1;

    for(std::uint32_t i = 0; i < octaves; i++) {
      result += noise(x, y, z) * exp;
      x *= 2;
      y *= 2;
      z *= 2;
      exp /= 2;
    }

    return result / weight(octaves);
  }

  ///////////////////////////////////////////////////////
  // octave_noise_0_1(x, y, z, octaves)
  //
  // Calculate octave noise between the ranges of 0, 1

  value_type octave_noise_0_1(value_type x, value_type y, value_type z, std::uint32_t octaves) const noexcept {
    value_type result = 0;
    value_type exp = 1;

    for(std::uint32_t i = 0; i < octaves; i++) {
      result += noise(x, y, z) * exp;
      x *= 2;
      y *= 2;
      z *= 2;
      exp /= 2;
    }

    return std::clamp<value_type>(result * value_type(0.5) + value_type(0.5), 0, 1);
  }

};


using PERLIN = BaseNoise<double>;

#endif // _PERLIN_HPP
