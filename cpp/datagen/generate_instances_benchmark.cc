#include "datagen.ih"


void DataGen::generate_instances_benchmark(int seed, int nInstances,
                                 int nDepots, int nCustomers,
                                 int xMin, int xMax,
                                 int yMin, int yMax,
                                 int capMin, int capMax,
                                 int weightMin, int weightMax)
{
  for (int idx = 0; idx != nInstances; ++idx)
  {
    random2::setSeed(seed +  10 * nDepots + 500*nCustomers + idx);
    
    ofstream file("instances_benchmark/n" + to_string(nCustomers) + "m" + to_string(nDepots) + "_" + to_string(idx));
    
    if (not file.is_open())
      throw string("DataGen::generate_instances -> niet gouwd\n");
    
    // print first line, containing seed and instance name
    file << "Seed " << seed << " - Instance: n" << nCustomers << "m" << nDepots << "_" << idx << '\n';
   
    // print ncustomers, and ndepots.
    file << "n " << nCustomers << '\n'
         << "m " << nDepots    << '\n';
    
    // randomly draw vehicle cap within bounds
    int const cap = random2::runif_int<int>(capMin, capMax);
    file << "Q " << cap << '\n';
    
    //give coordinates to depot  x,y
    file << "Depot information" << '\n';
    for (int jdx = 0; jdx != nDepots; ++jdx)
      file << random2::runif_int<int>(xMin, xMax) << " " << random2::runif_int<int>(yMin, yMax) << '\n';
    
    // give customer information x, y, weight 
    file << "Customer information" << '\n';
    
    for (int jdx = 0; jdx != nCustomers; ++jdx)
      file << random2::runif_int<int>(xMin, xMax) << " " 
           << random2::runif_int<int>(yMin, yMax) << " "
           << random2::runif_int<int>(weightMin, weightMax) << '\n';
  }
}

