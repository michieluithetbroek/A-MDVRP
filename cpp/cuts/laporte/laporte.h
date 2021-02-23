#pragma once

#include "./../cut.h"

class Laporte: public Cut
{
  double const d_eps = 0.000001;
  
  int const d_nDepots;
  int const d_nNodes;
  
  vector<size_t> const d_iDepots;
  
  public:
    
    Laporte (int priority, bool lazy, bool user, 
             bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut       (priority, lazy, user, stopIfFound, onlyRootNode, std::string("Laporte")),
      d_nDepots (data.d_nDepots),
      d_nNodes  (data.d_nNodes),
      d_iDepots (data.d_iDepots)
    {};
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------
    

};