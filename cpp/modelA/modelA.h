#pragma once

#include <map>
#include <iosfwd>
#include <vector>
#include <memory>  // std::unique_ptr
#include <chrono>
#include <utility>

#include "./../data/data.h"
#include <lemon/list_graph.h>
#include <ilcplex/ilocplex.h>

#include "./../cuts/cut.h"

using IloNumMatrix    = IloArray<IloNumArray>;
using IloNumVarMatrix = IloArray<IloNumVarArray>;

// TODO do we use this?
using numMatrix = vector<vector<double>>;

using namespace std;
using namespace lemon;

using dur_t = std::chrono::duration<double>;



/*
 * The basic model formulation
 */

struct ModelA
{
  // -------------------------
  // --- Own datamembers   ---
  // -------------------------
  
  Data const d_data;
  
  int const d_M = 9999; // TODO Michiel: What is this?
  
  int const d_nDepots;
  int const d_nCustomers;
  int const d_nNodes;
  int const d_vehicleCap;
  
  vector<int> const d_demands;
  
  vector<size_t> const d_iDepots;
  vector<size_t> const d_iCustomers;
  vector<size_t> const d_iNodes;
  
  vector<vector<double>> const d_cost;

  vector<shared_ptr<Cut>> d_cuts; 

  
  // -------------------------
  // --- CPLEX             ---
  // -------------------------
  
  IloEnv   d_env;
  IloModel d_model;
  
  IloNumVarMatrix d_x;
  IloNumVarArray  d_loc;


  
  // -------------------------
  // --- Functions         ---
  // -------------------------
  
  ModelA() = delete;
  ModelA (Data const &data, vector<shared_ptr<Cut>> const &allCuts);
  
  void createVariables();
  void createObjective();
  void createConstraints();
  void addOwnLazyConstraints(IloCplex &cplex);

  void solve();
  void solve_root();
  
  void constraints_u();
  void constraints_subtours();
  
  // TODO Michiel: is this one used?
  bool check_subtour  (numMatrix const &x, vector<int> const &cc_nodes, IloExpr &expr, int &rhs);

  IloRange normalized_cut(IloRange &&cut_in) const;

  void check_correctness() const;
  
  
  
  // -----------------------------
  // --- Print functions    ------
  // -----------------------------
  
  void printTimeToSol(string const &fileName) const;
  
  // TODO why do we have all the commented functions?
  void printArcs    (IloCplex const &cplex) const;
//   void printArcs    (IloNumMatrix const &x) const;
//   void printArcs    (numMatrix const &x)    const;
  void printRoutes  (IloCplex &cplex) const;
//   void printTimes  () const;
  
//   void showSolution (IloCplex const &cplex) const;
  
  // Multi depot multi traveling salesman problem
  void constraints_subtours_tsp();
};
