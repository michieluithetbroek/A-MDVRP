#include "./../../main.ih"

/*
 * Create a table that shows how many cuts are found
 * on average per problem type. At the moment this is
 * table 3 in the manuscript.
 */

void process_output_files_for_cuts()
{
  stringstream output;
  
  // Which setting do we read
  int constexpr n1 = 250;
  int constexpr n2 = 200;
  int constexpr n3 = 200;
  
  for (int idx_problem = 0; idx_problem < 12; ++idx_problem)
  {
    set_global_enums(idx_problem);
    
    int cnt = 0;
    
    vector<int> nCuts_lazy(17, 0);
    vector<int> nCuts_user(17, 0);
    
    for (auto const el: get_characs(idx_problem))
    {
      for (int rep = 0; rep != 3; ++rep)
      {
        string const filename("./../analysis/tuning/" 
                              + getInstanceName() 
                              + "/base_plusBoth/" 
                              + to_string(n1)    + "_" 
                              + to_string(n2)    + "_" 
                              + to_string(n3)    + "/n"
                              + to_string(el[1]) + "m"
                              + to_string(el[0]) + "_" 
                              + to_string(rep));
                            
        ResultSingleFile const result(filename);
        
        ++cnt;
        
        for (int idx = 0; idx < 17; ++idx)
        {
          nCuts_lazy[idx] += result.nCuts_lazy[idx];
          nCuts_user[idx] += result.nCuts_user[idx];
        }
      }
    }
    
    for (int idx = 0; idx < 17; ++idx)
    {
      nCuts_lazy[idx] /= cnt;
      nCuts_user[idx] /= cnt;
    }
    
    output << endl << setw(5) << cnt;
    
    for (int idx = 0; idx < 17; ++idx)
      output << setw(6) << nCuts_user[idx];
  }
  
  cout << output.str() << endl;
}
