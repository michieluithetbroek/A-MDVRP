#include "../main.ih"

/*
 * Quite ugly that his is a member function
 * On the other hand, it should be called at the start of each run
 * 
 * TODO Maybe we should get rid of all globals completely
 * All globals are given in the main folder: globals.h
 * 
 * TODO when is this actually called? We also have a function
 * reset_globals.cc... what the??
 */

void Data::reset_time_and_count_globals() const
{
  gg_timer_callback_lazy      = dur_t::zero();
  gg_timer_callback_lazy1     = dur_t::zero();
  gg_timer_callback_user      = dur_t::zero();
  gg_timer_callback_user1     = dur_t::zero();
  gg_timer_callback_heuristic = dur_t::zero();
  
  gg_timeToSol_modelA = vector<pair<dur_t, int>>();
  gg_timeToSol_modelC = vector<pair<dur_t, int>>();
  
  // globals for summarizing results after run
  g_UB      = 0;        
  g_LB      = 0;
  g_LBRoot  = 0;
  g_runTime = 0;   
  g_nodes   = 0; 
  
  g_globalSol   = vector<vector<atomwrapper<int>>>();
  g_finalSol    = vector<vector<int>>();
  g_modelSolved = false;
  g_cutOff      = numeric_limits<int>::max();
  
  g_smallestDelta = 0;
}
