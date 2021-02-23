#include "./../../main.ih"



/*
 * Compare the performance of the basic algorithm with our framework
 * 
 * Time: average time of instances that are solved by both
 * Gap:  average gap of instances where both found an upper bound but not solved
 * LB:   average lower bound of remaining instances
 * 
 * For each problem type we create a single line in the output table
 * Note that a problem type describes both the problem and the assymetricy
 */ 

void process_compareBoth ()
{
  string const settings  = "250_200_200";
  string const nThreads  = "_nThreads-5";
  string const sleepTime = "_sleep-60";
  string const repIdx    = "_repIdx-1";
  
  double sumTime_A = 0;
  double sumTime_B = 0;
  double sumGap_A  = 0;
  double sumGap_B  = 0;
  double sumLB_A   = 0;
  double sumLB_B   = 0;
  
  int n_times      = 0;
  int n_gaps       = 0;
  int n_LowerBs    = 0;
  
  // Loop over all our problem classes
  for (int idx_problem = 0; idx_problem < 12; ++idx_problem)
  {
    vector<double> timeA;
    vector<double> timeB;
    vector<double> gapA;
    vector<double> gapB;
    vector<double> lowerbA;
    vector<double> lowerbB;
      
    set_global_enums(idx_problem);
    
    auto const characs = get_characs(idx_problem);
    
    for (auto const el: get_characs(idx_problem))
    {
      // Each instance has three setting replication 
      for (int rep = 0; rep < 3; ++rep)
      {
        string const filenameA("./../analysis_new/tuning/" 
                                + getInstanceName() + "/" 
                                + "base"            + "/" 
                                + settings          + "/n"
                                + to_string(el[1])  + "m"
                                + to_string(el[0])  + "_" 
                                + to_string(rep)
                                + nThreads
                                + sleepTime
                                + repIdx
                              );
        
        string const filenameB("./../analysis_new/tuning/" 
                                + getInstanceName() + "/" 
                                + "base_plusBoth"   + "/" 
                                + settings          + "/n"
                                + to_string(el[1])  + "m"
                                + to_string(el[0])  + "_" 
                                + to_string(rep)
                                + nThreads
                                + sleepTime
                                + repIdx
                              );
                
        ResultSingleFile const resultA(filenameA);
        ResultSingleFile const resultB(filenameB);
        
        if (resultA.optimal and resultB.optimal)
        {
          timeA.emplace_back(resultA.time);
          timeB.emplace_back(resultB.time);
        }
        
        else if (resultA.UB > 0 and resultB.UB > 0)
        {
          gapA.emplace_back(resultA.gap);
          gapB.emplace_back(resultB.gap);
        }
        
        else
        {
          lowerbA.emplace_back(resultA.LB);
          lowerbB.emplace_back(resultB.LB);
        }
      }
    }
    
    // ------------------------------
    // --- Print TeX table        ---
    // ------------------------------
    
    if (size(timeA) != size(timeB)
         or size(gapA) != size(gapB)
         or size(lowerbA) != size(lowerbB))
      throw string("How?? (process_compareBoth.cc)");
    
    
    double const sumTimeA = accumulate(cbegin(timeA),   cend(timeA),   0.0);
    double const sumTimeB = accumulate(cbegin(timeB),   cend(timeB),   0.0);
    double const sumGapA  = accumulate(cbegin(gapA),    cend(gapA),    0.0);
    double const sumGapB  = accumulate(cbegin(gapB),    cend(gapB),    0.0);
    double const sumLBA   = accumulate(cbegin(lowerbA), cend(lowerbA), 0.0);
    double const sumLBB   = accumulate(cbegin(lowerbB), cend(lowerbB), 0.0);

    double const avgTimeA = sumTimeA / size(timeA);
    double const avgTimeB = sumTimeB / size(timeB);
    double const avgGapA  = sumGapA  / size(gapA);
    double const avgGapB  = sumGapB  / size(gapB);
    double const avgLBA   = sumLBA   / size(lowerbA);
    double const avgLBB   = sumLBB   / size(lowerbB);    
    
    n_times   += size(timeA);
    n_gaps    += size(gapA);
    n_LowerBs += size(lowerbA);

    sumTime_A += sumTimeA;
    sumTime_B += sumTimeB;
    sumGap_A  += sumGapA;
    sumGap_B  += sumGapB;
    
    if (size(lowerbA) > 0)
    {
      sumLB_A += sumLBA;
      sumLB_B += sumLBB;
    }
    
    cout << fixed
         << "           &      & "
         << setprecision(0) << setw(7) << avgTimeA << " &"
         << setprecision(1) << setw(7) << avgGapA  << " &"
         << setprecision(1) << setw(7) << avgLBA   << " &"
         << setprecision(0) << setw(7) << avgTimeB << " &"
         << setprecision(1) << setw(7) << avgGapB  << " &"
         << setprecision(1) << setw(7) << avgLBB   << " \\\\\n";
  }
  
  cout << "\\midrule\n\\rowstyle{\\itshape}\n"
       << "           & Avg. & " 
       << setprecision(0) << setw(7) << sumTime_A / n_times << " &"
       << setprecision(1) << setw(7) << sumGap_A / n_gaps   << " &"
       << setprecision(1) << setw(7) << sumLB_A / n_LowerBs << " &"
       << setprecision(0) << setw(7) << sumTime_B / n_times << " &"
       << setprecision(1) << setw(7) << sumGap_B / n_gaps   << " &"
       << setprecision(1) << setw(7) << sumLB_B / n_LowerBs << " \\\\ \\bottomrule\n";
}
