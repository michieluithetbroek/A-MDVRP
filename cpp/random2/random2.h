#pragma once

#include <vector>
#include <random>

namespace random2
{
  extern std::default_random_engine d_generator;
  
  void setSeed(unsigned seed);
  std::default_random_engine &engine();
  
  std::vector<size_t> random_indices(size_t min, size_t max);
  std::vector<size_t> random_indices(size_t min, size_t max, size_t n);
  
  template<typename type>
  type runif_int (type min, type max)
  {
    std::uniform_int_distribution<type> distribution(min, max);
    return distribution(d_generator);
  };
  
  template<typename type>
  type runif_real (type min, type max)
  {
    std::uniform_real_distribution<type> distribution(min, max);
    return distribution(d_generator);
  };
}
