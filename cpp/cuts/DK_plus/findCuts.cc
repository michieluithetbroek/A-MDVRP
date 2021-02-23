#include "./DK_plus.ih"

/*
 * 
 */

vector<CutReturn> DK_plus::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  auto const components = graphFunctions::LEMON_get_connected_components(x);

  for (auto const &iComponent: components)
  {
    if (iComponent.size() == 1)
      continue;
    
    vector<int> sequence(iComponent.size(), 0);
    
    for (int const idx: iComponent)
    {
      d_maxPhi = 0;
      sequence[0] = idx;
      extend(1, 0, 0, x, sequence, iComponent, cuts);
    }
  }
  
  return cuts;
}
