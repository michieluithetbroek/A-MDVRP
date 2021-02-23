#include "./Cut_cat.ih"

/*
 * 
 * TODO maybe this should be a function of the namespace graphFunctions
 */

bool Cut_cat::incident (ListGraph::Node &u,
                        ListGraph::Node &v,
                        ListGraph::Node &vprime,
                        ListGraph &bipart_graph,
                        int nNodes) const
{
  for (ListGraph::IncEdgeIt e(bipart_graph, vprime); e != INVALID; ++e)
    if (u == bipart_graph.u(e) or u == bipart_graph.v(e) )
      return true;
      
  return false;
}