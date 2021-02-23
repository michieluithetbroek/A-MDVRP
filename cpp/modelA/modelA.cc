#include "modelA.ih"


/*
 * This one can be removed
 * 
 */

ModelA::ModelA (Data const &data, vector<shared_ptr<Cut>> const &allCuts)
:
  d_data       (data),
  d_nDepots    (data.d_nDepots),
  d_nCustomers (data.d_nCustomers),
  d_nNodes     (data.d_nNodes),
  d_vehicleCap (data.d_vehicleCap),
  d_demands    (data.d_demands),
  d_iDepots    (data.d_iDepots),
  d_iCustomers (data.d_iCustomers),
  d_iNodes     (data.d_iNodes),
  d_cost       (data.d_cost),
  d_cuts       (allCuts),
  d_env        (),
  d_model      (d_env),
  d_x          (d_env, d_nNodes),
  d_loc        (d_env, d_nDepots)
{
  // ---------------------------------
  // --- Set namespace variables   ---
  // ---------------------------------   
  
  graphFunctions::setValues(d_nDepots, d_nCustomers, d_nNodes,
                            d_iDepots, d_iCustomers, d_iNodes);
  
  
  // ---------------------------------
  // --- Build the model           ---
  // ---------------------------------
  
  createVariables();
  createObjective();
  createConstraints();
}
