#include "./DK_min.ih"

double DK_min::update_pi (vector<vector<double>> const &x,
                          vector<int> const &seq,
                          size_t n, double pi) const
{
  double tmp_pi = pi + x[seq[n - 1]][seq[n]] - 1;

  for (size_t h = 0; h < n; ++h)
    tmp_pi += x[seq[n]][seq[h]];
    
  return tmp_pi;
}

