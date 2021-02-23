#include "./Cut_example.ih"

vector<CutReturn> Cut_example::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  /*
   * Seperate the valid inequalities here and store them into
   * vector<CutReturn>. The definition of the CutReturn struct
   * can be found in the header file cut.h. Note that each cut
   * should be written as a smaller than inequality.
   */
  
  /*
   * Example
   * The cut 8 * x[1][2] + 1 * x[2][1] <= 1 is created as follows
   */
  
  CutReturn cut;
 
  cut.rhs = 1;
  cut.add(8, 1, 2);
  cut.add(1, 2, 1);
  
  cuts.push_back(cut);

  
  return cuts;
}
