#include "./Cut_cat.ih"

/*
 * Returns a map that links node to edge, and by reference adds nodes to graph
 * 
 * TODO maybe this should be a function of the namespace graphFunctions
 */

map<int, pair<int, int>> Cut_cat::create_edge_map(vector<vector<double>> const &x, ListGraph &graph) const
{
  map<int, pair<int, int>> map; // maps  node to arc (int, int)
  
  int ctr = 0;
  for (int i = 0; i != d_nNodes; ++i)
    for (int j = 0; j != d_nNodes; ++j)
      if (x[i][j] > 0.0001)
      {
        map[ctr++] = make_pair(i,j);
        graph.addNode();
      }
      
  return map;
} 