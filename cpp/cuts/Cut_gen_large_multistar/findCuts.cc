#include "./Cut_gen_large_multistar.ih"

vector<CutReturn> Cut_gen_large_multistar::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  vector<int> const custList = call_lysgard_gen_large_multistar(x);
  
  if (custList.empty())
    return cuts;
    
  CutReturn cut;
  
  double lhs = 0;
  double NN = 0;
  
  // add Qx(N:N)
  for (int i = 0, n = custList.size(); i != n; ++i)
  {
    for (int j = 0, m = custList.size(); j != m; ++j)
    {
      if (i != j)
      {
        NN  += x[custList[i] + d_nDepots - 1][custList[j] + d_nDepots - 1];
        lhs += (d_vehicleCap * x[custList[i] + d_nDepots - 1][custList[j] + d_nDepots - 1]);
        
        cut.add(d_vehicleCap, custList[i] + d_nDepots - 1, custList[j] + d_nDepots - 1);
      }
    }
  }
  
      
  // add q_jx(N:j)
  double NtoElse = 0;
  
  for (int const i: d_iNodes)
  {
    double NtoJ = 0;

    if (find(cbegin(custList), cend(custList), i - d_nDepots + 1) != cend(custList))
      continue;
    
    for (int const j: custList)
    {
      NtoJ += x[i][j + d_nDepots - 1] + x[j + d_nDepots - 1][i];
      lhs  += (d_demands[i] * x[i][j + d_nDepots - 1]) + (d_demands[i] * x[j + d_nDepots - 1][i]);
      
      cut.add(d_demands[i], i, j + d_nDepots - 1);
      cut.add(d_demands[i], j + d_nDepots - 1, i);   
    }
    
    NtoElse += NtoJ;
    NtoJ = 2 * NtoJ * (double)d_demands[i] / (double)d_vehicleCap;
  }
  
  double rhs = (double) d_vehicleCap * custList.size();
  
  for (int const el: custList)
    rhs -= d_demands[el + d_nDepots - 1];
    
  cut.rhs = rhs;
  
  if (lhs - d_eps > rhs)
    cuts.push_back(cut);
  
  return cuts;
}