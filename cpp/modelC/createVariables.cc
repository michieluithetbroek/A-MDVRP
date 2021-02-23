#include "modelC.ih"

void ModelC::createVariables()
{
  // ---------------------------------------------------------
  // --- x_ij variables                                    ---
  // ---------------------------------------------------------
  
  for (int idx = 0; idx != d_nNodes; ++idx)
  {
    for (int jdx = 0; jdx != d_nNodes; ++jdx)
    {
      string name("x_" + to_string(idx) + "_" + to_string(jdx));
      d_x[idx][jdx] = d_model.addVar(0.0, 1.0, d_cost[idx][jdx], GRB_BINARY, name.c_str());  
      
      d_z[idx][jdx] = d_model.addVar(0, d_vehicleCap, 0, GRB_CONTINUOUS, name.c_str());  
      
    }
  }
   
  if (g_depotCost)
  {
    for (int idx : d_iDepots)
    {
      string name("s_" + to_string(idx));
      d_loc[idx] = d_model.addVar(0.0, 1.0, d_data.d_depotCost[idx], GRB_CONTINUOUS, name.c_str());
    }
  }
      
  
  // ---------------------------------------------------------
  // --- y_i variables: subtour variables MTZ formulation  ---
  // ---------------------------------------------------------
  
  for (int idx = 0; idx != d_nNodes; ++idx)
  {
    string name("y_" + to_string(idx));
    d_y[idx] = d_model.addVar(d_demands[idx], d_vehicleCap, 0.0, GRB_CONTINUOUS, name.c_str());          
  }  

  
  
  // ---------------------------------------------------------
  // --- u_i variables: depot fixing variables             ---
  // ---------------------------------------------------------
  
  for (int idx = 0; idx != d_nNodes; ++idx)
  {
    string name("u_" + to_string(idx));
    d_u[idx] = d_model.addVar(0.0, d_nDepots, 0.0, GRB_CONTINUOUS, name.c_str());          
  }
}
