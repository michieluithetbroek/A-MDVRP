#include "./../../main.ih"

void process_mergeRoots(string filename);

void process_all_roots()
{
//   process_mergeRoots("roots_withoutCplexCuts_withoutGurobi_0");
//   process_mergeRoots("roots_withoutCplexCuts_withoutGurobi_2000");
//   process_mergeRoots("roots_withoutCplexCuts_withoutGurobi_100000");
//   
//   process_mergeRoots("roots_withCplexCuts_withoutGurobi_0"); 
//   process_mergeRoots("roots_withCplexCuts_withoutGurobi_2000");
//   process_mergeRoots("roots_withCplexCuts_withoutGurobi_100000");
  
  
  
  process_roots("roots_withoutCplexCuts_withoutGurobi_0"); 
  process_roots("roots_withoutCplexCuts_withoutGurobi_2000");
  process_roots("roots_withoutCplexCuts_withoutGurobi_100000");
  
//   process_roots("roots_withCplexCuts_withoutGurobi_0"); 
//   process_roots("roots_withCplexCuts_withoutGurobi_2000");
//   process_roots("roots_withCplexCuts_withoutGurobi_100000");
}


/*
 * Merge the best UB into the file with roots
 * We also calculate the root node gap for each setting
 * 
 */

void process_mergeRoots(string filename)
{
  int constexpr nLines    = 720;                                         
  int constexpr nSettings = 6; // number of columns of file to read in
  
  string const filename_1 = "./results_tmp/bestSols_short";
  string const filename_2 = "./results_tmp/" + filename;
  
  ifstream file_UB    (filename_1);
  ifstream file_roots (filename_2);
  
  if (not file_UB.is_open())
    throw string("I couldn't open: " + filename_1 + " (process_mergeRoots)");
  
  if (not file_roots.is_open())
    throw string("I couldn't open: " + filename_2 + " (process_mergeRoots)");
  
  ofstream file_out ("./results_tmp/extended_" + filename);
  
  string dummy;
  getline(file_UB, dummy);
  
  for (int idx_line = 0; idx_line < nLines; ++idx_line)
  {
    string name1, name2;
    int n1, n2, m1, m2, rep1, rep2, opt;
    double UB;
    
    file_UB    >> name1 >> n1 >> m1 >> rep1 >> UB >> opt;
    file_roots >> name2 >> n2 >> m2 >> rep2;
    
    if (name1 != name2 or n1 != n2 or m1 != m2 or rep1 != rep2)
      throw string("I am reading different instances (process_mergeRoots)");
      
    file_out << fixed << setprecision(0)
             << setw(12) << name1 << ' '
             << setw(3)  << n1    << ' '
             << setw(4)  << m1    << ' '
             << setw(2)  << rep1  << ' '
             << setw(7)  << UB    << ' '
             << setw(2)  << opt   << " | "
             << fixed << setprecision(2);
    
    vector<double> all_obj(nSettings, 0);
            
    for (int idx = 0; idx < nSettings; ++idx)
    {
      string val1, val2;
      
      file_roots >> val1;
      
      if (val1 == string("|"))
        file_roots >> val1;
      
      file_roots >> val2;
      
      double const obj = stod(val1);
      double const gap = 100 * (UB - obj) / UB;
      
      all_obj[idx] = obj;
      
      file_out << setw(10) << val1 << ' '
               << setw(6)  << (UB != -1 ? gap : -1) << ' '
               << setw(4)  << stoi(val2) << ' ';
    }
    
    if (UB == -1)
      file_out << " | " << setw(7) << '*';
    
    else
    {
      double const gap1 = UB - all_obj[0];
      double const gap6 = UB - all_obj[5];
      
      double const deltaGap = 100 * (gap1 - gap6) / gap1;
      
      file_out << " | " << setw(7) << deltaGap;
    }
    
    file_out << setw(2) << (all_obj[0] <= all_obj[1])
             << setw(2) << (all_obj[3] <= all_obj[4]);
             
             
    // Is both better than only laporte and only DK?
    // 0 is worse, 1 is equal, 2 is better
             
    int tmp1 = 1;
    int tmp2 = 1;
    
    if (all_obj[2] > max(all_obj[0], all_obj[1]))
      tmp1 = 2;
    
    else if (all_obj[2] < max(all_obj[0], all_obj[1]))
      tmp1 = 0;
    
    if (all_obj[5] > max(all_obj[3], all_obj[4]))
      tmp2 = 2;
    
    else if (all_obj[5] < max(all_obj[3], all_obj[4]))
      tmp2 = 0;
    
    file_out << setw(2) << tmp1
             << setw(2) << tmp2 << endl; 
  }
}







void process_roots(string filename)
{
  int constexpr nSettings = 6;
  
  string const fileName = "./results_tmp/extended_" + filename;
  ifstream file_in (fileName);
  
  if (not file_in.is_open())
    throw string("I couldn't open: " + fileName + " (process_mergeRoots)");
  
  cout << "\n\nresults for: " << filename << endl << endl;
  
  string type_prev;
  
  int    cnt       = 0;
  double delta_sum = 0;
  double delta_min = numeric_limits<double>::max();
  double delta_max = numeric_limits<double>::min();
  
  array<double, nSettings> obj_sum = {0, 0, 0, 0, 0, 0};
  
  stringstream stable;
  stable << fixed << setprecision(2);
  
  int cnt1 = 0;
  int cnt2 = 0;
  
  // Read all lines from the input file
  for (string line, type_curr; 
       getline(file_in, line); 
       ++cnt, type_prev = type_curr)
  {
    stringstream sline(line);
    
    string dummy;
    sline >> type_curr >> dummy >> dummy >> dummy >> dummy >> dummy >> dummy;
    
    // If we start reading a new problem type
    // Then we first print the results of the previous type
    // cnt > 0 is used such that we do not have to set 
    // 'type_prev' for the first line
    
    if (cnt > 0 and type_prev != type_curr)
    {
      cout << fixed << setprecision(2)
           << setw(12) << type_prev
           << setw(4)  << cnt 
           << setw(7)  << delta_sum / cnt
           << setw(7)  << delta_min
           << setw(7)  << delta_max << endl;
      
      // Print TeX table
      stable << setw(10) << "&   & ";
      
      for (int idx = 0; idx < nSettings; ++idx)
        stable << setw(9) << obj_sum[idx] / cnt << " & ";
           
      stable << setw(6) << delta_sum / cnt << " & "
             << setw(6) << delta_max << " \\\\" << endl;
        
      cnt       = 0;
      delta_sum = 0;
      delta_min = numeric_limits<double>::max();
      delta_max = numeric_limits<double>::min();
      obj_sum   = {0, 0, 0, 0, 0, 0};
    }
    
    
    // Process the new line
    
    for (int idx = 0; idx < nSettings; ++idx)
    {
      double obj;
      sline >> obj >> dummy >> dummy;

      obj_sum[idx] += obj;
    }
  
    string delta;
    int tmp1, tmp2;
    sline >> dummy >> delta >> tmp1 >> tmp2;
    
    cnt1 += tmp1;
    cnt2 += tmp2;
    
    if (delta != string("*"))
    {
      double d = stod(delta);
      
      delta_sum += d;
      
      delta_min = min(d, delta_min);
      delta_max = max(d, delta_max);
    }
    
    
    type_prev = type_curr;
  }
  
  // Print results of the last type
  cout << fixed << setprecision(2)
        << setw(12) << type_prev
        << setw(4)  << cnt 
        << setw(7)  << delta_sum / cnt
        << setw(7)  << delta_min
        << setw(7)  << delta_max << endl << endl
        << setw(5)  << cnt1 << endl
        << setw(5)  << cnt2 << endl << endl;
  
  // Print TeX table
  stable << fixed << setprecision(2)
         << setw(10) << "&   & ";
  
  for (int idx = 0; idx < nSettings; ++idx)
    stable << setw(9) << obj_sum[idx] / cnt << " & ";
        
  stable << setw(6) << delta_sum / cnt << " & "
         << setw(6) << delta_max << " \\\\" << endl;
             
  cout << stable.str() << endl;
}
