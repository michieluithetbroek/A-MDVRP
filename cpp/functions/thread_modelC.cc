#include "../main.ih"

/*
 * 
 * 
 */

void thread_modelC(Data dat)
{
  gg_startTime_modelC = chrono::high_resolution_clock::now();
  
  // For the santos benchmark we use different settings
  // for Gurobi, namely, it starts with a bigger delta.
  
  if (DATA_ASYMMETRY == ASYCLASS::SANTOS)
  {
    ModelC C(dat, 15);
    C.solve(0);
    
    return;
  }
  
  
  
  // ----------------------
  // --- Own instances  ---
  // ----------------------
  
  g_smallestDelta = 5;
  
  for (int delta = g_smallestDelta; delta <= 10; ++delta)
  {
    if (g_modelSolved)
      break;
    
    ModelC C(dat, delta);
    C.solve(0);
  }
  
  // First, we do a short exploration for all deltas
  
  for (int delta = g_smallestDelta; delta <= min(25, dat.d_nCustomers); ++delta)
  {
    if (g_modelSolved)
      break;
    
    ModelC C(dat, delta);
    C.solve(1);
  }
  
  
  // Now we give more time for each delta
  for (int delta = g_smallestDelta; delta <= min(50, dat.d_nCustomers); ++delta)
  {
    if (g_modelSolved)
      break;
    
    ModelC C(dat, delta);
    C.solve(2);
  }
}
