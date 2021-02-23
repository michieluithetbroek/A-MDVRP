#include "graphFunctions.ih"

/* 
 * This gets the connected components without the depots !!!!!!
 * TODO Deze word niet gebruikt, ook niet zeker of die goed is
 * 
 */

vector<vector<int>> graphFunctions::LEMON_get_connected_components(ListGraph const &g)
{
  ListGraph::NodeMap<int> a(g);

  connectedComponents(g, a);
  
  vector<vector<int>> v_cc;
  
  for (int n = 0; n != graphFunctions::d_nNodes; ++n)
  {
    vector<int> cc;
    
    for (ListGraph::NodeIt u(g); u != INVALID; ++u)
      if (a[u] == n)
        cc.push_back(g.id(u));
      
    if (cc.empty())
      break;
        
    v_cc.push_back(cc);
  }
  
  return v_cc;
}

// vector<vector<int>> graphFunctions::LEMON_get_connected_components(ListGraph const &g)
// {
//   ListGraph::NodeMap<int> a(g);
// 
//   connectedComponents(g, a);
//   
//   vector<vector<int>> v_cc;
//   
//   
//   for (ListGraph::NodeIt v(g); v != INVALID; ++v)
//   {
//     vector<int> cc;
//     
//     for (ListGraph::NodeIt u(g); u != INVALID; ++u)
//       if (a[u] == a[v])
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