#include "./DK_depot_min.ih"

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

vector<CutReturn> DK_depot_min::findCuts (vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  // Get the components
  // The vector only includes customer indices
  // For each component: find customers i,l that are connected to a depot
  
  auto const components = graphFunctions::LEMON_get_connected_components(x);
  
  for (auto const &iComponent: components)
  {
    // Tour between depots (via single customer)
    if (iComponent.size() == 1)
    {
      int const cust = iComponent[0];
        
      for (int d1: d_iDepots)
      {
        for (int d2: d_iDepots)
        {
          if (d1 == d2)
            continue;
            
          if (x[d1][cust] + x[cust][d2] > 1 + d_eps)
          {
            CutReturn cut;
            cut.add(1, d1, cust);
            cut.add(1, cust, d2);
            cut.rhs = 1;
            
            cuts.push_back(cut);
          }
        }
      }
      
      if (not cuts.empty())
        return cuts;
      
      continue;
    } 
    
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

        double const sep_dep = seperate_depots(x, l, i);
        
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
        
        double const phi = sep_dep + 2 * x[l][i] + x[i][l] - 2;
        
        if (phi > gg_eps)
          cuts.emplace_back(create_cut(x, sequence, 1, l));    
        
        extend (1, l, phi, alpha, beta, x, sequence, iComponent, cuts);
      }
    }
  }

  return cuts;
}
