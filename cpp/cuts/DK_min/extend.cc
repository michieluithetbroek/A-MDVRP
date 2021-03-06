#include "./DK_min.ih"

/*
 * Extend the current sequence
 *  - extend_full   Consider all options
 *  - extend_part   Only the best option is considered
 * 
 * Parameters
 *   n     Size of incoming sequence
 *   x     LP relaxation
 *   seq   Sequence of customers
 */

void DK_min::extend (size_t n, double phi, double pi,
                     vector<vector<double>> const &x, 
                     vector<int> &seq,
                     vector<int> const &iComponent,
                     vector<CutReturn> &DKcuts
                    )
{
  if (n == iComponent.size())
    return;
  
  size_t const j = seq[n - 1];
  
  for (int const k: iComponent)
  {
    // Only consider promising childs
    // See equation 10 of paper Fischetti (1997)
    
    if (x[k][j] <= d_maxPhi - pi)
      continue;

    if (already_in_sequence(seq, n, k))
      continue;
    
    seq[n] = k;
    
    double const tmp_pi  = update_pi  (x, seq, n, pi);
    double const tmp_phi = update_phi (x, seq, n, phi);

    if (tmp_phi > d_maxPhi + gg_eps)
    {
      d_maxPhi = tmp_phi;
      DKcuts.emplace_back(create_cut(seq, n + 1));
    }
    
    extend(n + 1, tmp_phi, tmp_pi, x, seq, iComponent, DKcuts);
  }
}