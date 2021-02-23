#include "./../../main.ih"

void create_MDAmTSP_benchmarkC_RC()
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
  int const xmin       = 0;
  int const xmax       = 500;
  int const ymin       = 0;
  int const ymax       = 500;
  int const Lmin       = 2;
  int const Lmax       = 6;
  int const Umin       = 15;
  int const Umax       = 25;   
  
  string const filename = string("instances/own/MDAmTSP-CRC");
  
  DataGen gen; 
  
  set_global_enums(5);
  auto const characs = get_characs(5);

  for (auto el: characs)
    gen.generate_instancesRC(seed, nInstances, el[0], el[1],
                             xmin, xmax, ymin, ymax, capmin, capmax,
                             weightmin, weightmax, depotmin, depotmax,
                             Lmin, Lmax, Umin, Umax, filename);
}
