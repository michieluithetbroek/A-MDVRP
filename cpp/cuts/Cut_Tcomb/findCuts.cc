#include "./Cut_Tcomb.ih"

vector<CutReturn> Cut_Tcomb::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  // we are going to create tooth vectors for each depot
  int ncomp = 0;
  int *compscount;
  int *comps;
  
  graphFunctions::get_connected_components_including_depot(x, &ncomp, &compscount, &comps);
  
  int ctr = 0;
  for (int cc_idx = 0; cc_idx < ncomp; ++cc_idx) 
  {
    vector<size_t> cc_nodes;
    
    for (int j = 0; j != compscount[cc_idx]; ++j)
      cc_nodes.push_back( (size_t) comps[++ctr - 1]);
  
    vector<vector<size_t>> const tooth = create_tooth(x, cc_nodes);
    
    
    int constexpr ntry   = 1000;
    int constexpr nteeth = 3;
    
    bool found = false;
    
    for (int i = 0; i < ntry and not found; ++i)
    {
      vector<int> selected_teeth(d_nDepots, 0);
      
      iota(begin(selected_teeth), end(selected_teeth), 0);
      shuffle(begin(selected_teeth), end(selected_teeth), random2::engine());

      vector<vector<size_t>> tooth_comb(nteeth, vector<size_t>());
      
      for (int j = 0; j != nteeth; ++j)
        tooth_comb[j] = tooth[selected_teeth[j]];

      if (not pairwise_disjoint(tooth_comb))
        continue;
          
      if (span_complete_connected_component(tooth_comb, cc_nodes))
        continue;
      
      
      // search for handle;
      vector<size_t> H = cc_nodes;
      
      // remove depots 
      
      for (int i = 0; i != d_nDepots; ++i)
        if (i < d_nDepots)
          H.erase(remove(begin(H), end(H), i), end(H));

      double lhs = 0;
      
      for (vector<size_t> const &t: tooth_comb)
        lhs += calc_cutset(t, x);

      double HinOut = calc_cutset(H, x);
      
      while (true)
      {
        int best_cust  = -1;
        int best_delta = 100;
        
        for (int const el: H)
        {
          // check if in tooth
          bool found = false;
          
          for (vector<size_t> const &t: tooth_comb)
            if (find(cbegin(t), cend(t), el) != cend(t))
              found = true;
            
          if (found)
            continue;
          
          vector<size_t> tmp_h = H;
          
          tmp_h.erase(remove(begin(tmp_h), end(tmp_h), el), end(tmp_h));
          
          double const delta = calc_cutset(tmp_h, x) - calc_cutset(H, x);
          
//           cout << "el" << el << "-" << delta << endl;
          
          if (delta < best_delta)
          {
            best_cust = el;
            best_delta = delta;
          }
          
        }
        
        HinOut += best_delta;
        
        if (best_cust == -1)
          break;
        
        H.erase(remove(begin(H), end(H), best_cust), end(H));
      
        if (HinOut + lhs < 2 * tooth_comb.size() + 2 - gg_eps)
        {
          CutReturn cut = create_Tcomb(tooth_comb, H);
          
          cut.rhs = - (2 * tooth_comb.size() + 2);
          
          cuts.push_back(cut);
        }
      }
    }
  }
  
  free(compscount);
  free(comps);

  return cuts;
}