#include "modelA.ih"

/*
 * -2 since we do not count depots in tour min/max size
 */


void ModelA::check_correctness() const
{
  /* check upper and lower bound */
  if (g_tourSize)
  {
    size_t const l_bound = d_data.d_tourMin;
    size_t const u_bound = d_data.d_tourMax;
    
    for (vector<int> const &el: g_finalSol)
    {
      if (el.size() - 2 < l_bound)
      {
        cout << "Lower bound is not respected !! " << endl << endl;
        throw string("check_correctness a\n");
      }
      
      if (el.size() - 2 > u_bound)
      {
        cout << "Upper bound is not respected !! " << endl << endl;
        throw string("check_correctness a\n");
      }
    }
  }
}
