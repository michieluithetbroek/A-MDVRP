#include "./laporte_single_customer.ih"

vector<CutReturn> Laporte_single_customer::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  // create directed graph
  // And get the connected components
  
  ListDigraph g;
  graphFunctions::create_listDigraph(g, x);
  
  vector<vector<int>> const v_cc = graphFunctions::LEMON_get_connected_components(g);

 
  // From here run for each component
  for (size_t cc_idx = 0; cc_idx < v_cc.size(); ++cc_idx) 
  {
    vector<int> cc_nodes(v_cc[cc_idx]);
  
   // we have a tour of lenght 1 between two depots
    if (cc_nodes.size() == 1)
    {
      int const cust = cc_nodes[0];
        
      for (int d1: d_iDepots)
      {
        for (int d2: d_iDepots)
        {
          if (d1 == d2)
            continue;
            
          if (x[d1][cust] + x[cust][d2] > 1 + d_eps)
          {
            CutReturn cut;
            cut.add(1, d1, cust);
            cut.add(1, cust, d2);
            cut.rhs = 1;
            cuts.push_back(cut);
          }
        }
      }
      
      if (not cuts.empty())
        return cuts;
    } 
    
    
    //check if at least connected to two depots:
    int cc_nDepots = 0;
    
    for (int const d: d_iDepots)
    {
      for (int const i: cc_nodes)
      {  
        if (x[d][i] + x[i][d] > d_eps)
        {
          ++cc_nDepots;
          break;      
        }
      }
      
      cc_nodes.push_back(d);
    }
    
    // continue if connected to single depot only.
    if (cc_nDepots < 2)
      continue;
      

    
    

  
    
    
    // here we can add arcs between depots and graph!
    for (ListDigraph::NodeIt u(g); u != INVALID; ++u)
    {
      if (g.id(u) >= d_nDepots)
        continue;
      
      for (ListDigraph::NodeIt v(g); v != INVALID; ++v)
      {
        if (g.id(v) < d_nDepots)
          continue;
        
        if (x[g.id(u)][g.id(v)] + x[g.id(v)][g.id(u)] > d_eps)
        {
//           cout << g.id(u) << "-" << g.id(v)  << ": " << x[g.id(u)][g.id(v)] + x[g.id(v)][g.id(u)] << endl;
          g.addArc(u,v);
          g.addArc(v,u);
        }
      }
    }

    
    
    // create a copy of the LEMON graph with only the cc_nodes in it
    ListDigraph::NodeMap<bool> new_nodes(g, false);
    ListDigraph::ArcMap<bool> new_arcs(g, true);
  
    for (ListDigraph::NodeIt u(g); u != INVALID; ++u)
      if (find(cbegin(cc_nodes), cend(cc_nodes), g.id(u)) != cend(cc_nodes))
        new_nodes[u] = true;
  
    using SUB_G = SubDigraph<ListDigraph, ListDigraph::NodeMap<bool>, ListDigraph::ArcMap<bool>>;
    
    SUB_G sub_g(g, new_nodes, new_arcs);

    for (SUB_G::NodeIt i(sub_g); i != INVALID; ++i)
    {
      int i_idx = sub_g.id(i);
      if (sub_g.id(i) < d_nDepots)
        continue;
      
      for (SUB_G::NodeIt j(sub_g); j != INVALID; ++j)
      { 
        if (sub_g.id(j) < d_nDepots)
          continue;
        
        if (sub_g.id(i) == sub_g.id(j))
          continue;
        
        
//         SUB_G sub_g(g, new_nodes, new_arcs);
        
        int j_idx = sub_g.id(j);
//         cout << "(i,j) " << i_idx << " " << j_idx << endl;
        
        vector<int> I;
        vector<int> NotI;
        double sum_i = 0;
        double sum_j = 0;
        
        for (int depot: d_iDepots)
        {
          if (x[depot][i_idx]  >= x[j_idx][depot] )
          {
            I.push_back(depot);
            sum_i += x[depot][i_idx];  
          }
          else
          {
            NotI.push_back(depot);
            sum_j += x[j_idx][depot];
          }
        }
        
          
        if (sum_i + sum_j < 2.0 - d_eps) // True if subtours are gone.
          continue;
        
        
        // add  source depot    
        SUB_G::Node source = sub_g.addNode();
        sub_g.status(source, true);
        
        // include source - i,j edges
        SUB_G::Arc arc_si = sub_g.addArc(source, i);
        sub_g.status(arc_si, true);
        
        SUB_G::Arc arc_sj = sub_g.addArc(source, j);
        sub_g.status(arc_sj, true);
        
        // add sink depot
        SUB_G::Node sink   = sub_g.addNode();
        sub_g.status(sink, true);
        
        // add sink edges
        for (SUB_G::NodeIt u(sub_g); u != INVALID; ++u)
        {
          if (sub_g.id(u) >= d_nDepots)
            continue;
          
          sub_g.status(sub_g.addArc(u, sink), true);
        }
        
        
        SUB_G::ArcMap<double> valEdge_sub_g(sub_g);
        
        for (SUB_G::ArcIt a(sub_g); a != INVALID; ++a)
        {
          int const id_from = sub_g.id(sub_g.source(a));
          int const id_to   = sub_g.id(sub_g.target(a));
          
          // do not add weights based on LP relaxation for dummy depots
          if (id_from >= d_nNodes or id_to >= d_nNodes)
            valEdge_sub_g[a] = 100000;
          
          else
            valEdge_sub_g[a] = (double)x[id_from][id_to] + (double)x[id_to][id_from];
          
//           cout << sub_g.id(sub_g.source(a)) << " - " << sub_g.id(sub_g.target(a)) << " : " << valEdge_sub_g[a] << endl;
        }
      
    
            
        Preflow<SUB_G, SUB_G::ArcMap<double>> flow(sub_g, valEdge_sub_g, source, sink);
        flow.run();
        
        SUB_G::NodeMap<bool> b(sub_g, false);
        flow.minCutMap(b);
        
        vector<int> s_cut_our;
        
//         cout << "SOURCE: " << sub_g.id(source) << endl;
//         cout << "SINK: " << sub_g.id(sink) << endl;
//         
//         cout << "MINIMUM CUT: " << flow.flowValue() << " ------ ";
        
        if (flow.flowValue() < d_eps)
          throw string("Inspecified error (laporte_single_customer::findCuts.cc)");
        
        for (SUB_G::NodeIt n(sub_g); n != INVALID; ++n)
          if (b[n] == 1 and sub_g.id(n) < d_nNodes)
            s_cut_our.push_back(sub_g.id(n));

        
        double sum_ijs = 0;
        
        for (int  el: s_cut_our)
          for (int  el2: s_cut_our)
            sum_ijs += x[el][el2];
            
        
        
        // as i and j will always be in the cut on the source side, cut_size equals 'S+2'
        
        if (sum_ijs + sum_j + sum_i > s_cut_our.size() + d_eps)
        {
          // recalculate cut:
          
//           if (i_idx == 27 or j_idx == 27)
//           {
//             cout << "DEPOT CUT FOUND: " << endl;
//             
//             cout << "LHS: " << sum_ijs + sum_j + sum_i << endl;
//             cout << "RHS: " << s_cut_our.size() << endl;
//             cout << "sumij: " << sum_ijs << endl;
//             cout << "sumjd: " << sum_j << endl;
//             cout << "sumdi: " << sum_i << endl;
//             
//             cout << "CC NODES size: " << cc_nodes.size() << endl;
//           }
          
          CutReturn cut;
          
          for (int idx: I)
            cut.add(1, idx, i_idx);
          
          for (int idx: NotI)
            cut.add(1, j_idx, idx);
                      
          for (int idx: s_cut_our)
            for (int jdx: s_cut_our)
              cut.add(1, idx, jdx);
          
          cut.rhs = s_cut_our.size();
            
          cuts.push_back(cut);
          
          for (int x: {i_idx, j_idx})
          {
            if (find(cbegin(s_cut_our), cend(s_cut_our), x) == cend(s_cut_our))
            {
              cout << "\ni: " << i_idx << '\n' << "j: " << j_idx << endl;
              
              for (auto el: s_cut_our)
                cout << el << " ";
              cout << endl;
              
              throw string("(laporte_single_customer::findCuts.cc)");
            }
          }
        }
        
        // remove fake depots and corresponding edges
        sub_g.erase(source);
        sub_g.erase(sink);
      }
    }
  }

  return cuts;
}
