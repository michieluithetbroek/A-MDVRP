#include "modelA.ih"

void ModelA::createConstraints()
{
  
  // ----------------------------------------------
  // --- Single tour Depot                      ---
  // --- if MDATSP                              ---
  // ----------------------------------------------
 
  if (g_atMostOneTour)
  {
    // Leave depot at most once
    for (int i: d_iDepots)
    {
      IloNumExpr expr (d_env);
      
      for (int j: d_iNodes)
        expr += d_x[i][j];
  
      d_model.add(expr <= 1);
      expr.end();
    }  
    
    for (int i: d_iDepots)
    {
      IloNumExpr expr (d_env);
      
      for (int j: d_iNodes)
        expr += d_x[j][i];
  
      d_model.add(expr <= 1);
      expr.end();
    }  
  }
  
  
  
  // ----------------------------------------------
  // --- Depot variables                        ---
  // --- if ACLRP                               ---
  // ----------------------------------------------

  if (g_depotCost)
  {
    for (int d: d_iDepots)
    {
      for (int j: d_iCustomers)
      {
        IloNumExpr expr(d_env);
        expr += ( d_x[d][j] - d_loc[d]);
        
        d_model.add(expr <= 0);
        expr.end();
      }
    }
  }
    
    
    
  // ---------------------------------
  // --- Flow conservation         ---
  // ---------------------------------  
  
  for (int i: d_iNodes)
  {
    IloNumExpr expr(d_env);
    
    for (int j: d_iNodes)
      expr += d_x[i][j] - d_x[j][i];

    d_model.add(expr == 0);
    expr.end();
  }
  
  
  
  // ---------------------------------
  // --- Visit each customer       ---
  // --------------------------------- 
  
  for (int i: d_iCustomers)
  {
    IloNumExpr expr(d_env);
    
    for (int j: d_iNodes)
      if (j != i)
        expr += d_x[i][j];

    d_model.add(expr == 1);
    expr.end();
  }
   
   
   
  //---------------------------------
  // --- x_ii == 0                ---
  //--------------------------------- 
  
  IloNumExpr expr(d_env);
  
  for (int i: d_iNodes)
    expr += d_x[i][i];
    
  d_model.add(expr == 0);
  expr.end();
   
 
  //------------------------------------------------
  // --- Remove subtours of n = 2                ---
  // --- ALERT !!! CANNOT BE REMOVED !!! ALERT   ---
  //------------------------------------------------

  cout << "Remove subtours n = 2" << endl;
  
  for (int i: d_iCustomers)
  {
    for (int j: d_iCustomers)
    {
      if (i >= j)
        continue;
      
      IloExpr expr(d_env);
      expr += d_x[i][j] + d_x[j][i];
      
      d_model.add(expr <= 1);
      expr.end();
    }
  }

  
  // TODO why not using g_atMostOneTour?
  
  if (P_TYPE == PROBLEMTYPE::MDAMTSP)
  {
    cout << "------------------------------------------------\n"
         << "------------------------------------------------\n"
         << "------------------------------------------------\n"
         << "------------------------------------------------\n"
         << "------------------------------------------------\n"
         << "------------------------------------------------\n"
         << "------------------------------------------------\n";
    
    for (int i: d_iDepots)
    {
      for (int j: d_iCustomers)
      {
        IloNumExpr expr1(d_env);
        expr1 += d_x[i][j] + d_x[j][i];
        
        d_model.add(expr1 <= 1);
        expr1.end();
      }
    }
  }

  //---------------------------------
  // --- No arcs between d_depots ---
  //--------------------------------- 
  
  IloNumExpr expr1(d_env);
  
  for (int i: d_iDepots)
    for (int j: d_iDepots)
      expr1 += d_x[i][j];

  d_model.add(expr1 == 0);
  expr1.end();
  
}
 
 
 
 
 
 
 
 
 
 
//  
//  
//   //---------------------------------
//   // --- Preprocessing            ---
//   //--------------------------------- 
// 
//   // Too heavy customers for one vehicle
//   for (i: d_iCustomers)
//   {
//     for (j: d_iCustomers)
//     {
//       if (d_demands[i] + d_demands[j] > d_vehicleCap)
//       {
//         IloNumExpr expr(d_env);
//         expr += d_x[i][j] + d_x[j][i];
//         d_model.add(expr == 0);
//       }
//     }
//   }
//   // other subtour constraints
//   for (int j : d_iCustomers)
//   {
//     IloExpr expr(d_env);
//     expr -= d_demands[j];
//     
//     for (int i : d_iNodes)
//       expr += d_z[i][j] - d_z[j][i];
//     
//     d_model.add(expr == 0);
//   }
//   
//   
//   IloExpr expr2(d_env);
//   for (int i : d_iDepots)
//     for (int j : d_iCustomers)
//       expr2 += d_z[i][j];
//   
//   for (int j : d_iCustomers)
//     expr2 -= d_demands[j];
//   d_model.add(expr2 == 0);
//     
//   
//   for (int i: d_iNodes)
//   {
//     for (int j: d_iCustomers)
//     {
//       IloExpr expr(d_env);
//       expr += d_z[i][j];
//       
//       expr -= (d_vehicleCap - d_demands[i])*d_x[i][j];
//       
//       d_model.add(expr <= 0);
//     }
//   }
//   
//   for (int i : d_iCustomers)
//     for (int j : d_iCustomers)
//     {
//       IloExpr expr(d_env);
//       expr += d_z[i][j] - d_demands[j]*d_x[i][j];
//       d_model.add(expr >= 0 );
//     }
// 
// 
//  
//  // MTZ below.
//  
//   for (int i: d_iCustomers)
//   {
//     for (int j: d_iCustomers)
//     {
//       if (i == j)
//         continue;
//       
//       if (d_demands[i] + d_demands[j] > d_vehicleCap)
//         continue;
//       
//       IloExpr expr(d_env);
//       expr += d_y[i] - d_y[j];
//       expr += d_vehicleCap * d_x[i][j];
//          
//       expr += ( (d_vehicleCap - d_demands[i] - d_demands[j]) * d_x[j][i]);
//       expr += d_demands[j] - d_vehicleCap;
//       
//       d_model.addConstr(expr, GRB_LESS_EQUAL, 0, "MTZ");
//     }
//   }
//   
//   for (int i: d_iCustomers)
//   {
//     
//     int maxDemand = 0;
//     for (int j: d_iCustomers)
//     {
//       if (i == j)
//         continue;
//       
//       maxDemand = max(d_demands[j], maxDemand);
//     }
//     
//       
//     IloExpr expr(d_env);
//     expr += d_y[i];
//     
//     expr += (-1 * d_vehicleCap);
//     for (int d: d_iDepots)
//       expr += (d_vehicleCap - maxDemand - d_demands[i]) * d_x[d][i];
//     
//     for (int j: d_iCustomers)
//     {
//       if (j == i)
//         continue;
//       
//       expr += d_demands[j]*d_x[i][j];
//     }
//     
//     d_model.addConstr(expr, GRB_LESS_EQUAL, 0, "MTZ-CUT1");
//   }
// 
// 
// 
//   //---------------------------------
//   // --- Preprocessing            ---
//   //--------------------------------- 
// 
//   // Too heavy customers for one vehicle
//   for (i: d_iCustomers)
//   {
//     for (j: d_iCustomers)
//     {
//       if (d_demands[i] + d_demands[j] > d_vehicleCap)
//       {
//         IloExpr expr(d_env);
//         expr += d_x[i][j] + d_x[j][i];
//         d_model.addConstr(expr1, GRB_EQUAL, 0, "name");
//       }
//     }
//   }
//
//
//
//   //---------------------------------
//   // --- Remove subtours of n = 3 ---
//   //---------------------------------
// 
//   {
//     cout << "Remove subtours n = 3" << endl;
//     int constexpr n = 5;
//     
//     for (int i: d_iCustomers)
//     {
//       vector<tuple<int, int, double>> tmp;
//       tmp.reserve(d_nCustomers * d_nCustomers);
//       
//       for (int j: d_iCustomers)
//       {
//         if (i == j)
//           continue;
//         
//         for (int k: d_iCustomers)
//         {
//           if (i == k or j == k)
//             continue;
//           
//           tmp.emplace_back(j, k, d_cost[i][j] + d_cost[j][k] + d_cost[k][i]);
//         }
//       }
//       
//       partial_sort(begin(tmp), begin(tmp) + n, end(tmp), [](auto const &t1, auto const &t2) {
//         return get<2>(t1) < get<2>(t2);
//       });
//       
//       for (int idx = 0; idx < n; ++idx)
//       {
//         int const j = get<0>(tmp[idx]);
//         int const k = get<1>(tmp[idx]);
//         
//         double const demand = d_demands[i] + d_demands[j] + d_demands[k];
//         int const rhs = 3 - ceil(demand / static_cast<double>(d_vehicleCap));
//         
//         IloExpr expr(d_env);
//         expr +=   d_x[i][j] + d_x[i][k]
//                 + d_x[j][i] + d_x[j][k]
//                 + d_x[k][i] + d_x[k][j];
// 
//         d_model.add(expr <= rhs);
//       }
//     }
//   }
// 
//   
//   
//   //---------------------------------
//   // --- Remove subtours of n = 4 ---
//   //---------------------------------
// 
//   {
//     int constexpr n = 3;      // Number of constraints per customer node
//     
//     cout << "Remove subtours n = 4" << endl;
//     
//     for (int i: d_iCustomers)
//     {
//       vector<tuple<int, int, int, double>> tmp;
//       tmp.reserve(d_nCustomers * d_nCustomers * d_nCustomers);
//       
//       for (int j: d_iCustomers)
//       {
//         if (j == i)
//           continue;
//         
//         for (int k: d_iCustomers)
//         {
//           if (k == i or k == j)
//             continue;
//           
//           for (int l: d_iCustomers)
//           {
//             if (l == i or l == j or l == k)
//               continue;
//             
//             tmp.emplace_back(j, k, l, d_cost[i][j] + d_cost[j][k] + d_cost[k][l] + d_cost[l][i]);
//           }
//         }
//       }
//       
//       partial_sort(begin(tmp), begin(tmp) + n, end(tmp), [](auto const &t1, auto const &t2) {
//         return get<3>(t1) < get<3>(t2);
//       });
//       
//       for (int idx = 0; idx < n; ++idx)
//       {
//         int const j = get<0>(tmp[idx]);
//         int const k = get<1>(tmp[idx]);
//         int const l = get<2>(tmp[idx]);
//         
//         double const demand = d_demands[i] + d_demands[j] + d_demands[k] + d_demands[l];
//         int const rhs = 4 - ceil(demand / static_cast<double>(d_vehicleCap));
//         
//         IloExpr expr(d_env);
//         expr +=   d_x[i][j] + d_x[i][k] + d_x[i][l]
//                 + d_x[j][i] + d_x[j][k] + d_x[j][l]
//                 + d_x[k][i] + d_x[k][j] + d_x[k][l]
//                 + d_x[l][i] + d_x[l][j] + d_x[l][k];
//         
//         d_model.add(expr <= rhs);
//       }
//     }
//   }
