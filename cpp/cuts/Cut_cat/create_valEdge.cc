#include "./Cut_cat.ih"

/* 
 * creates valEdge, a edgemap with edge weight in it
 * 
 * TODO Should we move this to graphFunctions namespace?
 */

void Cut_cat::create_valEdge(vector<vector<double>> const &x,
                             ListGraph &graph,
                             map<int, pair<int, int>> &map,
                             ListGraph::EdgeMap<double> &valEdge) const
{
  for (ListGraph::EdgeIt a(graph); a != INVALID; ++a)
  {
    pair<int, int> const &info_from = map[graph.id(graph.u(a))];
    pair<int, int> const &info_to   = map[graph.id(graph.v(a))];
    
    valEdge[a] = 1.0001 
                 - x[info_from.first][info_from.second] 
                 - x[info_to.first][info_to.second];
  } 
}