#include "graphFunctions.ih"

/* 
 * This gets the connected components without the depots
 * The graph is taken by reference and adjusted!
 * 
 */



vector<vector<int>> graphFunctions::LEMON_get_connected_components(ListDigraph const &g)
{
  ListDigraph::NodeMap<int> a(g);
  Undirector<ListDigraph const> undirected_g(g);
  connectedComponents(undirected_g, a);
  
  vector<vector<int>> v_cc;
  
  for (int n = 0; n != graphFunctions::d_nNodes; ++n)
  {
    vector<int> cc;
    
    for (ListDigraph::NodeIt u(g); u != INVALID; ++u)
      if (a[u] == n and g.id(u) >= d_nDepots)
        cc.push_back(g.id(u));
      
    if (cc.empty())
      break;
        
    v_cc.push_back(cc);
  }
  
  return v_cc;
}



// vector<vector<int>> graphFunctions::LEMON_get_connected_components(ListDigraph const &g)
// {
//   ListDigraph::NodeMap<int> a(g);
//   
//   Undirector<ListDigraph const> undirected_g(g);
//   connectedComponents(undirected_g, a);
//   
//   vector<vector<int>> v_cc;
//   
//   for (ListDigraph::NodeIt v(g); v != INVALID; ++v)
//   {
//     vector<int> cc;
//     
//     for (ListDigraph::NodeIt u(g); u != INVALID; ++u)
//       if (a[u] == a[v] and g.id(u) >= d_nDepots)
//         cc.push_back(g.id(u));
//       
//     if (cc.empty())
//       break;
//         
//     v_cc.push_back(cc);
//   }
//   
//   return v_cc;
// }