#include "./cut.ih"

/*
 * Parameters
 *  x   The LP relaxation
 *  lazyCall   Is the function called from the lazy (true) or 
 *             user (false) callback? Just used to set some statistics
 */

vector<IloRange> Cut::getCuts(IloEnv const &env, 
                              IloArray<IloNumVarArray> const &variables,
                              vector<vector<double>> const &x,
                              bool const lazyCall
                             )
{
  auto const start = chrono::high_resolution_clock::now();
  
  vector<IloRange> cuts (createIloRange(env, variables, findCuts(x)));
  
  auto const end = chrono::high_resolution_clock::now();
  
  if (lazyCall)
  {
    d_cnt_lazy   += 1;
    d_nCuts_lazy += cuts.size();
    d_time_lazy  += end - start;
  }
  
  else
  {
    d_cnt_user   += 1;
    d_nCuts_user += cuts.size();
    d_time_user  += end - start;
  }
  
  return cuts;
}
