#include "./../../main.ih"


/*
 * Skip nLines of the given file stream
 */

void skipLines (std::ifstream &fstr, int nLines)
{
  std::string dummy;
  
  for (int idx = 0; idx < nLines; ++idx)
    std::getline(fstr, dummy);
}
