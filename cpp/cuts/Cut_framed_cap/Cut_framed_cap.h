#pragma once

#include "./../cut.h"

#include <cvrpsep.h>

class Cut_framed_cap: public Cut
{
  double const d_eps = 0.000001;
  double const d_minViolation = 0.1;  // Small violations does not result in a cut
  
  int const d_nDepots;
  int const d_nCustomers;
  int const d_vehicleCap;
  
  std::vector<size_t> const d_iNodes;
  
  std::vector<int> d_lysgard_demand;
  
  public:
    
    Cut_framed_cap (int priority, bool lazy, bool user, 
                    bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut              (priority, lazy, user, stopIfFound, onlyRootNode, std::string("framed_cap")),
      d_nDepots        (data.d_nDepots),
      d_nCustomers     (data.d_nCustomers),
      d_vehicleCap     (data.d_vehicleCap),
      d_iNodes         (data.d_iNodes),
      d_lysgard_demand (data.lysgard_demand())
    { };
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------

    CnstrMgrPointer call_lysgard_framed_cap(std::vector<std::vector<double>> const &x);    
};