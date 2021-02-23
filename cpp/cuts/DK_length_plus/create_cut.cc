#include "./DK_length_plus.ih"

/*
 * 
 */

CutReturn DK_length_plus::create_cut(vector<int> const &seq, size_t n, int l) const
{
  CutReturn cut;
  cut.rhs = n + 1;
  
  size_t const i = seq[0];
  size_t const k = seq[n - 1];
  
  cut.add(2, i, l);
  cut.add(1, l, k);
  
  for (size_t h = 1; h < n; ++h)
    cut.add(2, i, seq[h]);
  
  for (size_t h = 1; h < n; ++h)
    cut.add(1, seq[h], seq[h - 1]);
  
  for (size_t h = 1; h < n - 1; ++h)
    for (size_t h2 = h + 1; h2 < n; ++h2)
      cut.add(1, seq[h], seq[h2]);
  
  for (size_t h = 1; h < n; ++h)  
    cut.add(1, seq[h], l);
  
  // Add depots
  for (size_t idx = 0; idx < d_nDepots; ++idx)
  {
    cut.add(1, i, idx);
    cut.add(1, idx, l);
  }

  return cut;
}
