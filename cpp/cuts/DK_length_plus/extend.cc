#include "./DK_length_plus.ih"

/*
 * Extend the current sequence
 *  - extend_full   Consider all options
 *  - extend_part   Only the best option is considered
 * 
 * NOTICE Remark the new pruning rule!
 * Not sure whether it is tight or not but it seems (?) to work
 * 
 * Parameters
 *   n     Size of incoming sequence (excluding customer l!)
 *   k     Last customer that is fixed (not included in seq)
 *   lhs   The reusable part of the LHS
 *   x     LP relaxation
 *   seq   Sequence of customers
 * 
 * Optimization
 *   - The 'fromDepot' could be calculated once for every customer node
 */

void DK_length_plus::extend (size_t n, int k, double phi,
                            double alpha, double beta,
                            vector<vector<double>> const &x,
                            vector<int> &seq,
                            vector<int> const &iComponent,
                            vector<CutReturn> &cuts
                           )
{
  // The two because we already have n+1 customers in the sequence
  // length(sequence) + customer j == n + 1
  // Thus after extension we have n + 2
  
  if (n + 2 >= d_tourMin)
    return;
  
  if (n + 1 == iComponent.size())
    return;  
  
  size_t const i = seq[0];
  size_t const j = seq[n - 1];
  
  // Insert new customer b at position n
  for (int const b: iComponent)
  {
    if (already_in_sequence(seq, n, b, k))
      continue;
    
    seq[n] = b;
    
    // Pruning
    // This can avoid fromDepot
    
    if (x[b][j] <= d_maxPhi + alpha + beta + x[k][j] - phi - 2)
      continue;
    
    double fromDepot = 0;
    
    for (size_t d = 0; d < d_nDepots; ++d)
      fromDepot += x[d][b];
    
    if (x[b][j] - fromDepot <= d_maxPhi + alpha + beta + x[k][j] - phi - 2)
      continue;
    
    double const next_alpha = alpha + x[i][b];
    double const next_beta  = beta + x[b][k];
    double const next_phi   = update_phi (x, seq, n + 1, phi, k);
    
    if (next_alpha - 1 > gg_eps or next_beta - 1 > gg_eps) 
    {
      cout << next_alpha << " <- alpha \n" << next_beta << " <- beta \n";
      throw string("Alpha/beta too large (DK_length_plus::extend.cc)");
    }
    
    // Violation found?
    if (next_phi > gg_eps)
    {      
      d_maxPhi = max(d_maxPhi, next_phi);
      cuts.emplace_back(create_cut(seq, n + 1, k));
    }
    
    extend (n + 1, k, next_phi, next_alpha, next_beta, x, seq, iComponent, cuts);
  }
}
