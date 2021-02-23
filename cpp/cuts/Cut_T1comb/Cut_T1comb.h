#pragma once

#include "./../cut.h"

class Cut_T1comb: public Cut
{
  double const d_eps = 0.000001;
  
  int const d_nDepots;
  
  std::vector<size_t> const d_iDepots;
  std::vector<size_t> const d_iCustomers;
  std::vector<size_t> const d_iNodes;
  
  public:
    
    Cut_T1comb (int priority, bool lazy, bool user, 
                bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut          (priority, lazy, user, stopIfFound, onlyRootNode, std::string("T1comb")),
      d_nDepots    (data.d_nDepots),
      d_iDepots    (data.d_iDepots),
      d_iCustomers (data.d_iCustomers),
      d_iNodes     (data.d_iNodes)
    {};
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------
    
    CutReturn calc_T1comb (std::vector<size_t> const &T, 
                           std::vector<size_t> const &H, 
                           std::vector<std::vector<double>> const &x) const;

    double calc_inOut     (std::vector<size_t> const &T, 
                           size_t new_cust, 
                           std::vector<std::vector<double>> const &x, 
                           std::vector<size_t> const &d_iNodes) const;
};