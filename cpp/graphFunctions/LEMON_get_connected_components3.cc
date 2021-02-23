#include "graphFunctions.ih"

/* 
 * This gets the connected components without the depots
 * If you already have a directed graph g, then it's more 
 * efficient to call the function with that graph
 * 
 */

vector<vector<int>> graphFunctions::LEMON_get_connected_components (vector<vector<double>> const &x)
{
  ListDigraph g;
  create_listDigraph(g, x);
  
  return graphFunctions::LEMON_get_connected_components(g);
}