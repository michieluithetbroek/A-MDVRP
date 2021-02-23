#include "modelC.ih"

void ModelC::constraints_u()
{
  // Constraint 1h and 1i
  for (int i: d_iCustomers)
  {
    GRBLinExpr expr = 0;
    
    for (int j: d_iDepots)
      expr += (j + 1) * d_x[j][i];

    d_model.addConstr(expr, GRB_LESS_EQUAL, d_u[i], "constraint 1h");
  }
  
  for (int i: d_iCustomers)
  {
    GRBLinExpr expr = 0;
    
    for (int j: d_iDepots)
      expr += (j + 1) * d_x[i][j];

    d_model.addConstr(expr, GRB_LESS_EQUAL, d_u[i], "constraint 1i");
  }
  
  
  // Constraint 1j and 1k
  for (int i: d_iCustomers)
  {
    GRBLinExpr expr = d_u[i] - d_nDepots;
    
    for (int j: d_iDepots)
      expr += -1 * (j + 1 - d_nDepots) * d_x[j][i];
    
    d_model.addConstr(expr, GRB_LESS_EQUAL, 0, "constraint 1j");
  }
  
  for (int i: d_iCustomers)
  {
    GRBLinExpr expr = d_u[i] - d_nDepots;
    
    for (int j: d_iDepots)
      expr += -1 * (j + 1 - d_nDepots) * d_x[i][j];
    
    d_model.addConstr(expr, GRB_LESS_EQUAL, 0, "constraint 1k");
  }
    
  // Constraint 3.14
  for (int i: d_iCustomers)
  {
    for (int j: d_iCustomers)
    {
      if (i == j)
        continue;
      
      GRBLinExpr expr = d_u[i] - d_u[j] - d_M * (1 - d_x[i][j] - d_x[j][i]);
      
      d_model.addConstr(expr, GRB_LESS_EQUAL, 0, "constraint 3.14");
    }
  }
}
