#include "data.ih"

/* 
 * 
 * Checks whether all datamembers are correctly set
 * Call this function after each use_data() function
 * 
 */  

void Data::check () const
{ 
  // -------------------------------
  // --- Check globals           ---
  // -------------------------------
  
  if (g_vehicleCapacity != 0 and g_vehicleCapacity != 1)
    throw string("g_vehicleCapacity not set (data::check.cc)");
  
  if (g_depotCost != 0 and g_depotCost != 1)
    throw string("g_depotCost not set (data::check.cc)");

  if (g_atMostOneTour == -1)
    throw string("g_atMostOneTour not set (data::check.cc)");
  
  if (g_tourSize == -1)
    throw string("g_tourSize not set (data::check.cc)");
  
  if (g_tourSize)
  {
    if (d_tourMin > d_tourMax)
      throw string("tourSizeMin > tourSizeMax (data::check.cc)");
    
    if (d_tourMin < 0)
      throw string("tourSizeMin < 0 (data::check.cc)");
    
    if (d_tourMax <= 0)
      throw string("tourSizeMax <= 0 (data::check.cc)");
  }
    
  
  
  // -------------------------------
  // --- Number of nodes         ---
  // -------------------------------
  
  if (d_nDepots <= 0 or d_nDepots >= 1000)
    throw string("Number of depots incorrect (data::check.cc)");
  
  if (d_nCustomers <= 0 or d_nCustomers >= 2000)
    throw string("Number of customers incorrect (data::check.cc)");
  
  if (d_nNodes != d_nDepots + d_nCustomers)
    throw string("Number of nodes incorrect (data::check.cc)");
  
  if (d_vehicleCap <= 0)
    throw string("Negative vehicle capacity (data::check.cc)");
  
  
  
  // -------------------------------
  // --- Check d_demands vector  ---
  // -------------------------------
  
  /*
   * I replaced: d_nCustomers by d_nNodes !!
   * I = Albert
   * Albert = the smart ass working on routing and network design
   * End.
   * 
   * Still something went wrong here. Henceforth we say: Albert != Smart
   */
  
  cout << d_demands.size() << endl << d_nNodes << endl;
  
  if (d_demands.size() != static_cast<size_t>(d_nNodes))
    throw string("Number of demands incorrect (data::check.cc)");
  
  for (int idx = 0; idx < d_nCustomers; ++idx)
    if (d_demands[idx] < 0)
      throw string("Negative demand observed (data::check.cc)");
  
   
    
  // -------------------------------
  // --- Check d_depotCost       ---
  // -------------------------------
  
  /*
  * I included the if (g_depotCost)
  * I = Albert
  */  
  
  if (g_depotCost)
  {
    if (d_depotCost.size() != static_cast<size_t>(d_nDepots))
      throw string("Number of depotCost incorrect (data::check.cc)");
    
    for (int idx = 0; idx < d_nDepots; ++idx)
      if (d_depotCost[idx] < 0)
        throw string("Negative depot cost observed (data::check.cc)");
  }
  
  if (not g_depotCost)
  {
    for (int idx = 0; idx < d_nDepots; ++idx)
      if (d_depotCost[idx] > 0)
        throw string("Positive depot cost observed (data::check.cc)");  
  }
      
  // -------------------------------
  // --- Check indices           ---
  // -------------------------------   
  
  if (d_iDepots.size() != static_cast<size_t>(d_nDepots))
    throw string("Incorrect size d_iDepots (data::check.cc)");
  
  if (d_iCustomers.size() != static_cast<size_t>(d_nCustomers))
    throw string("Incorrect size d_iCustomers (data::check.cc)");
  
  if (d_iNodes.size() != static_cast<size_t>(d_nNodes))
    throw string("Incorrect size d_iNodes (data::check.cc)");
  
  
      
  for (int idx = 0; idx < d_nDepots; ++idx)
    if (d_iDepots[idx] != static_cast<size_t>(idx))
      throw string("Incorrect depot index (data::check.cc)");

  for (int idx = 0; idx < d_nCustomers; ++idx)
    if (d_iCustomers[idx] != static_cast<size_t>(d_nDepots + idx))
      throw string("Incorrect customer index (data::check.cc)");    

    
  for (int idx = 0; idx < d_nNodes; ++idx)
    if (d_iNodes[idx] != static_cast<size_t>(idx))
      throw string("Incorrect node index (data::check.cc)");
    
    
    
  // -------------------------------
  // --- Check struct objects    ---
  // -------------------------------
  
  if (d_depots.size() != static_cast<size_t>(d_nDepots))
    throw string("Incorrect size d_depots (data::check.cc)");
  
  if (d_customers.size() != static_cast<size_t>(d_nCustomers))
    throw string("Incorrect size d_customers (data::check.cc)");
  
  if (d_nodes.size() != static_cast<size_t>(d_nNodes))
    throw string("Incorrect size d_nodes (data::check.cc)"); 
  
  for (int idx = 0; idx < d_nDepots; ++idx)
    if (d_depots[idx].x != d_nodes[idx].x
      or d_depots[idx].y != d_nodes[idx].y)
        throw string("Incorrect depot struct(data::check.cc)");  
  
  for (int idx = d_nDepots; idx < d_nNodes; ++idx)
    if (d_customers[idx - d_nDepots].x != d_nodes[idx].x
      or d_customers[idx - d_nDepots].y != d_nodes[idx].y
      or d_customers[idx - d_nDepots].w != d_nodes[idx].w)
        throw string("Incorrect customer struct(data::check.cc)");  
  
  
        
  cout << "Data correct" << endl;
}


