#include "./../../main.ih"



/*
 * Create an overview with statistics of all instances
 * Currently table 5 in the paper
 */
 
void process_allSettings_long()
{
  vector<int> const all_n1 = {-1, 0, 100, 250, 500};
  vector<int> const all_n2 = {50, 100, 150, 200};
  vector<int> const all_n3 = {10, 25, 50, 100, 200};
  
  string const alg = "base";
  
  for (int idx_problem = 0; idx_problem < 11; ++idx_problem)
  {
    vector<MergedResultSetting> allResults;
  
    set_global_enums(idx_problem);
    
    auto const characs = get_characs(idx_problem);
    
    for (int v_n1: all_n1)
      for (int v_n2: all_n2)
        for (int v_n3: all_n3)
          allResults.emplace_back(array<int, 3> ({v_n1, v_n2, v_n3}), characs, alg);

    cout << endl << endl; 
    
    sort(begin(allResults), end(allResults), [](auto lhs, auto rhs)
    {
      if (lhs.nSolved > rhs.nSolved)
        return true;
      
      if (lhs.nSolved != rhs.nSolved)
        return false;
      
      return (lhs.avgLB > rhs.avgLB);
    });
    
    cout << "results for: " << getInstanceName() 
         << endl << alg << endl
         << setw(15) << "settings" << " | "
         << setw(15) << " "
         << setw(5)  << "nOpt"
         << setw(10) << "avgLB"
         << setw(10) << "avgTime"
         << setw(11) << "avgNodes"
         << setw(25) << "nGap (1, 2, 5, 10, 25)"
         << setw(10) << "avgRoot"
         << setw(30) << "avgTime (lazy, user, heur)" << endl;
    
    for (auto v: allResults)
      cout << fixed << setprecision(2)
          << setw(5)  << v.n1 << setw(5) << v.n2 << setw(5) << v.n3 << " | "
          << setw(5)  << v.nInstances
          << setw(5)  << v.nNotFound
          << setw(5)  << v.nNoSol          
          << setw(5)  << v.nSolved
          << setw(10) << v.avgLB
          << setw(10) << v.avgTime
          << setw(11) << v.avgNodes
          << setw(5)  << v.nGap1
          << setw(5)  << v.nGap2
          << setw(5)  << v.nGap5
          << setw(5)  << v.nGap10
          << setw(5)  << v.nGap25
          << setw(10) << v.avgRoot
          << setw(10) << v.avgTimeLazy
          << setw(10) << v.avgTimeUser
          << setw(10) << v.avgTimeHeur << endl;
  }
}



void process_allSettings_short ()
{
  /*
   * The final settings that we use for each problem type
   * We should store this in a file as soon as we 
   * start using this information in other functions too.
   * 
   * settingsA are the settings for the base model
   * settingsB are the settings for our B&B
   */
  

  vector<array<int, 3>> const settingsA =
  {
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200},
    {250, 200, 200}
  };
  
    
  
  /*
   * For each problem type we create a single line in the final table
   * Note that a problem type describes both the problem and the assymetricy
   */ 
  
  for (string const alg: {"base", "base_plusBoth"})
  {
    vector<MergedResultSetting> allResults;
    
    for (int idx_problem = 0; idx_problem < 12; ++idx_problem)
    {
      set_global_enums(idx_problem);
       
      auto const characs = get_characs(idx_problem);
      auto const setting = settingsA[idx_problem];
      
      allResults.emplace_back(setting, characs, alg);
    }
    
    
    
    // ------------------------------
    // --- Print to terminal      ---
    // ------------------------------
    
//     cout << endl << alg << endl
//          << endl << endl 
//          << setw(30) << "settings" << " | "
//          << setw(15) << " "
//          << setw(5)  << "nOpt"
//          << setw(10) << "avgLB"
//          << setw(10) << "avgTime"
//          << setw(11) << "avgNodes"
//          << setw(25) << "nGap (1, 2, 5, 10, 25)"
//          << setw(10) << "avgRoot"
//          << setw(30) << "avgTime (lazy, user, heur)" << endl;
//       
//     for (int idx_problem = 0; idx_problem < 12; ++idx_problem)
//     {
//       set_global_enums(idx_problem);
//       
//       auto const &v = allResults[idx_problem];
//       
//       cout << fixed << setprecision(2)
//            << setw(15) << getInstanceName()
//            << setw(5)  << v.n1 << setw(5) << v.n2 << setw(5) << v.n3 << " | "
//            << setw(5)  << v.nInstances
//            << setw(5)  << v.nNotFound
//            << setw(5)  << v.nNoSol          
//            << setw(5)  << v.nFeas
//            << setw(5)  << v.nSolved
//            << setw(10) << v.avgLB
//            << setw(10) << v.avgTime
//            << setw(11) << v.avgNodes
//            << setw(5)  << v.nGap1
//            << setw(5)  << v.nGap2
//            << setw(5)  << v.nGap5
//            << setw(5)  << v.nGap10
//            << setw(5)  << v.nGap25
//            << setw(10) << v.avgRoot
//            << setw(10) << v.avgTimeLazy
//            << setw(10) << v.avgTimeUser
//            << setw(10) << v.avgTimeHeur << endl;
//     }
    
    
    
    // ------------------------------
    // --- Print TeX table        ---
    // ------------------------------
    
    cout << endl << endl;
    
    for (int idx_problem = 0; idx_problem < 12; ++idx_problem)
    {
      int const asyClass = idx_problem % 3 + 1;
      string asyClassP = "I";
      
      if (asyClass == 2)
        asyClassP = "II";
      
      if (asyClass == 3)
        asyClassP = "III"; 
      
      set_global_enums(idx_problem);
      
      auto const &v = allResults[idx_problem];
      
      cout << fixed << setprecision(2) << left
           << setw(15) << (asyClass == 1 ? getPrintInstanceName() : " ") << " & " 
           << setw(5)  << asyClassP    << " & " << right
           << setw(4)  << v.nInstances << " & "
           << setw(5)  << v.nFeas      << " & "
           << setw(4)  << v.nSolved    << " & "
           << setw(4)  << v.nGap1      << " & " 
           << setw(4)  << v.nGap5      << " & "
           << setw(10) << v.avgLB      << " & " << setprecision(0)
           << setw(10) << v.avgTime    << " & "
           << setw(6)  << v.avgNodes / 1000   << " \\\\ " << v.nStopped << endl;
    }
  }
}
