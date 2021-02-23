#include "./DK_min.ih"

double DK_min::update_phi (vector<vector<double>> const &x, 
                            vector<int> const &seq,
                            size_t n, double phi) const
{
  double tmp_phi = phi + x[seq[n]][seq[0]] + x[seq[n - 1]][seq[n]] - 1;
  
  for (size_t h = 0; h < n - 1; ++h)
    tmp_phi += x[seq[n - 1]][seq[h]]; 
  
  return tmp_phi;
}