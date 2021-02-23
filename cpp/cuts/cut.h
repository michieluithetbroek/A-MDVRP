#pragma once

#include <chrono>
#include <vector>
#include <array>
#include <string>
#include <iostream>
#include <algorithm>
#include <atomic>

#include <ilcplex/ilocplex.h>

// Not used by the base class Cut but by every derived class
// TODO thus move this to the cut.ih file..
#include "./../data/data.h"

using dur_t = std::chrono::duration<double>;

/*
 * This is the return type of all cuts
 * It represents the lhs and the strictly positive coefficients for x_ij 
 * 
 */

struct CutReturn
{
  double rhs;
  std::vector<std::array<int, 3>> coeff;
  
  //TODO why push_back and not emplace_back
  void add(int coefficient, int i, int j)
  {
    coeff.push_back({coefficient, i, j});
  }
};

  
  
/*
 * Other Cut classes should use public inheritance.
 * The only required public functions of the derived classes is the constructor
 * 
 * The derived cut classes provide the Cut base class with a vector<CutReturn>
 * This base class transforms it into the desired cut object that can be used by 
 * CPLEX or Gurobi. The returned cuts are already normalized for CPLEX.
 * 
 * The first four members (i.e., priority, lazy, user, stopIfCutFound) are not used
 * by the Cut class itself. It can be used by the model class to decide when to apply a cut.
 * 
 * TODO Cut::getCuts() should not use a bool but an ENUM
 * Or with a template such that the if-statement can be evaluated at compile time
 */

class Cut
{
  int const d_priority;            // In which order do we apply the cuts
  
  bool const d_lazy;               // Will the cut be used in the lazy/user callback?
  bool const d_user;
  
  bool const d_stopIfCutFound;     // Do not apply other cuts if this one finds a VI
  bool const d_onlyRootNode;       // Do we apply the cut after the root node is solved?
  
  std::atomic<int> d_cnt_lazy;     // How often is the cut called
  std::atomic<int> d_cnt_user;
  
  std::atomic<int> d_nCuts_lazy;   // How many VI were found?
  std::atomic<int> d_nCuts_user;
  
  dur_t d_time_lazy = dur_t::zero();
  dur_t d_time_user = dur_t::zero();
  
  string const d_name;
  
  public:
  
    Cut() = delete;
    
    Cut (int priority, 
         bool lazy, bool user, 
         bool stopIfFound, bool onlyRootNode, 
         std::string const &name
        );
  

    std::vector<IloRange> getCuts(IloEnv const &env, 
                                  IloArray<IloNumVarArray> const &variables,
                                  std::vector<std::vector<double>> const &x,
                                  bool const lazyCall
                                 );
    
    
    // ---------------------
    // --- Getters       ---
    // ---------------------
    
    int priority() const;
    
    bool lazy() const;
    bool user() const;
    
    bool stopIfCutFound() const;
    bool onlyRootNode() const;
    
    int cnt_lazy() const;
    int cnt_user() const;
    
    int nCuts_lazy() const;
    int nCuts_user() const;
    
    dur_t time_lazy() const;
    dur_t time_user() const;
    
    std::string name() const;
    
  private:
    
    virtual std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x) = 0;
    
    IloExpr normalize(IloExpr const &expr) const;
    
    std::vector<IloRange> createIloRange(IloEnv const &env, 
                                         IloArray<IloNumVarArray> const &variables,
                                         std::vector<CutReturn> const &cuts_in
                                        ) const;
};



inline int Cut::priority() const
{
  return d_priority;
}

inline bool Cut::lazy() const
{
  return d_lazy;
}

inline bool Cut::user() const
{
  return d_user;
}

inline bool Cut::stopIfCutFound() const
{
  return d_stopIfCutFound;
}

inline bool Cut::onlyRootNode() const
{
  return d_onlyRootNode;
}

inline int Cut::cnt_lazy() const
{
  return d_cnt_lazy;
}

inline int Cut::cnt_user() const
{
  return d_cnt_user;
}

inline int Cut::nCuts_lazy() const
{
  return d_nCuts_lazy;
}

inline int Cut::nCuts_user() const
{
  return d_nCuts_user;
}

inline dur_t Cut::time_lazy() const
{
  return d_time_lazy;
}

inline dur_t Cut::time_user() const
{
  return d_time_user;
}

inline std::string Cut::name() const
{
  return d_name;
}



// This must be at the bottom! Why?
// Because the derived classes cannot exist before the above base class is defined

#include "./allCuts.h"
