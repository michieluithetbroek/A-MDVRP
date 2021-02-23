#pragma once

#include "./../cut.h"

class Cut_Tcomb: public Cut
{
  int const d_nDepots;
  int const d_nNodes;
  
  std::vector<size_t> const d_iDepots;
  std::vector<size_t> const d_iNodes;
  
  public:
    
    Cut_Tcomb (int priority, bool lazy, bool user, 
               bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut       (priority, lazy, user, stopIfFound, onlyRootNode, std::string("Tcomb")),
      d_nDepots (data.d_nDepots),
      d_nNodes  (data.d_nNodes),
      d_iDepots (data.d_iDepots),
      d_iNodes  (data.d_iNodes)
    {};
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------
    
    double calc_inOut      (std::vector<size_t> const &T, 
                            size_t new_cust, 
                            std::vector<std::vector<double>> const &x, 
                            std::vector<size_t> const &d_iNodes) const;
                       
    CutReturn create_Tcomb (std::vector<std::vector<size_t>> const &tooth,
                            std::vector<size_t> const &H) const;
                            
    bool pairwise_disjoint (std::vector<std::vector<size_t>> const &tooth) const;
    
    double calc_cutset     (std::vector<size_t> const &t,
                            std::vector<std::vector<double>> const &x) const;
    
                            
    bool span_complete_connected_component (std::vector<std::vector<size_t>> const &teeth,
                                            std::vector<size_t> const &cc) const;
    
    std::vector<std::vector<size_t>> create_tooth (std::vector<std::vector<double>> const &x, 
                                                   std::vector<size_t> cc_nodes) const;

};