#include "data.ih"

/*
 * TODO Shouldn't there be a globally accessible function
 * that returns the complete file name? We al
 * 
 */

void Data::readFile_own()
{
  // ----------------------------------
  // --- Determine the file name    ---
  // ----------------------------------
  
  string filename("instances/own/");
  
  switch (d_inst)
  {
    case PROBLEMTYPE::MDATSP:
      filename += "MDATSP-";
      break;
      
    case PROBLEMTYPE::MDAMTSP:
      filename += "MDAmTSP-";
      break;
      
    case PROBLEMTYPE::MDACVRP:
      filename += "MDACVRP-";
      break;
      
    case PROBLEMTYPE::ACLRP:
      filename += "ACLRP-";
      break;
      
    default:
      throw string("Unknown problem type (Data::readFile_own)");
  }
  
  switch (d_asy)
  {
    case ASYCLASS::A:
      filename += "A/n";
      break;
      
    case ASYCLASS::B:
      filename += "B/n";
      break;
      
    case ASYCLASS::CRC:
      filename += "CRC/n";
      break;
      
    default:
      throw string("Unknown assymetric class (Data::readFile_own)");
  }
  
  filename += string(to_string(d_nCustomers) + "m" 
               + to_string(d_nDepots) + "_" 
               + to_string(d_instance));
  
  
  
  // ----------------------------------
  // --- Read the file              ---
  // ----------------------------------
  
  // Set index vectors
  for (size_t idx = 0; idx < d_nDepots; ++idx)
    d_iDepots.push_back(idx);
  
  for (size_t idx = d_nDepots; idx < d_nNodes; ++idx)
    d_iCustomers.push_back(idx);
  
  for (size_t idx = 0; idx < d_nNodes; ++idx)
    d_iNodes.push_back(idx);
  

  ifstream file(filename);
  cout << filename << endl;
  string line;
  
  // skip irrelevant
  for (int idx = 0; idx != 3; ++idx)
    getline(file, line);
  string dummy;

  file >> dummy >> d_vehicleCap;
  file >> dummy >> d_tourMin;
  cout << d_tourMin << endl;
  file >> dummy >> d_tourMax;
  
  if (d_inst == PROBLEMTYPE::MDAMTSP)
    d_vehicleCap = d_tourMax;    

  cout << "Vehicle cap: " << d_vehicleCap << endl;
  
  // skip heading
  getline(file, line);  // skip current line
  getline(file, line);  // skip empty line
   
  // read distance matrix;
  for (int idx = 0; idx != d_nNodes; ++idx)
    for (int jdx = 0; jdx != d_nNodes; ++jdx)
      file >> d_cost[idx][jdx];
    

  // skip heading
  getline(file, line);
  getline(file, line);
  getline(file, line);


  
  if (d_asy != ASYCLASS::A and d_asy != ASYCLASS::B)
  {   
    // read depot 
    for (int idx = 0; idx != d_nDepots; ++idx)
    {
      int x, y, w;
      file >> x >> y >> w;

      d_depots.emplace_back(x, y);    
      d_nodes.emplace_back(x,y,w);
    }
        // skip heading
    getline(file, line);
    getline(file, line);
    getline(file, line);

    // read cust 
    for (int idx = 0; idx != d_nCustomers; ++idx)
    {
      int x, y, w;
      file >> x >> y >> w;

      d_customers.emplace_back(x, y, w);    
      d_nodes.emplace_back(x,y,w);
    }

  }
  
  else 
  { 
    // read depot 
    for (int idx = 0; idx != d_nDepots; ++idx)
    {
      int  w;
      file >> w;
      d_depots.emplace_back(-1, -1);    
      d_nodes.emplace_back(-1,-1, w);
    }
    
    // skip heading
    getline(file, line);
    getline(file, line);
    getline(file, line);

    // read customers
    for (int idx = 0; idx != d_nCustomers; ++idx)
    {
      int w;
      file >> w;

      d_customers.emplace_back(-1, -1, w);    
      d_nodes.emplace_back(-1, -1, w);
    }
  }
    


  
  
  // set demand vector;
  for (int i: d_iNodes)
    d_demands[i] = d_nodes[i].w;
  
  for (int i: d_iDepots)
    d_demands[i] = 0;
  
  if (P_TYPE == PROBLEMTYPE::ACLRP)
  {
    for (int i: d_iDepots)
      d_depotCost[i] = d_nodes[i].w;  // w is cost for depot TODO make neat
  }
}


