#include "./Cut_comb.ih"

void Cut_comb::print_tooth(vector<vector<int>> const &inTooth) const
{
  cout << "Print Tooth overview: \n";
  for (int i = 0, m = inTooth[0].size(); i != m; ++i)
  {
    cout << "Tooth: " << i << ": ";
    for (int j = 1, n = inTooth.size(); j != n; ++j)
    {
      if (inTooth[j][i] == 1)
        cout << j  << " ";
    }
    cout << endl;
  }      
  
  cout << endl << endl;
}