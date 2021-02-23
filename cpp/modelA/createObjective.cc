#include "modelA.ih"

void ModelA::createObjective()
{
  IloNumExpr expr(d_env);
 
  for (int i: d_iNodes)
    for (int j: d_iNodes)
        expr += d_x[i][j] * d_cost[i][j];
    
  if (g_depotCost)
    for (int d: d_iDepots)
      expr += d_loc[d] * d_data.d_depotCost[d];
    
  d_model.add(IloMinimize(d_env, expr));
  expr.end();
}

