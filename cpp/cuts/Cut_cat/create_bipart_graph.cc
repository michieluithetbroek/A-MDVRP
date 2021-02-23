#include "./Cut_cat.ih"

/*
 * 
 */

int Cut_cat::create_bipart_graph(ListGraph &bipart_graph, 
                                 ListGraph const &graph, 
                                 ListGraph::NodeMap<tuple<int, int>> &valNode, 
                                 map<int, pair<int, int>> &map_in) const
{
  int nNodes = 0;
  
  // copy all nodes in bipart_graph
  for (ListGraph::NodeIt u(graph); u != INVALID; ++u)
  {
    ++nNodes;
    bipart_graph.addNode();    
  }
  
  for (ListGraph::NodeIt u(graph); u != INVALID; ++u)
    bipart_graph.addNode();    
  
  
  // for every node: corresponding idx of node in edge-weighted graph + left(0) 
  // or right (1) in bipartite graph
  
  int c = 0;
  
  for (ListGraph::NodeIt u(bipart_graph); u != INVALID; ++u)
  {
    if (c < nNodes)
      valNode[u] = make_tuple(c, 0);
    else
      valNode[u] = make_tuple(c - nNodes, 1);
    
    ++c;
  }
  
  for (ListGraph::NodeIt u(bipart_graph); u != INVALID; ++u)
  {
    int const from = get<0>(valNode[u]);
    
    pair<int, int> const &from_info = map_in[from];
    
    for (ListGraph::NodeIt v(bipart_graph); v != INVALID; ++v)
    {
      int const to = get<0>(valNode[v]);
      
      pair<int, int> const &to_info = map_in[to];

      if (to <= from)
        continue;
      
      if (get<1>(valNode[u]) == get<1>(valNode[v]))
        continue;
      
      if (incompatible(from_info, to_info) or incompatible(to_info, from_info))
        bipart_graph.addEdge(u,v);
    }
  }
  
  return nNodes;
}