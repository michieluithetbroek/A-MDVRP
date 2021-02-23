#pragma once

#include <vector>
#include <map>
#include <utility>

#include <lemon/list_graph.h>
#include <lemon/euler.h>
#include <lemon/concepts/graph_components.h>
#include <lemon/adaptors.h>
#include <lemon/hao_orlin.h>
#include <lemon/preflow.h>
#include <lemon/dijkstra.h>
#include <lemon/edmonds_karp.h>

using namespace std;


/*
 * This namespace provides some functions that are typically used to find cuts
 * 
 * It requires the EMON library
 * 
 */

namespace graphFunctions
{
  
  // An unnamed namespace is only accessible from within the current namespace
  // You can compare it with private datamembers of a class
  //
  // The attributes are used! But in external files.
  // We indicate that they are unused to avoid several hundreds of warnings..

//   namespace
//   {
    double const d_eps = 0.001;
    
    extern int d_nDepots;
    extern int d_nCustomers;
    extern int d_nNodes;
//     extern int d_vehicleCap;
    
    extern std::vector<size_t> d_iDepots;
    extern std::vector<size_t> d_iCustomers;
    extern std::vector<size_t> d_iNodes;
//   }
  
  void setValues(
                  int nDepots, int nCustomers, int nNodes,
                  std::vector<size_t> const &iDepots,
                  std::vector<size_t> const &iCustomers,
                  std::vector<size_t> const &iNodes
                );
  
  
  
  void create_listDigraph (lemon::ListDigraph &g, std::vector<std::vector<double>> const &x);
  
  /*
   * The following functions return a vector containing
   * weakly connected components. You can call the functions
   * with a ListGraph, a ListDiGraph, or a with given LP relaxation
   */
  
  std::vector<std::vector<int>> LEMON_get_connected_components (lemon::ListGraph const &g);
  std::vector<std::vector<int>> LEMON_get_connected_components (lemon::ListDigraph const &g);
  std::vector<std::vector<int>> LEMON_get_connected_components (std::vector<std::vector<double>> const &x);
  
  void get_connected_components_including_depot (std::vector<std::vector<double>> const &x, 
                                                 int *ncomp, int **compscount, int **comps);

  
  
  /*
   * Transform graphs
   * 
   */
  
  void transform_to_lysgard_graph_single_depot(std::vector<std::vector<double>> const &x, 
                                               std::vector<int> &edgeTail,
                                               std::vector<int> &edgeHead, 
                                               std::vector<double> &edgeX);
}
