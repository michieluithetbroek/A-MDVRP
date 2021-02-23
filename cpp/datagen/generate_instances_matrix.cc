#include "datagen.ih"
#include <string>

void DataGen::generate_instances_matrix(int seed, int nInstances, 
                               int nDepots, int nCustomers, 
                               int capMin, int capMax, 
                               int weightMin, int weightMax,
                               int depotMin, int depotMax,
                               int mintourMin, int mintourMax,
                               int maxtourMin, int maxtourMax,
                               std::string filename   
                              )
{
  for (int idx = 0; idx != nInstances; ++idx)
  {
    random2::setSeed(seed + idx + nCustomers * nDepots);
    for (int t =0; t != 10; ++t)
      random2::runif_int<int>(capMin, capMax);
    
    ofstream file(filename + "/n" + to_string(nCustomers) + "m" + to_string(nDepots) + "_" + to_string(idx));
    
    if (not file.is_open())
      throw string("DataGen::generate_instances -> niet gouwd\n");
    
    // print first line, containing seed and instance name
    file << "Seed " << seed + idx << " - Instance: n" << nCustomers << "m" << nDepots << "_" << idx << '\n';
  
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
    
    int nNodes = nDepots + nCustomers;
    vector<vector<int>> dist(nNodes, vector<int>(nNodes, 0));
    file << '\n';
    for (int i = 0; i < nNodes; ++i)
    {
      for (int j = 0; j < nNodes; ++j)
      {
        if (i == j)
          file << "0" << " ";
        else
          file << random2::runif_int<int>(0, 1000) << " ";
      }
      file << '\n';
    }
     
    file << "\nDepot information" << '\n';
    for (int jdx = 0; jdx != nDepots; ++jdx)
      file << random2::runif_int<int>(depotMin, depotMax) << '\n';
    
    
    // give customer information x, y, weight 
    file << "\nCustomer information" << '\n';
    
    for (int jdx = 0; jdx != nCustomers; ++jdx)
      file << random2::runif_int<int>(weightMin, weightMax) << '\n';
    

  
  }
}

