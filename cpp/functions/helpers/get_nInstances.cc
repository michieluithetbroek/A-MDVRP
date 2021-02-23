#include "./../../main.ih"


/*
 * 
 */

int get_nInstances()
{
  if (P_TYPE == PROBLEMTYPE::MDATSP)
    return 3 * 15;
  
  if (P_TYPE == PROBLEMTYPE::MDAMTSP)
    return 3 * 23;
  
  return 3 * 21;
}
