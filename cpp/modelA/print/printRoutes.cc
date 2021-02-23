#include "./../modelA.ih"



void ModelA::printRoutes(IloCplex &cplex) const
{
  if (g_UB == 0)
  {
    cout << "No solution found yet" << endl;
    
    return;
  }
  
  vector<bool> visited(d_nNodes, false);    
  
  
  // Just to check the objective
  double totalCosts = 0;
  
  // Check all outgoing arcs
  for (int i: d_iDepots)
  {
    visited[i] = true;
    
    for (int j: d_iCustomers)
    {
      double const val = cplex.getValue(d_x[i][j]);
      
      if ((abs(val - 1) >= 0.0001))
        continue;
      
      // There is a route that starts with arc (i,j)
      // Now we follow this route
      cout << '\n' << i << " - " << j;
      vector<int> route = {i,j};
      int curr = j;
      
      while (true)
      {
        visited[curr] = true;
        
        int next = 0;
        for (; next < d_nNodes; ++next)
        {
          if ((abs(cplex.getValue(d_x[curr][next]) - 1) >= 0.0001))
            continue;
          
          curr = next; 
          cout << " - " << curr ;
          route.push_back(curr);
          
          break;
        }
        
        if (find(cbegin(d_iDepots), cend(d_iDepots), curr) != cend(d_iDepots))
        {
          if (i != curr)
            cout << " ------ INVALID ROUTE ------ ";
          
          break;
        }
      }
      
      // Add costs of the current route to totalCosts
      for (size_t idx = 0; idx < size(route) - 1; ++idx)
        totalCosts += d_cost[route[idx]][route[idx + 1]];
        
      g_finalSol.push_back(route);
    }
  }
  
  cout << "\nTotal costs: " << totalCosts << endl;

  for (bool val: visited)
    if (not val)
      throw string("Not each customer is visited! (ModelA::printRoutes)\n");
  
  
    
  // Find minimum delta required for this solution
    
  cout << "Print overview deltas of solution\n"
       << "from, to, cost, delta-th\n";
       
  for (int const idx_from: d_iCustomers)
  {
    // Sort outgoing acrs on length
    // We only consider arcs towards customers nodes
    
    vector<size_t> idx_cust_copy = d_data.d_iCustomers;
    vector<double> const &cost   = d_data.d_cost[idx_from];
    
    sort(begin(idx_cust_copy), end(idx_cust_copy), [&cost](size_t lhs, size_t rhs)
         {
           return cost[lhs] < cost[rhs]; 
         });

    bool alreadyFound = false;
    
    for (int idx_to: d_iCustomers)
    {
      if ((cplex.getValue(d_x[idx_from][idx_to]) < 1 - 0.001))
        continue;
      
      if (alreadyFound)
        throw string("This customer is already visited! (ModelA::printRoutes)");
      
      alreadyFound = true;
      
      // Find the customer index in the ordered sequence
      
      auto const it = find(cbegin(idx_cust_copy), cend(idx_cust_copy), idx_to);
      auto const n  = distance(cbegin(idx_cust_copy), it);
      
      cout << setw(5) << idx_from 
           << setw(5) << idx_to
           << setw(8) << d_data.d_cost[idx_from][idx_to] 
           << setw(5) << n << endl; 
    }
  }
}



