#include "./../../main.ih"

void create_ACLRP_benchmarkC_RC()
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
  int const xmin       = 0;
  int const xmax       = 500;
  int const ymin       = 0;
  int const ymax       = 500;
  
  string const filename = string("instances/own/ACLRP-CRC");
  
  DataGen gen; 
  
  set_global_enums(11);
  auto const characs = get_characs(11);        
                           
  for (auto el: characs)
    gen.generate_instancesRC(seed, nInstances, 
                             el[0], el[1], 
                             xmin, xmax, 
                             ymin, ymax, 
                             capmin, capmax, 
                             weightmin, weightmax, 
                             depotmin, depotmax, 
                             Lmin, Lmax, 
                             Umin, Umax, 
                             filename);
}
