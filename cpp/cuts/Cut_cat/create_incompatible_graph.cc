#include "./Cut_cat.ih"

/* 
 * creates incompatibility graph
 * 
 * TODO Should we move this to graphFunctions namespace?
 */

bool Cut_cat::create_incompatible_graph(vector<vector<double>> const &x, 
                                        ListGraph &graph, 
                                        map<int, pair<int, int>> &map_in) const
{
  bool empty_graph = true;
  
  for (ListGraph::NodeIt u(graph); u != INVALID; ++u)
  {
    pair<int, int> const &info_u = map_in[graph.id(u)];
    
    for (ListGraph::NodeIt v(graph); v != INVALID; ++v)
    {
      if (graph.id(v) <= graph.id(u))
        continue;
      
      pair<int, int> const &info_v = map_in[graph.id(v)];
      
      if ( incompatible(info_v, info_u) or incompatible(info_u, info_v)) 
      {
        graph.addEdge(u,v);
        empty_graph = false;
      }
    }
  }
  
  return empty_graph;
}