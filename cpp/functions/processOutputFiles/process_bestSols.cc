#include "./../../main.ih"

/*
 * Create an overview of the best known solution for each instance
 */

void process_bestSols ()
{
  // -------------------------------
  // --- Which settings to read  ---
  // -------------------------------
  
//   vector<string> const all_folders = {"base_plusBoth"};
  
  vector<int> const all_n1 = {250}; // {-1, 0, 100, 250, 500};
  vector<int> const all_n2 = {200}; // {50, 100, 150, 200};
  vector<int> const all_n3 = {200}; // {10, 25, 50, 100, 200};
  
  int constexpr idx_problem_first = 0;
  int constexpr idx_problem_last  = 12;
  
  int constexpr nThreads  = 5;
  int constexpr sleepTime = 60;
  int constexpr repIdx    = 0;
  
  
  // -------------------------------
  // --- Read the files          ---
  // -------------------------------
  
  int constexpr colWidthA = 44;
  int constexpr colWidthB = 11;
  
  ofstream file_long  ("results_tmp/bestSols_long"); 
  ofstream file_short ("results_tmp/bestSols_short"); 
  
  file_short << setw(17) << 'n'
             << setw(5)  << 'm'
             << setw(5)  << "rep"
             << setw(11) << "UB" << endl;
  
  file_long  << setw(17) << 'n'
             << setw(5)  << 'm'
             << setw(5)  << "rep"
             << setw(11) << "UB" << endl
             << setw(colWidthA) << ' ';
       
  for (int v_n1: all_n1)
    for (int v_n2: all_n2) 
      for (int v_n3: all_n3)
        file_long << setw(colWidthB) << v_n1;
  file_long << endl << setw(colWidthA) << ' ';
      
  for (int v_n1: all_n1)
    for (int v_n2: all_n2) 
      for (int v_n3: all_n3)
        file_long << setw(colWidthB) << v_n2;
  file_long << endl<< setw(colWidthA) << ' ';
  
  for (int v_n1: all_n1)
    for (int v_n2: all_n2) 
      for (int v_n3: all_n3)
        file_long << setw(colWidthB) << v_n3;
  file_long << endl;
  
  for (int idx_problem = idx_problem_first; idx_problem < idx_problem_last; ++idx_problem)
  {
    set_global_enums(idx_problem);

    for (auto const el: get_characs(idx_problem))
    {
      for (int rep = 0; rep != 3; ++rep)
      {   
        // ----------------------------
        // --- Read all solutions   ---
        // ----------------------------   
        
        vector<double> all_LB;
        vector<double> all_UB;
        vector<bool>   all_opt;
        
        for (int v_n1: all_n1)
        {
          for (int v_n2: all_n2) 
          {
            for (int v_n3: all_n3)
            {
// This is for the old data files (i.e., before the revision)
// We now use a different file name with more information in the name

//               string const filename("./../analysis/tuning/" 
//                                     + getInstanceName() 
//                                     + "/base_plusBoth/" 
//                                     + to_string(v_n1)  + "_" 
//                                     + to_string(v_n2)  + "_" 
//                                     + to_string(v_n3)  + "/n"
//                                     + to_string(el[1]) + "m"
//                                     + to_string(el[0]) + "_" 
//                                     + to_string(rep));
            
              string const filename("./../analysis_new/tuning/" 
                                    + getInstanceName() 
                                    + "/base_plusGurobi/" 
                                    + to_string(v_n1)  + "_" 
                                    + to_string(v_n2)  + "_" 
                                    + to_string(v_n3)  + "/n"
                                    + to_string(el[1]) + "m"
                                    + to_string(el[0]) + "_" 
                                    + to_string(rep)
                                    + "_nThreads-" + to_string(nThreads)
                                    + "_sleep-"    + to_string(sleepTime)
                                    + "_repIdx-"   + to_string(repIdx)
                                   );
              
              ResultSingleFile const result(filename);      
                          
              all_LB.push_back  (result.LB);
              all_UB.push_back  (result.UB);
              all_opt.push_back (result.optimal);
            }
          }
        }
        
        
        
        // ----------------------------
        // --- Create output file   ---
        // ----------------------------
        
        int bestUB = numeric_limits<int>::max();
        
        for (int v: all_UB)
          if (v > 0 and v < bestUB)
            bestUB = v;
        
        bool const optimal = (find(cbegin(all_opt), cend(all_opt), true) != cend(all_opt));
        
        file_short << setw(12) << getInstanceName() 
                   << setw(5)  << el[0] 
                   << setw(5)  << el[1] 
                   << setw(5)  << rep << ' '
                   << setw(10) << (bestUB < numeric_limits<int>::max() ? bestUB : -1) << ' '
                   << setw(4)  << (optimal ? '1' : '0')
                   << endl;
                   
        file_long  << setw(12) << getInstanceName() 
                   << setw(5)  << el[0] 
                   << setw(5)  << el[1]
                   << setw(5)  << rep
                   << setw(10) << (bestUB < numeric_limits<int>::max() ? bestUB : -1) << ' '
                   << setw(4)  << (optimal ? '1' : '0')
                   << "  |  ";      
                  
        for (size_t idx = 0; idx < all_UB.size(); ++idx)
        {
          file_long << setw(8) << all_UB[idx]
                    << setw(3) << (all_UB[idx] == bestUB) + all_opt[idx];
        }
        
        file_long << endl;
      }
    }
  }
}
