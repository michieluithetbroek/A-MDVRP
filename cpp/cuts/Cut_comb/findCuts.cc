#include "./Cut_comb.ih"

/* 
 * Strenghtened comb inequalities as in lysgard  (chapter 7)
 */

vector<CutReturn> Cut_comb::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts;
  
  CnstrMgrPointer myCutsCMP = call_lysgard_strengthened_combs(x);
  
  for (int i = 0; i < myCutsCMP->Size; ++i)
  {     
    int const nTeeth = myCutsCMP->CPL[i]->Key;
    double const rhs = myCutsCMP->CPL[i]->RHS; 
    
    vector<vector<int>> inTooth = parse_inTooth(myCutsCMP, i);
      
    bool violated = false;
    
    // check if T_i \cup T_j = \emptyset      
    for (int j = 1, n = inTooth.size(); j != n; ++j)
    {
      int tmp = 0;
      for (int j2 = 1, m = inTooth[j].size(); j2 < m; ++j2)
        tmp += inTooth[j][j2];
      
      if (tmp > 1) 
        violated = true;
    }
    
    if (violated)
      continue;
    
    // initialize lhs
    // The next function return lhs by reference
    double lhs = 0.0;
    
    // calculate the cut
    CutReturn cut = calc_strengthened_comb_cut(lhs, nTeeth, inTooth, x);     

    cut.rhs = rhs;
    
    // add if violated current LP
    if (lhs > rhs + d_eps)
      cuts.push_back(cut);
  }
  
  myCutsCMP->Size = 0;
  CMGR_FreeMemCMgr (&myCutsCMP);
  
  return cuts;
}