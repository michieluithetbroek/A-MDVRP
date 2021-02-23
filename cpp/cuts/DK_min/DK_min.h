#pragma once

#include "./../cut.h"

class DK_min: public Cut
{
  double d_maxPhi = 0;
  
  public:
    
    DK_min(int priority, bool lazy, bool user, 
           bool stopIfFound, bool onlyRootNode, Data const &data) 
    : 
      Cut (priority, lazy, user, stopIfFound, onlyRootNode, std::string("DK-"))
    {};
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------
    
    CutReturn create_cut (std::vector<int> const &seq, size_t n) const;
    
    double update_phi (std::vector<std::vector<double>> const &x, 
                       std::vector<int> const &seq, 
                       size_t n, double phi
                      ) const;
                       
    double update_pi  (std::vector<std::vector<double>> const &x,
                       std::vector<int> const &seq,
                       size_t n, double pi
                      ) const;
                       
    void extend       (size_t n, double phi, double pi,
                       std::vector<std::vector<double>> const &x,
                       std::vector<int> &seq,
                       std::vector<int> const &iComponent,
                       std::vector<CutReturn> &DKcuts
                      );
    
    bool already_in_sequence (std::vector<int> const &seq, int n, size_t k) const;
};

inline bool DK_min::already_in_sequence (std::vector<int> const &seq, int n, size_t k) const
{
  return (find(cbegin(seq), cbegin(seq) + n, k) != cbegin(seq) + n);
}