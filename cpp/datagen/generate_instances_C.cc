#include "datagen.ih"
#include <tuple>

void DataGen::generate_instancesR(int seed, int nInstances, 
                                 int nDepots, int nCustomers, 
                                 int xMin, int xMax, int yMin, int yMax, 
                                 int capMin, int capMax, 
                                 int weightMin, int weightMax,
                                 int depotMin, int depotMax,
                                 int mintourMin, int mintourMax,
                                 int maxtourMin, int maxtourMax,
                                 string filename
                                )  
{
  
  for (int idx = 0; idx != nInstances; ++idx)
  {
    vector<tuple<int, int, int>> depotCoord;
    vector<tuple<int, int, int>> custCoord;
    vector<tuple<int, int, int>> Coord;

    random2::setSeed(seed + idx + nCustomers * nDepots);
    for (int t =0; t != 10; ++t)
      random2::runif_int<int>(capMin, capMax);
    
    
    ofstream file(filename + "/n" + to_string(nCustomers) + "m" + to_string(nDepots) + "_" + to_string(idx));
    
    if (not file.is_open())
      throw string("DataGen::generate_instances -> niet gouwd\n");
    
    // print first line, containing seed and instance name
    file << "Seed " << seed << " - Instance: n" << nCustomers << "m" << nDepots << "_" << idx << '\n';
  
    // print ncustomers, and ndepots.
    file << "n " << nCustomers << '\n'
         << "m " << nDepots    << '\n';
    
    // randomly draw vehicle cap within bounds
    int cap = random2::runif_int<int>(capMin, capMax);
    file << "Q " << cap << '\n';
    
    int tourMin = random2::runif_int<int>(mintourMin, mintourMax);
    file << "L " << tourMin << '\n';
    
    int tourMax = random2::runif_int<int>(maxtourMin, maxtourMax);
    file << "U " << tourMax << '\n';
    
    // draw coordinates, weight of cust and cost of depots
    for (int jdx = 0; jdx != nDepots; ++jdx)
      Coord.push_back(make_tuple(random2::runif_int<int>(xMin, xMax), random2::runif_int<int>(yMin, yMax), random2::runif_int<int>(depotMin, depotMax)));
 
    int gen_customers = 0;
    while (gen_customers < nCustomers)
    {
      int centerX = random2::runif_int<int>(xMin, xMax);
      int centerY = random2::runif_int<int>(yMin, yMax);
      int width   = random2::runif_int<int>(20, 50);
      int size = random2::runif_int<int>(nCustomers/10, nCustomers/5);
      
      for (int i = 0; i < size and gen_customers < nCustomers; ++i)
      {
        gen_customers++;
        Coord.push_back(make_tuple(random2::runif_int<int>(centerX - width, centerX + width),
                                       random2::runif_int<int>(centerY - width, centerY + width),
                                   random2::runif_int<int>(weightMin, weightMax)
                                   ));
                                   
      }
    }
    
    for (int jdx = 0; jdx != nCustomers; ++jdx)
    {
      
      Coord.push_back(make_tuple(random2::runif_int<int>(xMin, xMax),
                                     random2::runif_int<int>(yMin, yMax),
                                     random2::runif_int<int>(weightMin, weightMax)
                          ));
      
    } 
    // create dist matrix;
    vector<vector<int>> dist(nDepots + nCustomers, vector<int>(nDepots + nCustomers, 0));
    for (int i =0 ; i != nDepots + nCustomers; ++i)
      for (int j = 0; j != nDepots + nCustomers; ++j)
      {
        int x1 = get<0>(Coord[i]);
        int x2 = get<0>(Coord[j]);
        int y1 = get<1>(Coord[i]);
        int y2 = get<1>(Coord[j]);
      
        dist[i][j] = sqrt( (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
      }
      
    // print dist matrix
    file << '\n';
    for (int i =0 ; i != nDepots + nCustomers; ++i)
    {
      for (int j = 0; j != nDepots + nCustomers; ++j)
      {
        if (i == j)
          file << "0 ";
        else
          file << dist[i][j] + random2::runif_int<int>(0, 20) << " ";
        
      }
      file << '\n';
    }
    
    file << '\n';
    // give customer information x, y, weight 
    file << "Depot information" << '\n';
    for (int i = 0; i != nDepots; ++i)
      file << get<0>(Coord[i]) << " " << get<1>(Coord[i]) << " " << get<2>(Coord[i]) << '\n' ;
    file << '\n';
    
    file << "Cust information" << '\n';
    for (int i = nDepots; i != nCustomers + nDepots; ++i)
      file << get<0>(Coord[i]) << " " << get<1>(Coord[i]) << " " << get<2>(Coord[i]) << '\n' ;
    

  } 
}

