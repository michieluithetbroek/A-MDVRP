#pragma once

#include "../data/data.h"
#include "gurobi_c++.h"

#include <iosfwd>
#include <vector>

using varMatrix = std::vector<vector<GRBVar>>;
using varArray  = std::vector<GRBVar>;
using numMatrix = std::vector<vector<double>>;

// TODO Michiel: why isn't this a class? 
// Many member function should be private

struct ModelC
{
  // TODO do we really need a complete copy of Data? This is 
  // also stored in modelA. Not too bad but with 400 
  // customers it requires a considerable amount of memory.
  
  Data const d_data;
  
  int const d_delta;
  
  // TODO can we set a smaller big M?
  int const d_M = 9999;
  
  int const d_nDepots;
  int const d_nCustomers;
  int const d_nNodes;
  int const d_vehicleCap;
  std::vector<int> const d_demands;
  
  std::vector<size_t> const d_iDepots;
  std::vector<size_t> const d_iCustomers;
  std::vector<size_t> const d_iNodes;
  
  std::vector<std::vector<double>> const d_cost;

  // Data for lysgard
  std::vector<int> d_lysgard_demand;
  
  // Gurobi
  GRBEnv   d_env;
  GRBModel d_model;
  
  varMatrix d_x;
  varArray  d_y;
  
  varArray  d_u;
  varMatrix d_z;
  
  varArray  d_loc;

  int d_neighbourhoodSize;
  
  // Functions
  ModelC(Data const &data, int neighbourhoodSize);
  
  void createVariables();
  void createObjective();
  void createConstraints();
  void solve(int solvingTime);
  
  void constraints_u();
  void constraints_subtours();

  void setInitialSolution();
  
  // -----------------------------
  // --- Print functions    ------
  // -----------------------------
  
//   void printArcs    (IloCplex const &cplex) const;
//   void printArcs    (IloNumMatrix const &x) const;
//   void printArcs    (numMatrix const &x)    const;
  void printRoutes() const;
  void printTimes() const;
  
//   void showSolution (IloCplex const &cplex) const;
  
  // Multi depot multi traveling salesman problem
  void constraints_subtours_tsp();
};
