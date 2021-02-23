#include "./Cut_comb.ih"

vector<vector<int>> Cut_comb::parse_inTooth(CnstrMgrPointer myCutsCMP, int i) const
{ 
  int const nTeeth = myCutsCMP->CPL[i]->Key;
  vector<vector<int>> inTooth(d_nCustomers + 2, vector<int>(nTeeth + 1, 0));
  
  for (int k = 1; k <= myCutsCMP->CPL[i]->IntListSize; ++k)
  {
    int const j = myCutsCMP->CPL[i]->IntList[k];
    inTooth[j][0] = 1; 
  }

  for (int t = 1; t <= nTeeth; ++t)
  {
    int const minIdx = myCutsCMP->CPL[i]->ExtList[t];
    int const maxIdx = (t == nTeeth) ? myCutsCMP->CPL[i]->ExtListSize : myCutsCMP->CPL[i]->ExtList[t + 1] - 1;   

    for (int k = minIdx; k <= maxIdx; ++k)
    {
      int const j = myCutsCMP->CPL[i]->ExtList[k];
      inTooth[j][t] = 1;
    }
  }

  // check for the existence of depot in the combs
  vector<int> depotTeeth;
  
  for (int t = 0; t <= nTeeth; ++t)
    if (inTooth[d_nCustomers + 1][t] == 1)
      depotTeeth.push_back(t);


  if (depotTeeth.size() > 0)
  {
    for (int k = 0; k != d_nDepots - 1; ++k)
      inTooth.push_back(inTooth[d_nCustomers + 1]);
  }
  else
  {
    vector<int> tmp(nTeeth + 1, 0); // add all the depots so we include in constraint
    
    for (int k = 0; k != d_nDepots; ++k)
      inTooth.push_back(tmp);
  }
    
  return inTooth;
}