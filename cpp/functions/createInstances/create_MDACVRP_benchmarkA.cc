#include "./../../main.ih"

void create_MDACVRP_benchmarkA()
{  
  /* -----------------------------------
   * ----  Create instances 
   * -----------------------------------
   */

  int const seed       = 123;
  int const nInstances = 3;
  int const capmin     = 150;
  int const capmax     = 300;
  int const weightmin  = 15;
  int const weightmax  = 25;
  int const depotmin   = 1;
  int const depotmax   = 1;  
  int const Lmin       = 0;
  int const Lmax       = 0;
  int const Umin       = 1000;
  int const Umax       = 1000;  
  
  string const filename = string("instances/own/MDACVRP-A");
  
  DataGen gen; 
  
  set_global_enums(6);
  auto const characs = get_characs(6);                                 
                                 
  for (auto el: characs)
    gen.generate_instances_matrix(seed, nInstances, el[0], el[1],
                                  capmin, capmax, weightmin, weightmax,
                                  depotmin, depotmax,
                                  Lmin, Lmax, Umin, Umax, filename);
}
