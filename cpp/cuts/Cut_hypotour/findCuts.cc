#include "./Cut_hypotour.ih"

/*
 * 
 */

vector<CutReturn> Cut_hypotour::findCuts(vector<vector<double>> const &x)
{
  int constexpr nMaxCuts = 100;
  cout << "hypotour \n";

  vector<CutReturn> cuts_tmp;

  CnstrMgrPointer myCutsCMP = call_lysgard_hypotour(x);
  
  vector<int>    tail(d_nNodes *d_nNodes, 0);
  vector<int>    head(d_nNodes *d_nNodes, 0);
  vector<double> coef(d_nNodes *d_nNodes, 0);
  
  for (int i = 0; i < myCutsCMP->Size; ++i)
  {
    CutReturn cut;
    cut.rhs = myCutsCMP->CPL[i]->RHS;
    
    for (int j = 1; j <= myCutsCMP->CPL[i]->IntListSize; ++j)
    {
      int const tail    = myCutsCMP->CPL[i]->IntList[j] + d_nDepots - 1;
      int const head    = myCutsCMP->CPL[i]->ExtList[j]+ d_nDepots - 1;
      double const coef = myCutsCMP->CPL[i]->CoeffList[j];
      
      if (tail == d_nNodes and head < d_nNodes) // tail should be vector of d_nDepot
      {
        for (int const d: d_iDepots)
        {
          cut.add(coef, d, head);
          cut.add(coef, head, d);
        }
      }
      
      else if (tail < d_nNodes and head == d_nNodes)
      {
        for (int const d: d_iDepots)
        {
          cut.add(coef, tail, d);
          cut.add(coef, d, tail);
        }
      }
      
      else if (tail < d_nNodes and head < d_nNodes)
      {
        cut.add(coef, head, tail);
        cut.add(coef, tail, head);
      }
    }

    cuts_tmp.push_back(cut);
  }
  
  myCutsCMP->Size = 0;
  CMGR_FreeMemCMgr (&myCutsCMP);
  
  vector<CutReturn> cuts;
  cuts.reserve(nMaxCuts);
  
  int nMax = min(nMaxCuts, (int)cuts_tmp.size());
  
  for (int idx = 0; idx < nMax; ++idx)
    cuts.emplace_back(cuts_tmp[idx]);
  
  return cuts;
}
