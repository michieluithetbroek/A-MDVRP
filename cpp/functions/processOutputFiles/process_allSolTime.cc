#include "./../../main.ih"



/*
 * Create a long format table that gives an overview
 * of the time up to a given objective value
 */

void process_allSolTime()
{
  // Which CPLEX settings are used
  string const settings   = "250_200_200";
  
  int constexpr nThreads  = 5;
  int constexpr sleepTime = 60;
  
  // Which algorithms do we merge?
  vector<string> const algos = {{"base", "base_plusCuts",
                                 "base_plusGurobi", "base_plusBoth"}};
  
  ofstream file("./timeToSol");
  
  file << setw(10) << "idx_inst"    << " "
       << setw(16) << "algoName"    << " "
       << setw(10) << "Solver"      << " "
       << setw(10) << "idx_col"     << " "
       << setw(6)  << "n"           << " "
       << setw(6)  << "m"           << " "
       << setw(7)  << "instRep"     << " "
       << setw(8)  << "nThreads"    << " "
       << setw(9)  << "sleepTime"   << " "
       << setw(6)  << "runRep"      << " "
       << setw(10) << "time"        << " "
       << setw(10) << "obj"         << '\n'; 
  
  for (string const algoName: algos)
  {
    int idx_inst = -1;
    
    // Loop over all our problem classes
    for (int idx_problem = 0; idx_problem < 12; ++idx_problem)
    {
      set_global_enums(idx_problem);
      
      auto const characs = get_characs(idx_problem);
      
      for (auto const el: get_characs(idx_problem))
      {
        // Each instance has three setting replication 
        for (int rep = 0; rep < 3; ++rep)
        {
          ++idx_inst;
            
          // We have runned each instance 3 times on Peregrine
          // Hereby we can checked whether difference in runtime are 
          // due to performance differences of the cluster -> not relevant
          
          for (int runRep = 0; runRep < 3; ++runRep)
          {
            string const filename("./../analysis_new/tuning/" 
                                  + getInstanceName() + "/" 
                                  + algoName          + "/" 
                                  + settings          + "/n"
                                  + to_string(el[1])  + "m"
                                  + to_string(el[0])  + "_" 
                                  + to_string(rep)
                                  + "_nThreads-" + to_string(nThreads)
                                  + "_sleep-"    + to_string(sleepTime)
                                  + "_repIdx-"   + to_string(runRep)
                                );
                  
            ResultSingleFile const result(filename);
            
            
            // We print a dummy row to indicate the start objective -1
            
            file << setw(10) << idx_inst     << " "
                  << setw(16) << algoName    << " "
                  << setw(10) << "CPLEX"     << " "
                  << setw(10) << idx_problem << " "
                  << setw(6)  << el[1]       << " "
                  << setw(6)  << el[0]       << " "
                  << setw(7)  << rep         << " "
                  << setw(8)  << nThreads    << " "
                  << setw(9)  << sleepTime   << " "
                  << setw(6)  << runRep      << " "
                  << setw(10) << 0           << " "
                  << setw(10) << -1          << '\n';
            
            int minVal = numeric_limits<int>::max();
            
            for (size_t idx = 0; idx < size(result.timeToSol_modelA); ++idx)
            {
              auto const &val = result.timeToSol_modelA[idx];
              
              // Skip rows with the same objective
              // The first row cannot be skipped
              
              if (idx > 0 and val.second >= minVal)
                continue;
              
              if (idx > 0 and val.first <= result.timeToSol_modelA[idx-1].first)
                continue;
              
              minVal = val.second;
              
              
              
              file << setw(10) << idx_inst   << " "
                  << setw(16) << algoName    << " "
                  << setw(10) << "CPLEX"     << " "
                  << setw(10) << idx_problem << " "
                  << setw(6)  << el[1]       << " "
                  << setw(6)  << el[0]       << " "
                  << setw(7)  << rep         << " "
                  << setw(8)  << nThreads    << " "
                  << setw(9)  << sleepTime   << " "
                  << setw(6)  << runRep      << " "
                  << setw(10) << val.first   << " "
                  << setw(10) << val.second  << '\n';
            }
            
            file << setw(10) << idx_inst     << " "
                  << setw(16) << algoName    << " "
                  << setw(10) << "Gurobi"    << " "
                  << setw(10) << idx_problem << " "
                  << setw(6)  << el[1]       << " "
                  << setw(6)  << el[0]       << " "
                  << setw(7)  << rep         << " "
                  << setw(8)  << nThreads    << " "
                  << setw(9)  << sleepTime   << " "
                  << setw(6)  << runRep      << " "
                  << setw(10) << 0           << " "
                  << setw(10) << -1          << '\n';
            

            minVal = numeric_limits<int>::max();
            
            for (size_t idx = 0; idx < size(result.timeToSol_modelC); ++idx)
            {
              auto const &val = result.timeToSol_modelC[idx];
              
              // Skip rows with the same objective
              // The first row cannot be skipped
              
              if (idx > 0 and val.second >= minVal)
                continue;
              
              if (idx > 0 and val.first <= result.timeToSol_modelC[idx-1].first)
                continue;
              
              minVal = val.second;
              
              file << setw(10) << idx_inst   << " "
                  << setw(16) << algoName    << " "
                  << setw(10) << "Gurobi"    << " "
                  << setw(10) << idx_problem << " "
                  << setw(6)  << el[1]       << " "
                  << setw(6)  << el[0]       << " "
                  << setw(7)  << rep         << " "
                  << setw(8)  << nThreads    << " "
                  << setw(9)  << sleepTime   << " "
                  << setw(6)  << runRep      << " "
                  << setw(10) << val.first   << " "
                  << setw(10) << val.second  << '\n';
            }
          }
        }
      }
    }
  }
}
