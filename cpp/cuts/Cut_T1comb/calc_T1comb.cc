#include "./Cut_T1comb.ih"

CutReturn Cut_T1comb::calc_T1comb(vector<size_t> const &T, 
                                  vector<size_t> const &H, 
                                  vector<vector<double>> const &x) const
{
  CutReturn cut;
  
  for (int const i: d_iNodes)
  {
    if (find (cbegin(T), cend(T), i) == cend(T))
    {
      for (int const el: T)
      {
        cut.add(-1, el, i);
        cut.add(-1, i, el);   
      }
    }
  }
  
  for (int const i: d_iNodes)
  {
    if (find (cbegin(H), cend(H), i) == cend(H))
    {
      for (int const el: H)
      {
        cut.add(-1, el, i);
        cut.add(-1, i, el);
      }
    }
  }

  return cut;
}