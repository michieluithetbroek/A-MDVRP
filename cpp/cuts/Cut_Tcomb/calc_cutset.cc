#include "./Cut_Tcomb.ih"

double Cut_Tcomb::calc_cutset(vector<size_t> const &t,
                              vector<vector<double>> const &x) const
{
  double obj =0;
  
  for (int const i: d_iNodes)
    if (find(cbegin(t), cend(t), i) == cend(t))
      for (int const el: t)
        obj += x[el][i] + x[i][el];
  
  return obj;
}