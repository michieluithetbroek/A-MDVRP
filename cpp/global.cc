#include "main.ih"



// ------------------------------------------------------------
// --- Set this for the specific run                        ---
// --- Later on we should read these from a file            ---
// ------------------------------------------------------------

mutex g_mtx;
condition_variable g_cv;
bool g_modelSolved = false;
int  g_cutOff = numeric_limits<int>::max();

vector<vector<atomwrapper<int>>> g_globalSol;
vector<vector<int>> g_finalSol;


ASYCLASS    DATA_ASYMMETRY = ASYCLASS::UNSET;
PROBLEMTYPE P_TYPE         = PROBLEMTYPE::UNSET;



// -------------------------------------------
// --- CPLEX settings                      ---
// -------------------------------------------

double const g_timeLimit    = 18000;
int    const g_nThreads     = 5;  
int    const g_workMem      = 24000;
int    const g_treeMemory   = 50000;
int    const g_nMaxNodes    = 10000000;

double const g_epGap        = 0.0;      // Relative stopping condition
double const g_epAGap       = 0.95;     // Absolute stopping condition
int    const g_verbosity    = 3;
int    const g_parallelMode = 1;        //  -1 oppertunistic, 0 auto, 1 deter.
int    const g_sleepTime    = 60;

int          g_cutPasses    = 250;      // ALERT hardcoded in solve.cc
bool         g_cplexCuts    = true;     // 0 is auto
bool         g_onlyRoot     = false;
bool         g_cplexFocusLB = true;     // Always true except in effect_gurobi.cc
bool         g_useGurobi    = true;

string const g_nodeFileDir  = "/local/tmp"; // "/local/tmp"

// How often do we want to call the user callback funtion?
int g_userSettingA = 100;
int g_userSettingB = 200;






// ------------------------------------------------------------
// --- Fine from here                                       ---
// --- All these variables can be set with reset()          ---
// ------------------------------------------------------------

// The -1 represent that the variable is uninitialized
// These values should be set by the data class

// TODO used??
int g_vehicleCapacity = -1;
int g_atMostOneTour   = -1;
int g_tourSize        = -1;
bool g_depotCost      = false;

double g_UB      = 0;    // best upper bound
double g_LB      = 0;    // best lower bound
double g_LBRoot  = 0;    // root relaxation node
double g_runTime = 0;    // run time
int    g_nodes   = 0;    // number of B&B nodes

dur_t gg_timer_callback_lazy      = dur_t::zero();
dur_t gg_timer_callback_lazy1     = dur_t::zero();
dur_t gg_timer_callback_user      = dur_t::zero();
dur_t gg_timer_callback_user1     = dur_t::zero();
dur_t gg_timer_callback_heuristic = dur_t::zero();

// At which time did CPLEX start running
// Used to find the time to new incumbent solutions
// The subsequent vector stores all itermediate objectives with timings. 

std::chrono::time_point<std::chrono::high_resolution_clock> gg_startTime_modelA;
std::chrono::time_point<std::chrono::high_resolution_clock> gg_startTime_modelC;

vector<pair<dur_t, int>> gg_timeToSol_modelA;
vector<pair<dur_t, int>> gg_timeToSol_modelC;


// What is the last delta for which the compact formulation
// has found a solution

int g_smallestDelta = 0;
