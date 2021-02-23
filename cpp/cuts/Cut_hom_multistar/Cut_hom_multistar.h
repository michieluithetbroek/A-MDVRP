#pragma once
 
#include "./../cut.h"

#include <cvrpsep.h>

class Cut_hom_multistar: public Cut
{
  double const d_eps = 0.000001;
  
  int const d_nDepots;
  int const d_nCustomers;
  int const d_vehicleCap;
  
  std::vector<size_t> const d_iNodes;
  
  std::vector<int> d_lysgard_demand;
  
  public:
    
    Cut_hom_multistar (int priority, bool lazy, bool user, 
                       bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut              (priority, lazy, user, stopIfFound, onlyRootNode, std::string("hom star")),
      d_nDepots        (data.d_nDepots),
      d_nCustomers     (data.d_nCustomers),
      d_vehicleCap     (data.d_vehicleCap),
      d_iNodes         (data.d_iNodes),
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
    

    CnstrMgrPointer call_lysgard_hom_multistar(std::vector<std::vector<double>> const &x);
    
    CutReturn calc_hom_multistar (std::vector<int> const &Nlist,
                                  std::vector<int> const &Tlist,
                                  std::vector<int> const &Clist, 
                                  int A,
                                  int B, 
                                  std::vector<std::vector<double>> const &x, 
                                  double &lhs);
};