#pragma once

#include "./../cut.h"

class DK_depot_min: public Cut
{
  size_t const d_nDepots;
  vector<size_t> const d_iDepots;
  
  double d_maxPhi = 0;
  
  double const d_eps = 0.001;
  
  public:
    
    DK_depot_min(int priority, bool lazy, bool user, 
                 bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut       (priority, lazy, user, stopIfFound, onlyRootNode, std::string("DK_depot-")),
      d_nDepots (data.d_nDepots),
      d_iDepots (data.d_iDepots)
    {};
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------
    
    double update_phi           (std::vector<std::vector<double>> const &x, 
                                 std::vector<int> const &seq,
                                 int n, double phi, int k
                                ) const;
                                
    CutReturn create_cut        (std::vector<std::vector<double>> const &x,
                                 std::vector<int> const &seq, 
                                 size_t n, int l
                                ) const;


    void extend                (size_t n, int k, double phi,
                                double alpha, double beta,
                                std::vector<std::vector<double>> const &x,
                                std::vector<int> &seq,
                                std::vector<int> const &iComponent,
                                std::vector<CutReturn> &DKcuts
                               );

    // TODO The first three could be functions in the namespace graphFunctions
    bool   already_in_sequence  (std::vector<int> const &seq, int n, int b, int k) const;
    bool   connected_to_depot   (std::vector<std::vector<double>> const &x, int idx) const;
    bool   connected_from_depot (std::vector<std::vector<double>> const &x, int idx) const;
    
    double seperate_depots      (std::vector<std::vector<double>> const &x, int idx, int jdx) const;
};


inline bool DK_depot_min::already_in_sequence (std::vector<int> const &seq,
                                               int n, int b, int k) const
{
  return (b == k or find(cbegin(seq), cbegin(seq) + n, b) != cbegin(seq) + n);
}

inline bool DK_depot_min::connected_to_depot (std::vector<std::vector<double>> const &x, 
                                              int idx) const
{
  for (size_t d = 0; d < d_nDepots; ++d)
    if (x[idx][d] > gg_eps)
      return true;
    
  return false;
}

inline bool DK_depot_min::connected_from_depot (std::vector<std::vector<double>> const &x,
                                                int idx) const
{
  for (size_t d = 0; d < d_nDepots; ++d)
    if (x[d][idx] > gg_eps)
      return true;
    
  return false;
}

inline double DK_depot_min::seperate_depots (std::vector<std::vector<double>> const &x, 
                                             int idx, int jdx) const
{
  double sum = 0;
  
  for (size_t d = 0; d < d_nDepots; ++d)
    sum += max(x[idx][d], x[d][jdx]);
    
  return sum;
}
