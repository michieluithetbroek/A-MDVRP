#include "./../../main.ih"

/*
 * 
 */

void run_base_plusBoth (int instanceType, int idx_instance, 
                        int cutPasses, int cutA, int cutB)
{
  g_cutPasses    = cutPasses;
  g_userSettingA = cutA;
  g_userSettingB = cutB;
  
  g_cplexFocusLB = true;          // CPLEX focussed on LB
  g_onlyRoot     = false;         // Solve the whole branch-and-bound
  g_cplexCuts    = true;          // 0 = with cplex cuts, -1 = without
  
  g_useGurobi    = true;
  int  const cutProfile = 1;

  set_global_enums(instanceType);
  
  string folder("results/tuning/" + getInstanceName() + "/base_plusBoth/");
  
  run_single_instance_own (instanceType, idx_instance, folder, cutProfile);
}
