#include "Cut_cat.ih"

/* 
 *  checks if the sequence 'cycle' is unique
 *  makes a copy to check 
 */

bool Cut_cat::is_simple(vector<int> cycle) const
{
  sort(begin(cycle), end(cycle) - 1);
  
  return adjacent_find(cbegin(cycle), cend(cycle)) == cend(cycle);
}