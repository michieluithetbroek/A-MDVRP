#include "Cut_cat.ih"

/* 
 * checks if edge info_u is incompatible with v (and vice versa)
 * 
 * TODO This should be a function of the namespace graphFunctions
 */

bool Cut_cat::incompatible(pair<int, int> const &info_v,
                           pair<int, int> const &info_u) const
{
  
  // case (i):
  if ( info_v.first >= d_nDepots and info_v.second >= d_nDepots)
  {
    if (info_v.first == info_u.first)
      return true;
    
    if (info_v.second == info_u.second)
      return true;
    
    if (info_v.second == info_u.first and info_v.first == info_u.second)
      return true;
  }
  
  // case (ii-a)
  else if (info_v.first < d_nDepots and info_v.second >= d_nDepots)
  {
    if (info_u.second == info_v.second)
      return true;
    if (info_u.first == info_v.second and info_u.second < d_nDepots and info_u.second != info_v.first)
      return true; 
  }
  
  // case (ii-b)
  else if (info_v.first >= d_nDepots and info_v.second < d_nDepots)
  {
    if (info_u.first == info_v.first)
      return true;
    
    if (info_u.second == info_v.first and info_u.first < d_nDepots and info_u.first != info_v.second)
      return true; 
  }
  
  return false;
}