#include "./Cut_Tcomb.ih"

CutReturn Cut_Tcomb::create_Tcomb(vector<vector<size_t>> const &tooth,
                                  vector<size_t> const &H) const
{
  CutReturn cut;
  
  for (vector<size_t> const &t: tooth)
  {
    for (int const i: d_iNodes)
    {
      if (find(cbegin(t), cend(t), i) == cend(t))
      {
        for (int const el: t)
        {
          cut.add(-1, el, i);
          cut.add(-1, i, el);
        }
      }
    }
  }
  
  for (int const i: d_iNodes)
  {
    if (find(cbegin(H), cend(H), i) == cend(H))
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