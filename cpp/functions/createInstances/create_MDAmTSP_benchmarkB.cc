#include "./../../main.ih"

void create_MDAmTSP_benchmarkB()
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
  int const Umin       = 15;
  int const Umax       = 25;  
  
  string const filename = string("instances/own/MDAmTSP-B");
  
  DataGen gen; 
  
  set_global_enums(4);
  auto const characs = get_characs(4);
  
  for (auto el: characs)
    gen.generate_instances_matrix_b(seed, nInstances, el[0], el[1],
                                    capmin, capmax, weightmin,
                                    weightmax, depotmin, depotmax,
                                    Lmin, Lmax, Umin, Umax, filename);
}
