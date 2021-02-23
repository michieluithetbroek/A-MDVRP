#include "./Cut_cat.ih"

/*
 * 
 * TODO maybe this should be a function of the namespace graphFunctions
 */

void Cut_cat::set_bipart_val_edge(ListGraph::EdgeMap<double> &val_edge,
                                  ListGraph::EdgeMap<double> &valEdge,
                                  ListGraph::NodeMap<tuple<int, int>> &valNode,
                                  ListGraph &bipart_graph,
                                  ListGraph &graph) const
{
  for (ListGraph::EdgeIt e(bipart_graph); e != INVALID; ++e)
  {
    auto const &from = bipart_graph.u(e);
    auto const &to   = bipart_graph.v(e);
    
    int const node_idx_from = get<0>(valNode[from]);
    int const node_idx_to   = get<0>(valNode[to]);
    
    // search corresponding arc in graph:
    for (ListGraph::EdgeIt a(graph); a != INVALID; ++a)
    {
      if (graph.id(graph.u(a)) != node_idx_from or graph.id(graph.v(a)) != node_idx_to)
        continue;
      
      val_edge[e] = valEdge[a];
    }   
  }
}