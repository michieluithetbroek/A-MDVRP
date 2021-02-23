#include "./Cut_comb.ih"

/*
 * lhs is used to check whether it actually is a cut
 */

CutReturn Cut_comb::calc_strengthened_comb_cut (double &lhs, int nTeeth, 
                                                vector<vector<int>> const &inTooth,
                                                vector<vector<double>> const &x) const
{
  CutReturn cut;
  
  for (int t = 0; t <= nTeeth; ++t)
  {
    for (int jdx = 1, m = inTooth.size(); jdx < m; ++jdx) // nodes start numbering at 1
    {
      if (inTooth[jdx][t] == 0)   // not in teeth t, so continue
        continue;
      
      int j_idx = jdx + d_nDepots - 1; // j_idx to index in our data structure
      
      if (jdx >= d_nCustomers + 1)
        j_idx = jdx - d_nCustomers - 1; 
      
      // summ all edges going outside/inside the teeth
      for (int idx = 1, n = inTooth.size(); idx < n; ++idx)
      {
        if (idx == jdx)
          continue;
        
        if (inTooth[idx][t] == 1)
          continue; 
        
        int i_idx = idx + d_nDepots - 1;
        
        if (idx >= d_nCustomers + 1)
          i_idx = idx - d_nCustomers - 1;
        
//         if (i_idx == 15 and j_idx == 5)
//           cout << endl << "--" << endl;
        
        lhs -= x[j_idx][i_idx] - x[i_idx][j_idx];   // + x[i_idx][j_idx];
//         expr += d_x[j_idx][i_idx] + d_x[i_idx][j_idx];// + d_x[i_idx][j_idx];
        
        cut.add(-1, j_idx, i_idx);
        cut.add(-1, i_idx, j_idx);
      }
    }
  }
  
  return cut;
}