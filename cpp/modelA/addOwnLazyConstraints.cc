#include "modelA.ih"

/*
 * Add constraints that remove small subtours to the base model
 * 
 * For each customer i, we find the cost of all subtours of a given
 * size n in which customer i is present. For the nCuts_nx cheapest
 * subtours a cut is added to the pool of lazy constraints.
 * 
 */

void ModelA::addOwnLazyConstraints(IloCplex &cplex)
{
  if (g_onlyRoot)
    return;
  /*
   * Until which instance size do we add the constraints
   * to remove subtours to the base model
   * 
   * nCuts_nx: How many cuts do we add per customer
   */
  
  size_t constexpr maxCustomers_n3 = 250;
  size_t constexpr maxCustomers_n4 = 100;
  
  int constexpr nCuts_n3 = 5;
  int constexpr nCuts_n4 = 5;
  
  
  
  
  
  //---------------------------------
  // --- Remove subtours of n = 3 ---
  //---------------------------------
  
  if (d_iCustomers.size() <= maxCustomers_n3)
  {
    cout << "Remove subtours n = 3" << endl;
    
    for (int i: d_iCustomers)
    {
      // -------------------------------
      // --- Find cheapest subtours  ---
      // -------------------------------
      
      vector<tuple<int, int, double>> tmp;
      tmp.reserve(d_nCustomers * d_nCustomers);
      
      for (int j: d_iCustomers)
      {
        if (i == j)
          continue;
        
        for (int k: d_iCustomers)
        {
          if (i == k or j == k)
            continue;
          
          tmp.emplace_back(j, k, d_cost[i][j] + d_cost[j][k] + d_cost[k][i]);
        }
      }
      
      
      
      partial_sort(begin(tmp), begin(tmp) + nCuts_n3, end(tmp), [](auto const &t1, auto const &t2) {
        return get<2>(t1) < get<2>(t2);
      });
      
      
      
      // -------------------------------
      // --- Add cuts                ---
      // -------------------------------      
      
      for (int idx = 0; idx < nCuts_n3; ++idx)
      {
        int const j = get<0>(tmp[idx]);
        int const k = get<1>(tmp[idx]);
        
        double const demand = d_demands[i] + d_demands[j] + d_demands[k];
        int const rhs = 3 - ceil(demand / static_cast<double>(d_vehicleCap));
        
        IloExpr expr(d_env);
        expr +=   d_x[i][j] + d_x[i][k]
                + d_x[j][i] + d_x[j][k]
                + d_x[k][i] + d_x[k][j];

        cplex.addLazyConstraint(expr <= rhs);
        expr.end();
      }
    }
  }

  
  
  
  
  
  
  //---------------------------------
  // --- Remove subtours of n = 4 ---
  //---------------------------------


  if (d_iCustomers.size() <= maxCustomers_n4)
  {
    cout << "Remove subtours n = 4" << endl;
    
    
    for (int i: d_iCustomers)
    {
      // -------------------------------
      // --- Find cheapest subtours  ---
      // -------------------------------
      
      vector<tuple<int, int, int, double>> tmp;
      tmp.reserve(d_nCustomers * d_nCustomers * d_nCustomers);
      
      for (int j: d_iCustomers)
      {
        if (j == i)
          continue;
        
        for (int k: d_iCustomers)
        {
          if (k == i or k == j)
            continue;
          
          for (int l: d_iCustomers)
          {
            if (l == i or l == j or l == k)
              continue;
            
            tmp.emplace_back(j, k, l, d_cost[i][j] + d_cost[j][k] + d_cost[k][l] + d_cost[l][i]);
          }
        }
      }
      
      
      partial_sort(begin(tmp), begin(tmp) + nCuts_n4, end(tmp), [](auto const &t1, auto const &t2) {
        return get<3>(t1) < get<3>(t2);
      });
      
      
      
      // -------------------------------
      // --- Add cuts                ---
      // -------------------------------
      
      for (int idx = 0; idx < nCuts_n4; ++idx)
      {
        int const j = get<0>(tmp[idx]);
        int const k = get<1>(tmp[idx]);
        int const l = get<2>(tmp[idx]);
        
        double const demand = d_demands[i] + d_demands[j] + d_demands[k] + d_demands[l];
        int const rhs = 4 - ceil(demand / static_cast<double>(d_vehicleCap));
        
        IloExpr expr(d_env);
        expr +=   d_x[i][j] + d_x[i][k] + d_x[i][l]
                + d_x[j][i] + d_x[j][k] + d_x[j][l]
                + d_x[k][i] + d_x[k][j] + d_x[k][l]
                + d_x[l][i] + d_x[l][j] + d_x[l][k];
        
        cplex.addLazyConstraint(expr <= rhs);
        expr.end();
      }
    }
  }
}
