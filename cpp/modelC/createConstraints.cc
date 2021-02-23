#include "modelC.ih"

void ModelC::createConstraints()
{
  constraints_subtours();
  constraints_u();

  // TODO Michiel: place this neighbor arcs constraints in a function
  // Add more details: these constrains fix all variables x_ij that 
  // do not correspond to one of the closest neighbors to zero
  
  //---------------------------------
  // --- Neighboorhoud arcs       ---
  //--------------------------------- 
  
  // For each customer node, we only allow to use one of the cheapeast 
  // outgoing arcs. We do so by adding constraints for the most expensive
  // onces. Arcs from and to depots are always included regardless their costs  
  
  for (int const idx: d_iCustomers)
  {
    vector<pair<int, int>> hash;
    
    for (int const jdx: d_iCustomers)
      hash.emplace_back(jdx, d_cost[idx][jdx]);
    
    sort(begin(hash), end(hash), 
         [] (auto const &lhs, auto const &rhs) 
         { return lhs.second < rhs.second;});
    
    // We have +1 because the self arc is also include in the hash list
    for (size_t jdx = d_delta + 1; jdx < size(hash); ++jdx)
      d_model.addConstr(d_x[idx][hash[jdx].first], GRB_EQUAL, 0, "Forbid this arc");
  }
  
  
  // constraints below appear in any formulation
  
  // ----------------------------------------------
  // --- Single tour Depot                      ---
  // --- if santos instances are solved         ---
  // ----------------------------------------------
 
  if (g_atMostOneTour)
  {
    // Leave depot at most once
    for (int const i: d_iDepots)
    {
      GRBLinExpr expr = 0;
      
      for (int const j: d_iNodes)
        expr += d_x[i][j];
  
      d_model.addConstr(expr, GRB_LESS_EQUAL, 1, "at most one tour");
    }  
    
    for (int const i: d_iDepots)
    {
      GRBLinExpr expr = 0;
      
      for (int const j: d_iNodes)
        expr += d_x[j][i];
  
      d_model.addConstr(expr, GRB_LESS_EQUAL, 1, "at most one tour");
    }
  }
  
  if (g_depotCost)
  {
    for (int const i: d_iCustomers)
    {
      for (int const d: d_iDepots)
      {
        GRBLinExpr expr = 0;
        expr += (d_x[d][i] - d_loc[d]);
        
        d_model.addConstr(expr, GRB_LESS_EQUAL, 0, "depot vars");
      }
    }
  }
  
  
  
  // ---------------------------------
  // --- Flow conservation         ---
  // ---------------------------------  
  
  for (int const i: d_iNodes)
  {
    GRBLinExpr expr = 0;
    
    for (int const j: d_iNodes)
      expr += d_x[i][j] - d_x[j][i];

    d_model.addConstr(expr, GRB_EQUAL, 0, "Flow conservation");
  }
  
  
  
  // ---------------------------------
  // --- Visit each customer       ---
  // --------------------------------- 
  
  for (int const i: d_iCustomers)
  {
    GRBLinExpr expr = 0;
    
    for (int const j: d_iNodes)
      if (j != i)
        expr += d_x[i][j];

    d_model.addConstr(expr, GRB_EQUAL, 1, "visit each customer");
  }
   
   
   
  //---------------------------------
  // --- x_ii == 0                ---
  //--------------------------------- 
  
  GRBLinExpr expr = 0;
  
  for (int const i: d_iNodes)
    expr += d_x[i][i];
    
  d_model.addConstr(expr, GRB_EQUAL, 0, "x_ii == 0");
  

  
  //---------------------------------
  // --- Remove subtours of n = 2 ---
  //---------------------------------

//   for (int i: d_iCustomers)
//   {
//     for (int j: d_iCustomers)
//     {
//       if (i >= j)
//         continue;
//       
//       GRBLinExpr expr = 0;
//       
//       expr += d_x[i][j] + d_x[j][i];
// 
//       d_model.addConstr(expr, GRB_LESS_EQUAL, 1, "no subtours of size 2");
//     }
//   }
//   

  
  //---------------------------------
  // --- No arcs between d_depots ---
  //--------------------------------- 
  
  GRBLinExpr expr1 = 0;
  
  for (int const i: d_iDepots)
    for (int const j: d_iDepots)
      expr1 += d_x[i][j];

  d_model.addConstr(expr1, GRB_EQUAL, 0, "no arcs between depots");   
}
