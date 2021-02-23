#include "./../../main.ih"

string getPrintInstanceName(int n, int m, int rep)
{
  string instName;
  
  if (P_TYPE == PROBLEMTYPE::MDATSP)
    instName += "A-MDTSP";
  
  else if (P_TYPE == PROBLEMTYPE::MDAMTSP)
    instName += "A-MDmTSP";
  
  else if (P_TYPE == PROBLEMTYPE::MDACVRP)
    instName += "A-MDCVRP";
  
  else if (P_TYPE == PROBLEMTYPE::ACLRP)
    instName += "A-CLRP";
  
  else
    throw string("Unknown instance type (getPrintInstanceName.cc)");
  
  instName += "_" + to_string(n) + "_" 
              + to_string(m) + "_"
              + to_string(rep);
  
  return instName;
}

string getPrintInstanceName()
{
  string instName;
  
  if (P_TYPE == PROBLEMTYPE::MDATSP)
    instName += "A-MDTSP";
  
  else if (P_TYPE == PROBLEMTYPE::MDAMTSP)
    instName += "A-MDmTSP";
  
  else if (P_TYPE == PROBLEMTYPE::MDACVRP)
    instName += "A-MDCVRP";
  
  else if (P_TYPE == PROBLEMTYPE::ACLRP)
    instName += "A-CLRP";
  
  else
    throw string("Unknown instance type (getPrintInstanceName.cc)");
  
  return instName;
}
