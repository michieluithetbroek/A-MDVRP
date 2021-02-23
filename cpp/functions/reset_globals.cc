#include "../main.ih"

/*
 * Used to reset all globals in between runs
 * Yes, this is one of the ugly drawbacks of using globals
 */

void reset_globals()
{
  // TODO unused?
  g_vehicleCapacity = -1;
  g_depotCost       = -1;
  g_atMostOneTour   = -1;
  g_tourSize        = -1;
  g_nodes           = 0;
  
  gg_timer_callback_lazy      = dur_t::zero();
  gg_timer_callback_lazy1     = dur_t::zero();
  gg_timer_callback_user      = dur_t::zero();
  gg_timer_callback_user1     = dur_t::zero();
  gg_timer_callback_heuristic = dur_t::zero();

  gg_timeToSol_modelA = vector<pair<dur_t, int>>();
  gg_timeToSol_modelC = vector<pair<dur_t, int>>();
  
  // set globals to zero, as solution is processed now

  // globals for summarizing results after run
  g_UB      = 0;
  g_LB      = 0;
  g_runTime = 0;
  g_nodes   = 0;
  
  g_globalSol   = vector<vector<atomwrapper<int>>>();
  g_modelSolved = false;
  g_cutOff      = numeric_limits<int>::max();
  g_finalSol    = vector<vector<int>>();

  g_smallestDelta = 0;
}
