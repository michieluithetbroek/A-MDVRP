#pragma once

#include<iosfwd>

/*
 * TODO Why is this a class (as we also have a folder 
 * called 'functions/createInstances')? Maybe all the 
 * functions there should be public functions of this 
 * class and then the functions below can be private
 * member functions.
 * 
 * TODO Do we actually use all the functions below?
 */

class DataGen
{
    
  public:
  /* void generate_instances(int seed, int nInstances, 
                            int nDepots, int nCustomers, 
                            int xMin, int xMax, 
                            int yMin, int yMax, 
                            int capMin, int capMax, 
                            int weightMin, int weightMax);
    
    void generate_instances(int seed, int nInstances, 
                            int nDepots, int nCustomers, 
                            int xMin, int xMax, 
                            int yMin, int yMax, 
                            int capMin, int capMax, 
                            int weightMin, int weightMax,
                            string filename
                          ); */
    
  void generate_instances_benchmark (int seed, int nInstances, 
                          int nDepots, int nCustomers, 
                          int xMin, int xMax, 
                          int yMin, int yMax, 
                          int capMin, int capMax, 
                          int weightMin, int weightMax);

  void generate_instances_matrix (int seed, int nInstances, 
                                int nDepots, int nCustomers, 
                                int capMin, int capMax, 
                                int weightMin, int weightMax,
                                int depotMin, int depotMax,
                                int mintourMin, int mintourMax,
                                int maxtourMin, int maxtourMax,
                                std::string filename
                                );

  void generate_instances_matrix_b (int seed, int nInstances, 
                                int nDepots, int nCustomers, 
                                int capMin, int capMax, 
                                int weightMin, int weightMax,
                                int depotMin, int depotMax,
                                int mintourMin, int mintourMax,
                                int maxtourMin, int maxtourMax,
                                std::string filename
                                );

  void generate_instancesR (int seed, int nInstances, 
                                  int nDepots, int nCustomers, 
                                  int xMin, int xMax, int yMin, int yMax, 
                                  int capMin, int capMax, 
                                  int weightMin, int weightMax,
                                  int depotMin, int depotMax,
                                  int mintourMin, int mintourMax,
                                  int maxtourMin, int maxtourMax,
                                  std::string filename
                                  );
  
  void generate_instancesC (int seed, int nInstances, 
                                  int nDepots, int nCustomers, 
                                  int xMin, int xMax, int yMin, int yMax, 
                                  int capMin, int capMax, 
                                  int weightMin, int weightMax,
                                  int depotMin, int depotMax,
                                  int mintourMin, int mintourMax,
                                  int maxtourMin, int maxtourMax,
                                  std::string filename
                                  );
  
  void generate_instancesRC (int seed, int nInstances, 
                                  int nDepots, int nCustomers, 
                                  int xMin, int xMax, int yMin, int yMax, 
                                  int capMin, int capMax, 
                                  int weightMin, int weightMax,
                                  int depotMin, int depotMax,
                                  int mintourMin, int mintourMax,
                                  int maxtourMin, int maxtourMax,
                                  std::string filename
                                  );
};
