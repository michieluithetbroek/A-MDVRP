
#include "modelC.ih"

/*
 * Reads the solution stored in the global solution variable
 * This is always feasible as we increase delta
 * 
 */


void ModelC::setInitialSolution()
{
  // Is there already a solution found?
  
  if (g_cutOff == numeric_limits<int>::max())
    return;
  
  cout << "Read initial solution from global variable" << endl;
  
  
  
  // ---------------------------------
  // --- Set initial solution      ---
  // ---------------------------------
  
  for (int idx = 0; idx != d_nNodes; ++idx)
  {
    for (int jdx = 0; jdx != d_nNodes; ++jdx)
    {
      int const value = g_globalSol[idx][jdx]._a;
      
      d_x[idx][jdx].set(GRB_DoubleAttr_Start, value);
    }
  }
}