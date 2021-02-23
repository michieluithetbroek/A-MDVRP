#include "data.ih"

/*
 * Constructor to read our own instances
 * 
 */

Data::Data(PROBLEMTYPE inst, ASYCLASS asy, 
           int instance, int nCustomers, int nDepots)
:
  d_instance   (instance),
  d_nDepots    (nDepots),
  d_nCustomers (nCustomers),
  d_nNodes     (nCustomers + nDepots),
  d_vehicleCap (-1),
  d_tourMin    (-1),
  d_tourMax    (-1),
  d_inst       (inst),
  d_asy        (asy),
  d_demands    (d_nNodes),
  d_depotCost  (nDepots),
  d_iDepots    (),
  d_iCustomers (),
  d_iNodes     (),
  d_cost       (nCustomers + nDepots, vector<double>(nCustomers + nDepots, 0.0))
{
  reset_time_and_count_globals();
  setSettings();
  readFile_own();
  
  vector<atomwrapper<int>> v_a;
  
  for (int i: d_iNodes)
    v_a.emplace_back(atomic<int>(0));
  
  for (int i: d_iNodes)
    g_globalSol.emplace_back(v_a);
  
  check();
  
//   create_initial();
}
