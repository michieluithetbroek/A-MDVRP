#include "./Cut_Tcomb.ih"

vector<vector<size_t>> Cut_Tcomb::create_tooth(vector<vector<double>> const &x, 
                                               vector<size_t> cc_nodes) const
{
  vector<vector<size_t>> tooth(d_nDepots, vector<size_t>());

  for (size_t depot: d_iDepots)
  {
    if (find(cbegin(cc_nodes), cend(cc_nodes), depot) == cend(cc_nodes))
      continue;
    
    vector<size_t> T = {{depot}};
    
    double inOut = 0;
    
    for (size_t const n: d_iNodes)
      inOut += x[n][depot] + x[depot][n];
    
    vector<size_t> cust = cc_nodes;
    
    if (cc_nodes.size() <= 4)
      continue;
    
    // remove depots 
    for (int i = 0, n = cust.size(); i < n; ++i)
      if (i < d_nDepots)
        cust.erase(remove(begin(cust), end(cust), i), end(cust));
    
    while(not cust.empty())
    {
      
      double best_delta = 100000;
      int best_cust = -1;
      
      for (size_t i = 0; i < cust.size(); ++i)
      {
        double delta = calc_inOut(T, cust[i], x, d_iNodes);
        
        if (delta < best_delta)
        {
          best_delta = delta;
          best_cust = cust[i];
        }   
        
        if (best_delta + gg_eps < 0)
          break;
      }
      
      if (best_cust == -1 or best_delta - gg_eps > 0)
        break;
      
//       cout << "T extended with: " << best_cust << "( " << best_delta << ") " << endl;
      T.push_back(best_cust);
      cust.erase(remove(begin(cust), end(cust), best_cust), end(cust));
      
      inOut += best_delta;
      
//       cout << "inOut: " << inOut << endl;
      if (inOut + gg_eps < 2)
        break;      
    }
    
    tooth[depot] = T;
  }
  
  return tooth;
}