#include "./../../main.ih"

void create_MDAmTSP_benchmarkA()
{  
  /* -----------------------------------
   * ----  Create instances 
   * -----------------------------------
   */
    
  int const seed       = 123;
  int const nInstances = 3;
  int const capmin     = 9999;
  int const capmax     = 9999;
  int const weightmin  = 1;
  int const weightmax  = 1;
  int const depotmin   = 1;
  int const depotmax   = 1;  
  int const Lmin       = 2;
  int const Lmax       = 6;
  int const Umin       = 10;
  int const Umax       = 20;
  
  string const filename = string("instances/own/MDAmTSP-A");
  
  DataGen gen;
  
  set_global_enums(3);
  auto const characs = get_characs(0);
  
  for (auto el: characs)
    gen.generate_instances_matrix(seed, nInstances, el[0], el[1],
                                  capmin, capmax, weightmin, weightmax,
                                  depotmin, depotmax, 
                                  Lmin, Lmax, Umin, Umax, filename);
  
}
