#include "./DK_plus.ih"

/*
 * Extend the current sequence
 *  - extend_full   Consider all options
 *  - extend_part   Only the best option is considered
 * 
 * Parameters
 *   n       Size of incoming sequence
 *   x       LP relaxation
 *   seq     Sequence of customers
 *   DKcuts  Vector with current cuts
 */

void DK_plus::extend (size_t n, double phi, double pi,
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
    
    if (x[j][k] <= d_maxPhi - pi)
      continue;

    if (already_in_sequence(seq, n, k))
      continue;
    
    seq[n] = k;
    
    double const tmp_phi = update_phi (x, seq, n + 1, phi);
    double const tmp_pi  = update_pi  (x, seq, n + 1, pi);  
 
    // Add new DK+ cut
    if (tmp_phi > d_maxPhi + gg_eps)
    {      
      d_maxPhi = tmp_phi;
      DKcuts.push_back(create_cut(seq, n + 1));
    }
    
    extend(n + 1, tmp_phi, tmp_pi, x, seq, iComponent, DKcuts);
  }
}