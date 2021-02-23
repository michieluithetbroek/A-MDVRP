#include "modelA.ih"

void ModelA::createVariables()
{
  // x_ij variables
  for (int idx = 0; idx != d_nNodes; ++idx)
  {
    d_x[idx] = IloNumVarArray(d_env, d_nNodes);
    
    for (int jdx = 0; jdx != d_nNodes; ++jdx)
    {
      string name("x_" + to_string(idx) + "_" + to_string(jdx));
      d_x[idx][jdx] = IloNumVar(d_env, 0.0, 1.0, ILOBOOL, name.c_str());
    }
  }
  
  if (g_depotCost == true) //@michiel, just to remember it is a bool, @albert: (Y)
  {
    for (int idx : d_iDepots)
    {
      string name("s_" + to_string(idx)); 
      d_loc[idx] = IloNumVar(d_env, 0.0, 1.0, ILOFLOAT, name.c_str());    
    }
  }
}
