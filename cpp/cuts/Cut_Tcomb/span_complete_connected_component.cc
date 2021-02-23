#include "./Cut_Tcomb.ih"

bool Cut_Tcomb::span_complete_connected_component(vector<vector<size_t>> const &teeth,
                                                  vector<size_t> const &cc) const
{
  vector<size_t> check(d_nNodes, 0);
  
  for (auto const &el: teeth)
    for (size_t const idx : el)
      ++check[idx];
  
  if (accumulate(cbegin(check), cend(check), (size_t) 0) >= cc.size())
    return true;
  
  return false;
}