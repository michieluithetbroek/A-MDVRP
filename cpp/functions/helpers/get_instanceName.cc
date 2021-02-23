#include "./../../main.ih"

/*
 * 
 */

string getInstanceName()
{
  string instName;
  
  if (P_TYPE == PROBLEMTYPE::MDATSP)
    instName += "MDATSP-";
  
  else if (P_TYPE == PROBLEMTYPE::MDAMTSP)
    instName += "MDAmTSP-";
  
  else if (P_TYPE == PROBLEMTYPE::MDACVRP)
    instName += "MDACVRP-";
  
  else if (P_TYPE == PROBLEMTYPE::ACLRP)
    instName += "ACLRP-";
  
  else
    throw string("Unknown instance type (getInstanceName.cc)");
  
  
  if (DATA_ASYMMETRY == ASYCLASS::A)
    instName += "A";
  
  else if (DATA_ASYMMETRY == ASYCLASS::B)
    instName += "B";
    
  else if (DATA_ASYMMETRY == ASYCLASS::CRC)
    instName += "CRC";
  
  else
    throw string("Unknown asymmetry type (getInstanceName.cc)");
  
  return instName;
}
