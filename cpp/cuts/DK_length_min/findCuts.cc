#include "./DK_length_min.ih"

/*
 * Assumptions
 *  - There are no subtours anymore
 *  - No tours with single customer between two different depots
 *  - The DK cuts without depots are already added (does the order matter?)
 * 
 * Observations
 *  - Only check sequences within the same connected component
 *  - Only check sequences with first/last customer connected to depot
 *  - Only connected components with two different depots
 * 
 * TODO
 *  - We skip all components with a single customer
 *  - We search the maximum cut per component
 *  - We find the components seperately for DK- and DK+
 */

vector<CutReturn> DK_length_min::findCuts (vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  // Get the components
  // The vector only includes customer indices
  // For each component: find customers i,l that are connected to a depot
  
  auto const components = graphFunctions::LEMON_get_connected_components(x);
 
  for (auto const &iComponent: components)
  {
    if (iComponent.size() == 1)
      continue;
    
    vector<int> sequence(iComponent.size() - 1, -1);
    
    for (int const i: iComponent)
    {
      if (not connected_from_depot(x, i))
        continue;
          
      for (int const l: iComponent)
      {
        if (i == l)
          continue;
        
        if (not connected_to_depot(x, l))
          continue;

        // TODO ALERT NOTICE waarom dit???
//         if (sep_dep < 1 + gg_eps)
//           continue;
        
        // 
        // Initialize alpha and beta
        //
        
        double alpha = x[l][i];
        double beta  = x[l][i];
        
        for (size_t d = 0; d < d_nDepots; ++d)
        {
          alpha += x[d][i];
          beta  += x[l][d];
        }

        
        // 
        // Start recursion
        //
        
        d_maxPhi    = 0;
        sequence[0] = i;
        
        double const phi = sum_depots(x, l, i) + 2 * x[l][i] + x[i][l] - 2;
        
        if (phi > gg_eps)
          cuts.emplace_back(create_cut(sequence, 1, l));    
        
        extend (1, l, phi, alpha, beta, x, sequence, iComponent, cuts);
      }
    }
  }

  return cuts;
}