#include "./data.ih"

/*
 * Return a vector that can be used by the lysgard library
 * That is, a zero followed by the customer demands
 */

vector<int> Data::lysgard_demand() const
{
  vector<int> tmp_vector({0});
  tmp_vector.reserve(d_nCustomers + 1);
  
  for (int const idx: d_iCustomers)
    tmp_vector.push_back(d_demands[idx]);
    
  return tmp_vector;
}