#include "./../../main.ih"

/*
 * 
 */

void run_base (int instanceType, int idx_instance, 
               int cutPasses, int cutA, int cutB)
{
  g_cutPasses    = cutPasses;
  g_userSettingA = cutA;
  g_userSettingB = cutB;
  
  g_cplexFocusLB = false;         // Run CPLEX on default mode
  g_onlyRoot     = false;         // Solve the whole branch-and-bound
  g_cplexCuts    = true;          // 0 = with cplex cuts
  
  g_useGurobi    = false;
  int  const cutProfile = 0;
  
  set_global_enums(instanceType);
  
  string folder("results/tuning/" + getInstanceName() + "/base/");
  
  run_single_instance_own (instanceType, idx_instance, folder, cutProfile);
}
