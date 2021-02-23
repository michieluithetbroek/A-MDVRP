#include "./../../main.ih"

/*
 * Solve the root node for all instances
 * All three repetitions of the instance are solved
 * 
 * We can just set the lazy globals such that only a part of the cuts are used
 * Then the actually running is handled by the function 'run_and_hash_and_set_globals' 
 *
 * The order of the bools in the array can be found in make_cut_vector.cc
 * 
 * TODO there is a terrible amount of hardcoding here
 * This occurs in all our functions that process output files..
 */

void run_roots(int cutPass, bool withCplexCuts, bool withGurobi)
{
  cout << "Run roots\n";
  
  g_onlyRoot     = true;
  g_cplexFocusLB = true;
  
  g_cutPasses    = cutPass;
  g_cplexCuts    = withCplexCuts;
  g_useGurobi    = withGurobi;
  
  size_t constexpr nTypes = 12; // 4 * 3
  
  // Number of instances per type
  array<size_t, 4> constexpr nInstances {{14, 22, 20, 20}}; 
  

  // --------------------------------
  // --- Define the settings      ---
  // --------------------------------
  
  // The order of the bools in the array can be found in make_cut_vector.cc
  
  vector<array<bool, 12>> const setting
  {
    {1, 0, 0,     0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1,     0, 0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1,     0, 0, 0, 0, 0, 0, 0, 0, 0},
    
    {1, 0, 0,     1, 1, 1, 1, 1, 1, 1, 1, 1},
    {0, 1, 1,     1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1,     1, 1, 1, 1, 1, 1, 1, 1, 1},
  };

  size_t const nSettings = setting.size();
  
  
  
  // --------------------------------
  // --- Create the output file   ---
  // --------------------------------

  string fileName("results_tmp/roots_");
  
  if (g_cplexCuts)
    fileName += "withCplexCuts_";
  else
    fileName += "withoutCplexCuts_";
  
  if (withGurobi)
    fileName += "withGurobi_";
  else
    fileName += "withoutGurobi_";
  
  fileName += to_string(g_cutPasses);
  
  ofstream file(fileName);
  
  
  // --------------------------------
  // --- Run all settings         ---
  // --------------------------------
  
  file << fixed << setprecision(2);

  for (size_t instType = 0; instType < nTypes; ++instType)
  {
    bool bound_on_route = false;
    
    // This are the mdtsp instances
    
    if (instType >= 3 and instType <= 5)
      bound_on_route = true;
    
    size_t const nInst = nInstances[instType / 3]; // TODO ALERT

    for (size_t idx_inst = 0; idx_inst <= nInst; ++idx_inst)
    {
      for (size_t idx_rep = 0; idx_rep < 3; ++idx_rep)
      {
        auto const el = hash_and_set_globals(instType, idx_inst);
        
        int const nDepots    = get<0>(el);
        int const nCustomers = get<1>(el);
        
        cout << "nDepots:    " << nDepots << endl
             << "nCustomers: " << nCustomers << endl << endl;
        
        file << setw(15) << getInstanceName() << ' '
             << setw(3)  << nDepots << ' '
             << setw(4)  << nCustomers << ' '
             << setw(3)  << idx_rep << ' ' << flush;
              
        // Run all settings      
        for (size_t idx_setting = 0; idx_setting < nSettings; ++idx_setting)
        {
          cout.clear();
          
          cout << "Root: " <<  instType 
               << " - " << idx_inst 
               << " - " << idx_rep 
               << " - " << idx_setting << endl;
               
          Data dat(P_TYPE, DATA_ASYMMETRY, idx_rep, nCustomers, nDepots);
          
          vector<shared_ptr<Cut>> const allCuts = make_cut_vector(dat, setting[idx_setting], bound_on_route);
          
          ModelA A(dat, allCuts);
          A.solve_root();
          
          file << setw(8) << g_LB << ' ' << setw(7) << g_runTime << ' ' << flush;
        }
        
        file << endl;
      }
    }
  }
}
