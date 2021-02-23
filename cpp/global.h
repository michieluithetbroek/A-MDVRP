#pragma once

#include <chrono>
#include <vector>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <thread>

using namespace std;

template <typename T>
struct atomwrapper
{
  std::atomic<T> _a;

  atomwrapper()
    :_a()
  {}

  atomwrapper(const std::atomic<T> &a)
    :_a(a.load())
  {}

  atomwrapper(const atomwrapper &other)
    :_a(other._a.load())
  {}

  atomwrapper &operator=(const atomwrapper &other)
  {
    _a.store(other._a.load());
  }
};

extern mutex g_mtx;
extern condition_variable g_cv;
extern vector<vector<atomwrapper<int>>> g_globalSol;
extern vector<vector<int>> g_finalSol;

extern bool g_modelSolved;

// We use gg_ to indicate global constants
double constexpr gg_eps = 0.000001;

// specifies degree of asymmetry: see fischetti toth 1997 MS paper

/*
 * The following enums describe the problem type (PROBLEMTYPE) and
 * the assymtry class (ASYCLASS) of the current instance. We use
 * enum class such that it is more easy to search whether a specific
 * member is used (e.g., grep -r DATACLASS::A). 
 * 
 * NOTE we slightly misuse the ASYCLASS to distuignish the santos
 * instances. This because santos instances are of the type 
 * PROBLEMTYPE::MDATSP. This is possible since for these instance
 * there is only a single assymetry class.
 * 
 */

enum class ASYCLASS
{
  A,
  B,
  CRC,
  SANTOS,
  UNSET
};

// specifies more or less the instances we are going to solve 
//  -> also name of the folder in "instances/own"

enum class PROBLEMTYPE
{
  MDATSP,
  MDAMTSP,
  MDACVRP,
  ACLRP,
  UNSET
};



// --------------------------------------------------------------
// --- global variables indicating the asymmetry              ---
// --------------------------------------------------------------

// TODO why don't we start these global variables with g_?
// When are these set? Who is responsible for doing that?
//
// If we remove this, then we can also remove SANTOS from the
// ASYCLASS and add it to PROBLEMTYPE, as then only the Data class
// deals (locally) with this enum.

extern ASYCLASS    DATA_ASYMMETRY;
extern PROBLEMTYPE P_TYPE;


// // TODO used??
// enum SOLVER
// {
//   CPLEX,
//   GUROBI
// };



// --------------------------------------------------------------
// --- Which model do we run?                                 ---
// --- These are set according to the DATACLASS above         ---
// --------------------------------------------------------------

// We do not use bool since we indicate uninitialized variables by -1
// TODO is this mixed with the use of the global enums?

extern int  g_vehicleCapacity;
extern bool g_depotCost;
extern int  g_atMostOneTour;
extern int  g_tourSize;

extern int g_cutOff;



// -----------------------------
// --- CPLEX settings        ---
// -----------------------------

extern double const g_timeLimit;     // time limit for running
extern int    const g_nThreads;      // Number of threads that cplex can use
extern int    const g_workMem;       // Memory (in MB) that cplex can use      16000
extern int    const g_treeMemory;    // 8000
extern int    const g_nMaxNodes;     // only for info on number of cuts
extern double const g_epGap;         // Relative stopping condition
extern double const g_epAGap;        // Absolute stopping condition
extern int    const g_verbosity;
extern int    const g_parallelMode;
extern int    const g_sleepTime;

extern int          g_cutPasses;       
extern bool         g_cplexCuts;     // Use the standard cplex cuts?
extern bool         g_onlyRoot;      // Solve only the root (more heavily?)
extern bool         g_cplexFocusLB;
extern bool         g_useGurobi;

extern string const g_nodeFileDir;   // "/local/tmp"

extern int g_userSettingA;
extern int g_userSettingB;



// --------------------------------------------------------------
// --- Timers                                                 ---
// --- As profiling doesnt work with cplex                    ---
// --------------------------------------------------------------

using dur_t = std::chrono::duration<double>;

extern dur_t gg_timer_callback_lazy;
extern dur_t gg_timer_callback_lazy1;
extern dur_t gg_timer_callback_user;
extern dur_t gg_timer_callback_user1;
extern dur_t gg_timer_callback_heuristic;

// At which time did CPLEX start running
// Used to find the time to new incumbent solutions
// The subsequent vector stores all itermediate objectives with timings. 

extern std::chrono::time_point<std::chrono::high_resolution_clock> gg_startTime_modelA;
extern std::chrono::time_point<std::chrono::high_resolution_clock> gg_startTime_modelC;

extern vector<pair<dur_t, int>> gg_timeToSol_modelA;
extern vector<pair<dur_t, int>> gg_timeToSol_modelC;

// --------------------------------------------------------------
// --- Counters                                               ---
// --------------------------------------------------------------

// globals for summarizing results after run
extern double g_UB;        // best upper bound
extern double g_LB;        // best lower bound
extern double g_runTime;   // run time
extern double g_LBRoot;    // root relaxation
extern int    g_nodes;     // number of B&B nodes


// What is the last delta for which the compact formulation
// has found a solution. Only the Gurobi thread uses this

extern int g_smallestDelta;
extern vector<vector<int>> g_characs_MDATSP;
extern vector<vector<int>> g_characs_MDAMTSP;
extern vector<vector<int>> g_characs_MDACRP;
extern vector<vector<int>> g_characs_ACLRP;
