#include "modelA.ih"

/* 
 * Assumes component size > 2
 * 
 */

bool ModelA::check_subtour(numMatrix const &x, vector<int> const &cc_nodes, IloExpr &expr, int &rhs)
{
  // calculated #needed vehicle
  double cap = 0;
  for (int i: cc_nodes)
    cap += d_demands[i];

  // calculate |S| - k(S)
  
  rhs = (int)cc_nodes.size() - 1  - ( ceil(cap / (double)d_vehicleCap) - 1);

  // calculate x(S:S)
  double sum_xij = 0.0;
  for (int i: cc_nodes)
    for (int j: cc_nodes)
      if (i != j)
        sum_xij += x[i][j];
         
  if (sum_xij <= rhs + 0.1)
    return false; 
      
  // add constraint , it violates LP
  for (int i: cc_nodes)
  {
    for (int j: cc_nodes)
    {
      if (i == j)
        continue;
      
      expr += d_x[i][j];
    }
  }
    
  return true;
}