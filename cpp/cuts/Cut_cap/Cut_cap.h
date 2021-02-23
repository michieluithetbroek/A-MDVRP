#pragma once

#include "./../cut.h"

class Cut_cap: public Cut
{
  int const d_nDepots;
  int const d_nCustomers;
  int const d_vehicleCap;

  // First element is zero, then customer demands follow
  // The lysgard needs this specific structure
  
  std::vector<int> d_lysgard_demand;
  
  public:
    
    Cut_cap (int priority, bool lazy, bool user, 
             bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut              (priority, lazy, user, stopIfFound, onlyRootNode, std::string("cap")),
      d_nDepots        (data.d_nDepots),
      d_nCustomers     (data.d_nCustomers),
      d_vehicleCap     (data.d_vehicleCap),
      d_lysgard_demand (data.lysgard_demand())
    { };
  
  private:

    std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
};