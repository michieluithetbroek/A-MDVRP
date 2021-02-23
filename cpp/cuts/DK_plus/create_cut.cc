#include "./DK_plus.ih"

/*
 * 
 */

CutReturn DK_plus::create_cut (vector<int> const &seq, size_t n) const
{
  size_t const i = seq[0];
  size_t const k = seq[n - 1];
  
  CutReturn cut;
  
  cut.rhs = n - 1;
  
  cut.add(1, i, k);
  
  for (size_t h = 1; h < n; ++h)
    cut.add(1, seq[h], seq[h - 1]);

  for (size_t h = 1; h < n - 1; ++h)
    cut.add(2, i, seq[h]);
  
  for (size_t h = 1; h < n - 2; ++h)
    for (size_t h2 = h + 1; h2 < n - 1; ++h2)
      cut.add(1, seq[h], seq[h2]);
  
  return cut;
}