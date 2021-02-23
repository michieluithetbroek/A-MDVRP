#include "./DK_plus.ih"

double DK_plus::update_phi (vector<vector<double>> const &x, 
                            vector<int> const &seq,
                            size_t n, double phi) const
{
  double tmp_phi = phi - 1
                   + x[seq[0]][seq[n - 1]] 
                   + x[seq[n - 1]][seq[n - 2]];
  
  for (size_t h = 0; h < n - 2; ++h)
    tmp_phi += x[seq[h]][seq[n - 2]];
  
  return tmp_phi;
}