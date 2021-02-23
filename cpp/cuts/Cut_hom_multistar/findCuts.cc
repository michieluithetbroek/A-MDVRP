#include "./Cut_hom_multistar.ih"
 
vector<CutReturn> Cut_hom_multistar::findCuts(vector<vector<double>> const &x)
{
  int constexpr nCutsMax = 10;
  
  vector<pair<CutReturn, double>> cuts_tmp;

  CnstrMgrPointer myCutsCMP = call_lysgard_hom_multistar(x);
    
  for (int i = 0; i < myCutsCMP->Size; ++i)
  {    
    vector<int> Nlist(d_nCustomers + 1, 0);
    vector<int> Tlist(d_nCustomers + 1, 0);
    vector<int> Clist(d_nCustomers + 1, 0);

    if (myCutsCMP->CPL[i]->CType != CMGR_CT_MSTAR)
      continue;

    for (int j = 1; j <= myCutsCMP->CPL[i]->IntListSize; ++j)
      Nlist[j] = myCutsCMP->CPL[i]->IntList[j];
    
    for (int j = 1; j <= myCutsCMP->CPL[i]->ExtListSize; ++j)
      Tlist[j] = myCutsCMP->CPL[i]->ExtList[j];
    
    for (int j = 1; j <= myCutsCMP->CPL[i]->CListSize; ++j)
      Clist[j] = myCutsCMP->CPL[i]->CList[j];
    
    
    
    int const A = myCutsCMP->CPL[i]->A;
    int const B = myCutsCMP->CPL[i]->B;
    int const L = myCutsCMP->CPL[i]->L;
    
    //calc in/out N
    double lhs = 0;
    
    CutReturn cut = calc_hom_multistar(Nlist, Tlist, Clist, A, B, x, lhs);
    cut.rhs = -L;
    
//     cout << "right hand side: " << L << endl << endl << endl;;
    
    if (lhs < L - 0.1 -  d_eps)
      cuts_tmp.push_back(make_pair(cut, L - lhs));
  }
  
  myCutsCMP->Size = 0;
  CMGR_FreeMemCMgr (&myCutsCMP);

  if (cuts_tmp.size() > nCutsMax)
  {
//     cout << "\n\nWe do not add all cuts: " << nCutsMax << " - " << cuts_tmp.size() << endl << endl;
     
    nth_element(begin(cuts_tmp), begin(cuts_tmp) + (size_t) nCutsMax, end(cuts_tmp),
                [](auto const &lhs, auto const &rhs) { return lhs.second < rhs.second;} );
  }
  
  vector<CutReturn> cuts;
  cuts.reserve(nCutsMax);
  
  int const nMax = min(nCutsMax, (int)cuts_tmp.size());
  
  for (int idx = 0; idx < nMax; ++idx)
    cuts.emplace_back(cuts_tmp[idx].first);
  
  return cuts;
}
