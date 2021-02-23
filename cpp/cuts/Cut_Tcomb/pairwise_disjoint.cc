#include "./Cut_Tcomb.ih"

// also checks if empty
bool Cut_Tcomb::pairwise_disjoint(vector<vector<size_t>> const &tooth) const
{
  for (int i = 0, n = tooth.size() - 1; i != n; ++i)
  {
    for (int j = i + 1, m = tooth.size(); j != m; ++j)
    {
      vector<size_t> const &teeth1 = tooth[i];
      vector<size_t> const &teeth2 = tooth[j];
      
      if (teeth1.size() <= 1 or teeth2.size() <= 1)
        return false;
      
      for (auto el: teeth1)
        if (find(begin(teeth2), cend(teeth2), el) != cend(teeth2))
          return false;
    }
  }
  
  return true;
}