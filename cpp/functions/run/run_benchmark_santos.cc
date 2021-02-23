#include "./../../main.ih"

/*
 * This functions runs all the instances from Santos
 * 
 * TODO remove bool deterministic
 */

void run_benchmark_santos(int idx_instance, bool deterministic, int rep)
{
  bool const withoutGurobi = false;

  if (not deterministic)
    throw string("Opportunistic run is not allowed! (run_benchmark_santos)");
  
  g_cutPasses    = 500;
  g_userSettingA = 200; //200;
  g_userSettingB = 200;
  
  g_cplexFocusLB = true;          // CPLEX focussed on LB
  g_onlyRoot     = false;         // Solve the whole branch-and-bound
  g_cplexCuts    = true;          // 0 = with cplex cuts, -1 = without
  g_useGurobi    = true;
  
  if (withoutGurobi)
  {
    g_cplexFocusLB = false;          // CPLEX focussed on LB
    g_onlyRoot     = false;         // Solve the whole branch-and-bound
    g_cplexCuts    = true;          // 0 = with cplex cuts, -1 = without
    g_useGurobi    = false;
  }

  int  const cutProfile = 1;
  
  /*
   * The following sets the global enums INSTANCE and DATA_ASYMMETRY
   * This is used in the Data struct to set the costs and to activate
   * the proper constraints in the ModelA class.
   * 
   */
  
  hash_and_set_globals(12, 0);
  
  Data data (idx_instance);
  
  if (deterministic and not withoutGurobi)
  {
    string folder("results/santos/" 
      + to_string(idx_instance)
      + "_nThreads-"
      + to_string(g_nThreads) 
      + "_rep-"
      + to_string(rep));
    
    run_single_instance(data, folder, cutProfile);
  }
  
  else if (deterministic and withoutGurobi)
  {
    cout << "without Gurobi!" << endl; 

    string folder("results/santos/" 
      + to_string(idx_instance)
      + "_nThreads-"
      + to_string(g_nThreads)
      + "_withoutGurobi"
      + "_rep-"
      + to_string(rep));
    
    run_single_instance(data, folder, cutProfile);
  }

  else
  {
    string folder("results/santos/" 
    + to_string(idx_instance) 
    + "_par_" + to_string(rep));
    
    run_single_instance(data, folder, cutProfile);
  }
}

