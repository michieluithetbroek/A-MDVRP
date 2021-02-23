#pragma once

#include "./../cut.h"

#include <cvrpsep.h>

class Cut_hypotour: public Cut
{
  int const d_nDepots;
  int const d_nCustomers;
  int const d_nNodes;
  int const d_vehicleCap;
  
  std::vector<size_t> const d_iDepots;

  std::vector<int> d_lysgard_demand;
  
  public:
    
    Cut_hypotour (int priority, bool lazy, bool user, 
                  bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut              (priority, lazy, user, stopIfFound, onlyRootNode, std::string("hypotour")),
      d_nDepots        (data.d_nDepots),
      d_nCustomers     (data.d_nCustomers),
      d_nNodes         (data.d_nNodes),
      d_vehicleCap     (data.d_vehicleCap),
      d_iDepots        (data.d_iDepots),
      d_lysgard_demand (data.lysgard_demand())
    {};
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------
    
    CnstrMgrPointer call_lysgard_hypotour(std::vector<std::vector<double>> const &x);
};