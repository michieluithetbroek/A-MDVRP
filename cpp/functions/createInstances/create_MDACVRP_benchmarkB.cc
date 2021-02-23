#include "./../../main.ih"

void create_MDACVRP_benchmarkB()
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
  
  string const filename = string("instances/own/MDACVRP-B");
  
  DataGen gen; 
  
  set_global_enums(7);
  auto const characs = get_characs(7);
                                 
  for (auto el: characs)
    gen.generate_instances_matrix_b(seed, nInstances,
                                    el[0], el[1], 
                                    capmin, capmax, 
                                    weightmin, weightmax, 
                                    depotmin, depotmax,
                                    Lmin, Lmax, 
                                    Umin, Umax, 
                                    filename);
}
