#include "./Cut_framed_cap.ih"

vector<CutReturn> Cut_framed_cap::findCuts(vector<vector<double>> const &x)
{
  vector<CutReturn> cuts; 

  CnstrMgrPointer myCutsCMP = call_lysgard_framed_cap(x);
  
  for (int i = 0; i < myCutsCMP->Size; ++i)
  {
    vector<int> label(d_nCustomers + 1, 0);
    int maxIdx = 0; 
    
    for (int subsetNr = 1; subsetNr <= myCutsCMP->CPL[i]->ExtListSize; ++subsetNr)
    {
      int const minIdx = maxIdx + 1;
      maxIdx = minIdx + myCutsCMP->CPL[i]->ExtList[subsetNr] - 1;
      
      for (int j = minIdx; j <= maxIdx; ++j)
      {
        int const k = myCutsCMP->CPL[i]->IntList[j];
        label[k] = subsetNr;
      }
    }
    
    double const RHS = myCutsCMP->CPL[i]->RHS;
    double LHS = 0;
    
    CutReturn cut;
    cut.rhs = -RHS;
    
    // A. findd -1/2x(d(S))
    
    // A1. find the frame (all elements k with label[k] > 0)
    vector<int> frame;
    
    for (int i = 0, n = label.size(); i != n; ++i)
      if (label[i] > 0)
        frame.push_back(i + d_nDepots - 1);
    
//     cout << "Frame: ";
//     for (int el: frame)
//       cout << el << " ";
//     cout << endl;
      
    // A2. calculate cutset of frame
    
      
    for (int const f: frame)
    {
      for (int const c: d_iNodes)
      {
        if (find(cbegin(frame), cend(frame), c) == cend(frame))
        {
          LHS += (x[f][c] + x[c][f]);
          
          cut.add(-1, f, c);
          cut.add(-1, c, f);
        }
      }
    }
        
    // A3. calculate cutset for the sets S
    int const nSets = *max_element(cbegin(label), cend(label));
    
    for (int setIdx = 1; setIdx <= nSets; ++setIdx)
    {   
      
      vector<int> set;
      for (int i = 0, n = label.size(); i != n; ++i)
        if (label[i]  == setIdx)
          set.push_back(i + d_nDepots - 1);
        
//       cout << "Set " << setIdx << " ";
//       for (int s: set)
//         cout << s << " ";
//       cout << endl;

  
      for (int const f: set)
      {
        for (int const c: d_iNodes)
        {
          if (find(cbegin(set), cend(set), c) == cend(set))
          {
            LHS += (x[f][c] + x[c][f]);
            
            cut.add(-1, f, c);
            cut.add(-1, c, f);
          }
        }
      }
    }
    
// //     cout << "LHS: " << LHS << "\n" << "RHS: " << RHS << endl;
  
    
    if (LHS + 0.1 + d_eps < RHS)
      cuts.push_back(cut);
  }
  
  myCutsCMP->Size = 0;
  
  CMGR_FreeMemCMgr (&myCutsCMP);
  
  return cuts;
}
