#include "./DK_length_min.ih"

/*
 * 
 */

CutReturn DK_length_min::create_cut(vector<int> const &seq, size_t n, int l) const
{
  CutReturn cut;
  cut.rhs = n + 1;
  
  size_t const i = seq[0];
  size_t const k = seq[n - 1];
  
  cut.add(2, l, i);
  cut.add(1, k, l);
  
  for (size_t h = 1; h < n; ++h)
    cut.add(2, seq[h], i);
  
  for (size_t h = 1; h < n; ++h)
    cut.add(1, seq[h - 1], seq[h]);
  
  for (size_t h = 1; h < n - 1; ++h)
    for (size_t h2 = h + 1; h2 < n; ++h2)
      cut.add(1, seq[h2], seq[h]);
  
  for (size_t h = 1; h < n; ++h)  
    cut.add(1, l, seq[h]);
  
  // Add depots
  for (size_t idx = 0; idx < d_nDepots; ++idx)
  {
    cut.add(1, idx, i);
    cut.add(1, l, idx);
  }
  
  return cut;
}
