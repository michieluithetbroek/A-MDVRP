#include "mycallbackcompact.ih"

/*
 * Check whether we have a new best solution 
 * If yes, then store it to the global variable 
 */

void MyCallbackcompact::callback_lazy()
{
  if (getDoubleInfo(GRB_CB_MIPSOL_OBJ) >= g_cutOff)
    return;
    
  g_cutOff = getDoubleInfo(GRB_CB_MIPSOL_OBJ);
  g_smallestDelta = d_model->d_delta;
  
  auto const currTime    = chrono::high_resolution_clock::now();
  dur_t const delta_time = currTime - gg_startTime_modelC;
  
  gg_timeToSol_modelC.emplace_back(delta_time, g_cutOff);
  
  cout << endl
       << "--- Gurobi" << endl
       << "--- UB SET = " << g_cutOff << endl
       << "--- delta = " << d_model->d_delta << endl 
       << endl;
  
  // Store the solution into the global variables
  for (int idx: d_model->d_iNodes)
  {
    int const len = d_model->d_x[idx].size();
    
    double *x = getSolution(d_model->d_x[idx].data(), len);
    
    for (int jdx = 0; jdx < len; ++jdx)
      g_globalSol[idx][jdx] = atomwrapper<int>(ceil(x[jdx] - 0.5));
  
    delete[] x;
  }
    
//     d_model->printRoutes();
}
