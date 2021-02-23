#pragma once

#include "./../cut.h"

#include <cvrpsep.h>

class Cut_comb: public Cut
{
  double const d_eps = 0.000001;
  
  int const d_nDepots;
  int const d_nCustomers;
  int const d_vehicleCap;
  
  std::vector<int> d_lysgard_demand;
  
  public:
    
    Cut_comb (int priority, bool lazy, bool user, 
              bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut              (priority, lazy, user, stopIfFound, onlyRootNode, std::string("comb")),
      d_nDepots        (data.d_nDepots),
      d_nCustomers     (data.d_nCustomers),
      d_vehicleCap     (data.d_vehicleCap),
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
    
    void print_tooth(vector<vector<int>> const &inTooth) const;
    
    CnstrMgrPointer call_lysgard_strengthened_combs(vector<vector<double>> const &x);

    vector<vector<int>> parse_inTooth(CnstrMgrPointer myCutsCMP, int i) const;
    
    CutReturn calc_strengthened_comb_cut (double &lhs, int nTeeth, 
                                          vector<vector<int>> const &inTooth,
                                          vector<vector<double>> const &x) const;
};

