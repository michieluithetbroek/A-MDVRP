#include "data.ih"

/*
 * Set the globals corresponding to the current problem type
 * 
 */

void Data::setSettings()
{
  switch (d_inst)
  {
    case PROBLEMTYPE::MDATSP:
      g_vehicleCapacity = false;
      g_depotCost       = false;
      g_atMostOneTour   = true;
      g_tourSize        = false;
      
      break;
      
    case PROBLEMTYPE::MDAMTSP:
      g_vehicleCapacity = false;
      g_depotCost       = false;
      g_atMostOneTour   = false;
      g_tourSize        = true;  
      
      break;
      
    case PROBLEMTYPE::MDACVRP:
      g_vehicleCapacity = true;
      g_depotCost       = false;
      g_atMostOneTour   = false;
      g_tourSize        = false;
      
      break;
      
    case PROBLEMTYPE::ACLRP:
      g_vehicleCapacity = true;
      g_depotCost       = true;
      g_atMostOneTour   = false;
      g_tourSize        = true;
      
      break;
      
    default: 
      throw string("Unknown setting (data::setSettings.cc)");
  }
}
