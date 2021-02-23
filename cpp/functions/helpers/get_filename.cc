#include "./../../main.ih"

/*
 * TODO where is this function used? Maybe it should be 
 * a function that is private within some class
 * 
 * Adds the specific instance file name to the input directory
 * 
 */

string get_filename(int dep, int cust, int rep, string folder)
{ 
  string filename(folder);

  switch (P_TYPE)
  {
    case PROBLEMTYPE::MDATSP:
      filename += "MDATSP-";
      break;
      
    case PROBLEMTYPE::MDAMTSP:
      filename += "MDAmTSP-";
      break;
      
    case PROBLEMTYPE::MDACVRP:
      filename += "MDACVRP-";
      break;
      
    case PROBLEMTYPE::ACLRP:
      filename += "ACLRP-";
      break;
      
    default:
      throw string("Unknown problem type (Data::readFile_own)");
  }
  
  switch (DATA_ASYMMETRY)
  {
    case ASYCLASS::A:
      filename += "A/n";
      break;
      
    case ASYCLASS::B:
      filename += "B/n";
      break;
      
    case ASYCLASS::CRC:
      filename += "CRC/n";
      break;
      
    default:
      throw string("Unknown assymetric class (Data::readFile_own)");
  }
  
  filename += string(to_string(cust) + "m" 
              + to_string(dep) + "_" 
              + to_string(rep));
  
  return filename;
}
