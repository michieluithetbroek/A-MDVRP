#include "data.ih"

/*
 * Print the data currently loaded into the Data struct
 * 
 */

void Data::print()
{
  cout << endl
       << "nDepots:     " << d_nDepots << endl
       << "nCustomers:  " << d_nCustomers << endl
       << "nNodes:      " << d_nNodes << endl
       << "Vehicle cap: " << d_vehicleCap << endl
       << "Tour min:    " << d_tourMin << endl
       << "Tour max:    " << d_tourMax << endl;

  cout << "\n--- Depots (x, y, cost) --------------------" << endl;
  
  for (int idx = 0; idx < d_nDepots; ++idx)
    cout << d_depots[idx].x << " " 
         << d_depots[idx].y << " " 
         << d_depotCost[idx] << endl;
  
  cout << "\n--- Customers ------------------------------" << endl;
  
  for (auto &el: d_customers)
    cout << el.x << " " 
         << el.y << " "
         << el.w << endl;
}


