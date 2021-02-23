#include "data.ih"

/*
 * This constructor read the Santos files
 * 
 */




Data::Data(int idx_instance)
:
  d_instance   (idx_instance),
  d_nDepots    (-1),
  d_nCustomers (-1),
  d_nNodes     (-1),
  d_vehicleCap (-1),
  d_tourMin    (-1),
  d_tourMax    (-1),
  d_inst       (P_TYPE),
  d_asy        (DATA_ASYMMETRY),
  d_demands    (),
  d_depotCost  (),
  d_iDepots    (),
  d_iCustomers (),
  d_iNodes     (),
  d_cost       ()
{
  if (P_TYPE != PROBLEMTYPE::MDATSP or DATA_ASYMMETRY != ASYCLASS::SANTOS)
    throw string("Enums are incorrect (Data::data2.cc)");
   
  // Some hardcoding to read the Santos files
  // The elements are
  //  0) Instance index of Santos
  //  1) Number of customers
  //  2) Number of depots in the file 
  //  3) Number of depots that skipped from the file
  
  vector<array<int, 4>> const settings = {
    {1, 100, 20, 15},
    {1, 100, 20, 10},
    {1, 100, 20,  0},
    {2, 100, 20, 15},
    {2, 100, 20, 10},
    {2, 100, 20,  0},
    {3, 100, 20, 15},
    {3, 100, 20, 10},
    {3, 100, 20,  0},
    {1, 200, 40, 30},
    {1, 200, 40, 20},
    {1, 200, 40,  0},
    {1, 300, 60, 50},
    {1, 300, 60, 40},
    {1, 300, 60, 30},
    {1, 300, 60, 20},
    {1, 300, 60,  0}
  };
  
  cout << idx_instance << endl;
  
  auto const &s = settings[idx_instance];
  
  // Now we set the data members
  d_nDepots    = s[2] - s[3];
  d_nCustomers = s[1];
  d_nNodes     = d_nDepots + d_nCustomers;
  
  d_vehicleCap = d_nCustomers + 5;
  
  // Set index vectors
  for (size_t idx = 0; idx < d_nDepots; ++idx)
    d_iDepots.push_back(idx);
  
  for (size_t idx = d_nDepots; idx < d_nNodes; ++idx)
    d_iCustomers.push_back(idx);
  
  for (size_t idx = 0; idx < d_nNodes; ++idx)
    d_iNodes.push_back(idx);
  
  d_demands   = vector<int>(d_nNodes, 1);
  d_depotCost = vector<int>(d_nDepots, 0);
  d_cost      = vector<vector<double>>(s[1] + s[2], 
                                     vector<double>(s[1] + s[2], 0.0));
  
  // Make dummy depots
  for (int idx = 0; idx != d_nDepots; ++idx)
  {
    d_depots.emplace_back(1, 1);
    d_nodes.emplace_back(1, 1, 0);    
  }
  
  // Make dummy customers
  for (int idx = 0; idx != d_nCustomers; ++idx)
  {
    d_customers.emplace_back(1, 1, 1);    
    d_nodes.emplace_back(1, 1, 1);
  }
  
  
  
  
  reset_time_and_count_globals();
  setSettings();
  
  readFile_santos(s[0], s[2], s[3]);
  
  vector<atomwrapper<int>> v_a;
  
  for (int i: d_iNodes)
    v_a.emplace_back(atomic<int>(0));
  
  for (int i: d_iNodes)
    g_globalSol.emplace_back(v_a);
  
  check();
}
