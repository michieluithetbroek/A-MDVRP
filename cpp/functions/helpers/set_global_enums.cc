#include "./../../main.ih"


/*
 * de-hashed the instance type to obtain the global
 * INSTANCE and DATA_ASYMMETRY
 * 
 * NOTE The Santos benchmarks works slightly different
 * It sets the INSTANCE to MDATSP since we need these constraints
 * However, we set DATA_ASYMMETRY to SANTOS since the Data
 * struct needs to known which file to read and by default we read 
 * our own instance files.
 */

void set_global_enums (int instanceType)
{
  // Get the instance type
  if (instanceType == 12)
    P_TYPE = PROBLEMTYPE::MDATSP; // TODO this is misuse for santos
  
  if (instanceType < 12)
    P_TYPE = PROBLEMTYPE::ACLRP;
  
  if (instanceType < 9)
    P_TYPE = PROBLEMTYPE::MDACVRP;
  
  if (instanceType < 6)
    P_TYPE = PROBLEMTYPE::MDAMTSP;
  
  if (instanceType < 3)
    P_TYPE = PROBLEMTYPE::MDATSP;

  
  // Which data class
  
  if (instanceType % 3 == 0)
    DATA_ASYMMETRY = ASYCLASS::A;
  
  else if (instanceType % 3 == 1)
    DATA_ASYMMETRY = ASYCLASS::B;
  
  else if (instanceType % 3 == 2)
    DATA_ASYMMETRY = ASYCLASS::CRC;
  
  if (instanceType == 12)
    DATA_ASYMMETRY = ASYCLASS::SANTOS;
}
