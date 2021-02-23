#include "./../../main.ih"

void create_ACLRP_benchmarkA()
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
  int const depotmin   = 500;
  int const depotmax   = 3000;  
  int const Lmin       = 0;
  int const Lmax       = 0;
  int const Umin       = 1000;
  int const Umax       = 1000;  
  
  string const filename = string("instances/own/ACLRP-A");
  
  DataGen gen; 
  
  set_global_enums(9);
  auto const characs = get_characs(9);                                 
                                 
  for (auto el: characs)
    gen.generate_instances_matrix(seed, nInstances, el[0], el[1],
                                  capmin, capmax, weightmin, weightmax,
                                  depotmin, depotmax, 
                                  Lmin, Lmax, Umin, Umax, filename);
}
