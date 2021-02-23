#include "./Cut_Tcomb.ih"

double Cut_Tcomb::calc_inOut(vector<size_t> const &T, 
                             size_t new_cust, 
                             vector<vector<double>> const &x, 
                             vector<size_t> const &d_iNodes) const
{
  double delta = 0;
  
  // first remove from T to new_cust;
  for (size_t const t: T)
    delta -= ( x[t][new_cust] + x[new_cust][t]);
  
  // add new_cust to outside T
  
  for (size_t const i: d_iNodes)
    if (find(cbegin(T), cend(T), i) == cend(T))
      delta += x[i][new_cust]+ x[new_cust][i];
  
  return delta;
}