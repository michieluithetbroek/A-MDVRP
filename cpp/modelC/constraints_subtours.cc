#include "modelC.ih"

/*
 * 
 * MTZ lifted SEC based on u variable
 */


void ModelC::constraints_subtours()
{
  for (int j: d_iCustomers)
  {
    GRBLinExpr expr = 0;
    expr -= d_demands[j];
    
    for (int i: d_iNodes)
      expr += d_z[i][j] - d_z[j][i];
    
    d_model.addConstr(expr, GRB_EQUAL, 0, "ARC1");
  }
  
  GRBLinExpr expr1 =  0;
  
  for (int i: d_iDepots)
    for (int j: d_iCustomers)
      expr1 += d_z[i][j];
  
  for (int j: d_iCustomers)
    expr1 -= d_demands[j];
  
  d_model.addConstr(expr1, GRB_EQUAL, 0, "ARC2");
    
  
  for (int i: d_iNodes)
  {
    for (int j: d_iCustomers)
    {
      GRBLinExpr expr = d_z[i][j];

      expr -= (d_vehicleCap - d_demands[i]) * d_x[i][j];
      
      d_model.addConstr(expr, GRB_LESS_EQUAL, 0, "UB-ARC");
    }
  }
      
  // TODO why not introducing a global bool for this
  // The bool should be set by the Data class. Then
  // we can remove these enums from the global scope.
  
  if (P_TYPE == PROBLEMTYPE::MDAMTSP)
  {
    for (int i: d_iDepots)
    {
      for (int j: d_iCustomers)
      {
        GRBLinExpr expr = 0;
        expr += d_z[i][j] + d_M * (1 - d_x[i][j]);
        d_model.addConstr(expr, GRB_GREATER_EQUAL, d_data.d_tourMin, "UB-ARC");
      }
    }
  }
}
