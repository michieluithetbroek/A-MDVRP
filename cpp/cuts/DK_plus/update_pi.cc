#include "./DK_plus.ih"

double DK_plus::update_pi (vector<vector<double>> const &x,
                           vector<int> const &seq,
                           size_t n, double pi) const
{
  double tmp_pi = pi + x[seq[n - 1]][seq[n - 2]] - 1;

  for (size_t h = 0; h < n - 1; ++h)
    tmp_pi += x[seq[h]][seq[n - 1]];
    
  return tmp_pi;
}

