#include "./Cut_T1comb.ih"

vector<CutReturn> Cut_T1comb::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  for (size_t const depot: d_iDepots)
  {
    vector<size_t> T = {{depot}};
    
    double inOut = 0;
    
    for (size_t const n: d_iNodes)
      inOut += x[n][depot] + x[depot][n];
    
    vector<size_t> cust = d_iCustomers;
    
    // find Teeth
    bool foundTeeth = false;
//     cout << "Init inOut: " << inOut << endl;
    
    while(not cust.empty())
    {
      double best_delta = 100000;
      int    best_cust  = -1;
      
      for (size_t i = 0; i < cust.size(); ++i)
      {
        double const delta = calc_inOut(T, cust[i], x, d_iNodes);
        
        if (delta < best_delta)
        {
          best_delta = delta;
          best_cust = cust[i];
        }
        
        if (best_delta + d_eps < 0)
          break;
      }
      
      if (best_cust == -1 or best_delta - d_eps > 0)
        break;
      
//       cout << "T extended with: " << best_cust << "( " << best_delta << ") " << endl;
      T.push_back(best_cust);
      cust.erase(remove(begin(cust), end(cust), best_cust), end(cust));
      
      inOut += best_delta;
      
//       cout << "inOut: " << inOut << endl;
      if (inOut + d_eps < 2)
      {
        foundTeeth = true;
        break;      
      }
    }

    
    if (not foundTeeth)
      continue;
    
    // find Handle
    
    // insert in H all customers from T (so not the depot)
    vector<size_t> H;
    
    for (int const el: T)
      if (el >= d_nDepots)
        H.push_back(el);
    
    cust = d_iCustomers;
    
    for (size_t const el: H)
      cust.erase(remove(begin(cust), end(cust), el), end(cust));
    
    //initialize H inout
    double HinOut = 0;
    
//     cout << "=================================================\n";
    for (size_t const el: H)
      for (size_t const i: d_iNodes)
        if (find(cbegin(H), cend(H), i) == cend(H))
          HinOut += x[i][el] + x[el][i];
        
//     cout << "init Hinout : " << HinOut << endl;
    
    bool cutFound = false;
    
    while (not cust.empty())
    {
      double best_delta = 100000;
      int    best_cust = -1;
    
      for (size_t i = 0; i < cust.size(); ++i)
      {
        double delta = calc_inOut(H, cust[i], x, d_iNodes);
        
        if (delta < best_delta)
        {
          best_delta = delta;
          best_cust = cust[i];
        }       
      }
      
//       cout << "H extended with: " << best_cust << "( " << best_delta << ")" << endl;
      H.push_back(best_cust);
      cust.erase(remove(begin(cust), end(cust), best_cust), end(cust));
      
      HinOut += best_delta;
      
      if (best_cust == -1)
        break;
      
      if (inOut + HinOut + gg_eps < 4)
      {
        cutFound = true;
        break;
      }
    }
    
//     throw;
    if (not cutFound)
      continue;
    
    // cut is found -> add it
//     cout << "CUT found (T-1 COMB !!!!!!!!!!!!!!!!!!!!!!!)" << endl;
//     
//       
//     cout << "T: ";
//     for (auto el: T )
//       cout << el << " ";
//     cout << endl;
//     
//     cout << "H: ";
//     for (auto el: H)
//       cout << el << " ";
//     cout << endl << endl;
//     throw;
    
    CutReturn cut = calc_T1comb(T, H, x);
    cut.rhs = -4;
 
    cuts.push_back(cut);    
  }
  
  return cuts;
}