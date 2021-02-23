#include "data.ih"


void Data::readFile_santos(int instance, int nDepots, int nRemoveDepots)
{
  if (P_TYPE != PROBLEMTYPE::MDATSP or DATA_ASYMMETRY != ASYCLASS::SANTOS)
    throw string("Enums are incorrect (Data::readFile_santos.cc)");
  
  string const fileName = "instances/instances_santos/bgs-" 
                          + to_string(d_nCustomers) + "-" 
                          + to_string(nDepots)    + "-" 
                          + to_string(instance)   + "a.mdvrp";
  
  ifstream file(fileName);
  
  if (not file.is_open())
    throw string ("Santos file not opened: " 
                  + fileName
                  + "\n\nData::use_santos_data\n\n");
 
  string line;
  
  for (int idx = 0; idx != 4; ++idx)
    getline(file, line);

  for (int idx = 0; idx != d_nCustomers + nDepots; ++idx)
  {
    for (int jdx = 0; jdx != d_nCustomers + nDepots; ++jdx)
    {
      int tmp;
      file >> tmp;
      
      d_cost[idx][jdx] = tmp;
    }

    string x;
    getline (file, x);
  }
  
  // invert some things to make it work (switch depots/customer indices)
  
  // first put for each row, depot in front
  for (int idx = 0; idx != d_cost.size(); ++idx)
  {
    auto &row = d_cost[idx];
    
    for (int jdx = 0; jdx != nDepots; ++jdx)
    {
      int x = row.back();
      row.insert(row.begin(), x);
      row.pop_back(); 
    }
  }
  
  // then switch rows
  for (int idx = 0; idx != nDepots; ++idx)
  {
    auto x = d_cost.back();
    
    d_cost.insert(d_cost.begin(), x);
    d_cost.pop_back();
  }
  
//   cout << "sizes:" << d_cost.size() << " " << d_cost[0].size() << endl;
  
  vector<vector<double>> new_cost(d_nCustomers + d_nDepots, 
                                  vector<double>(d_nCustomers + nDepots, 0)); 
  
//   for (auto el: d_cost)
//   {
//     for (auto el1: el)
//       cout << el1 << " ";
//     cout << endl;
//   }
  
  // -------------------------------
  // --- remove depots in costs  ---
  // -------------------------------
  
  int ctr = 0;
  for (size_t idx = 0; idx != d_cost.size(); ++idx)
  {
    if (idx < nRemoveDepots)
      continue;
    
    vector<double> tmp = d_cost[idx];
    new_cost[ctr++] = tmp;
  }

  for (size_t idx = 0; idx != new_cost.size(); ++idx)
    for (int jdx = 0; jdx < nRemoveDepots; ++jdx)
      new_cost[idx].erase(begin(new_cost[idx]), begin(new_cost[idx]) + 1);

  d_cost = new_cost;
}


