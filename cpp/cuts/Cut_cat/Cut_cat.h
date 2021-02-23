#pragma once

#include "./../cut.h"

#include <map>
#include <utility>
#include <tuple>
#include <lemon/list_graph.h>

class Cut_cat: public Cut
{
  int const d_nDepots;
  int const d_nNodes;

  public:
    
    Cut_cat (int priority, bool lazy, bool user,
             bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut       (priority, lazy, user, stopIfFound, onlyRootNode, std::string("cat")),
      d_nDepots (data.d_nDepots),
      d_nNodes  (data.d_nNodes)
    {};
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------
    
    // TODO Why are these function given as memberfunctions?
    // We may move them to the graphFunctions namespace
    
    bool is_simple(std::vector<int> cycle) const;
    
    std::map<int, std::pair<int, int>> create_edge_map (std::vector<std::vector<double>> const &x, 
                                                        lemon::ListGraph &graph) const;
                                                        
    int create_bipart_graph (lemon::ListGraph &bipart_graph,
                             lemon::ListGraph const &graph,
                             lemon::ListGraph::NodeMap<std::tuple<int, int>> &valNode,
                             std::map<int, std::pair<int, int>> &map) const;
    
    bool create_incompatible_graph (std::vector<std::vector<double>> const &x,
                                        lemon::ListGraph &graph,
                                        std::map<int, std::pair<int, int>> &map) const;
    
    void create_valEdge (std::vector<std::vector<double>> const &x,
                         lemon::ListGraph &graph,
                         std::map<int, std::pair<int, int>> &map,
                         lemon::ListGraph::EdgeMap<double> &valEdge) const;
    
    void set_bipart_val_edge (lemon::ListGraph::EdgeMap<double> &val_edge,
                              lemon::ListGraph::EdgeMap<double> &valEdge,
                              lemon::ListGraph::NodeMap<tuple<int, int>> &valNode,
                              lemon::ListGraph &bipart_graph,
                              lemon::ListGraph &graph) const;
                              
    bool incident (lemon::ListGraph::Node &u,
                   lemon::ListGraph::Node &v,
                   lemon::ListGraph::Node &vprime,
                   lemon::ListGraph &bipart_graph,
                   int nNodes) const;
                   
    bool incompatible(std::pair<int, int> const &info_v,
                      std::pair<int, int> const &info_u) const;
};