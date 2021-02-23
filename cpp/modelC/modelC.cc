#include "modelC.ih"

/*
 * The upper bound is unused...
 * 
 */

ModelC::ModelC(Data const &data, int neighbourhoodSize)
:
  d_data       (data),
  d_delta      (neighbourhoodSize),
  d_nDepots    (data.d_nDepots),
  d_nCustomers (data.d_nCustomers),
  d_nNodes     (data.d_nNodes),
  d_vehicleCap (data.d_vehicleCap),
  d_demands    (data.d_demands),
  d_iDepots    (data.d_iDepots),
  d_iCustomers (data.d_iCustomers),
  d_iNodes     (data.d_iNodes),
  d_cost       (data.d_cost),
  d_env        (),
  d_model      (d_env),
  d_x          (data.d_nNodes, vector<GRBVar>(data.d_nNodes, GRBVar())),
  d_y          (data.d_nNodes, GRBVar()),
  d_u          (data.d_nNodes, GRBVar()),
  d_z          (data.d_nNodes, vector<GRBVar>(data.d_nNodes, GRBVar())),
  d_loc        (data.d_nNodes, GRBVar()),
  d_neighbourhoodSize (d_delta)
{
  
  cout << " -- delta = " << d_delta << endl;
  
  createVariables();
  createObjective();
  createConstraints();

  setInitialSolution();
  
  
//   for (int i: d_iNodes)
//     for (int j: d_iNodes)
//       d_x[i][j].set(GRB_DoubleAttr_Start, 0.0);
//     
  
//   solve();
}
