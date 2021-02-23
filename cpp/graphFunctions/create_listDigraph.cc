#include "graphFunctions.ih"

/* 
 * The graph is taken by reference since we cannot copy this object..
 * In addition, we remove the depots from the graph, so no edges belonging to the depots will be returned
 */

void graphFunctions::create_listDigraph(ListDigraph &g, 
                                        vector<vector<double>> const &x
                                       )
{
  for (int i = 0, last = graphFunctions::d_nNodes; i < last; ++i)
    g.addNode();
  
  for (ListDigraph::NodeIt u(g); u != INVALID; ++u)
  {
    if (g.id(u) < graphFunctions::d_nDepots)
      continue;
    
    for (ListDigraph::NodeIt v(g); v != INVALID; ++v)
    {
      if (g.id(v) < graphFunctions::d_nDepots)
        continue;

      if (g.id(v) <= g.id(u))
        continue;
      
      if (x[g.id(u)][g.id(v)] + x[g.id(v)][g.id(u)] > 0.0001)
      {
        g.addArc(u, v);
        g.addArc(v, u);
      }
    }
  }
}

// void graphFunctions::create_listDigraph(ListDigraph &g, 
//                                         vector<vector<double>> const &x
//                                        )
// {
//   for (int i = 0, last = x.size(); i < last; ++i)
//     g.addNode();
//   
//   for (ListDigraph::NodeIt u(g); u != INVALID; ++u)
//   {
//     if (g.id(u) < d_nDepots)
//       continue;
//     
//     for (ListDigraph::NodeIt v(g); v != INVALID; ++v)
//     {
//       if (g.id(v) < d_nDepots)
//         continue;
// 
//       if (g.id(v) <= g.id(u))
//         continue;
//       
//       if (x[g.id(u)][g.id(v)] + x[g.id(v)][g.id(u)] > 0.0001)
//       {
//         g.addArc(u, v);
//         g.addArc(v, u);
//       }
//     }
//   }
// }