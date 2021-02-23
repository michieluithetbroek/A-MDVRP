#include "./Cut_cap.ih"

vector<CutReturn> Cut_cap::findCuts(vector<vector<double>> const &x)
{
  vector<int> edgeTail = {{0}};
  vector<int> edgeHead = {{0}};
  vector<double> edgeX = {{0}};

  graphFunctions::transform_to_lysgard_graph_single_depot(x, edgeTail, edgeHead, edgeX);
  
  CnstrMgrPointer MyCutsCMP;
  CnstrMgrPointer MyOldCutsCMP;

  // ALERT These variables has to be freed!
  // Due to other libraries we are bound to C style..
  
  CMGR_CreateCMgr (&MyCutsCMP, 100);
  CMGR_CreateCMgr (&MyOldCutsCMP, 100);  // Contains no cuts initially
  
  int    constexpr MaxNoOfCuts       = 100;
  double constexpr EpsForIntegrality = 0.0001;
  
  double MaxViolation       = 0;
  char   IntegerAndFeasible = 0;
  
  CAPSEP_SeparateCapCuts(d_nCustomers,
                         d_lysgard_demand.data(), 
                         d_vehicleCap,
                         edgeTail.size() - 1,
                         edgeTail.data(),
                         edgeHead.data(),
                         edgeX.data(),
                         MyOldCutsCMP,
                         MaxNoOfCuts,
                         EpsForIntegrality,
                         &IntegerAndFeasible,
                         &MaxViolation,
                         MyCutsCMP);
  
  vector<CutReturn> cuts;
  
  if (MaxViolation < 0.1)
  {
    MyOldCutsCMP->Size = 0;
    MyCutsCMP->Size = 0;
  
    CMGR_FreeMemCMgr (&MyCutsCMP);
    CMGR_FreeMemCMgr (&MyOldCutsCMP);
  
    return cuts;
  }
  
    
  for (int i = 0; i < MyCutsCMP->Size; ++i)
  {  
    vector<int> List;
    
    for (int j = 1; j <= MyCutsCMP->CPL[i]->IntListSize; ++j)
      List.push_back(MyCutsCMP->CPL[i]->IntList[j]);
  
    // Now List contains the customer numbers defining the cut.
    // The right-hand side of the cut,
    // in the form x(S:S) <= |S| - k(S), is RHS.
    
    CutReturn cut;
    
    cut.rhs = MyCutsCMP->CPL[i]->RHS;

    for (int const el1: List)
      for (int const el2: List)
        if (el1 != el2)
          cut.add(1, el1 + d_nDepots - 1, el2 + d_nDepots - 1);
        
    cuts.push_back(cut);    
  }
  
  MyOldCutsCMP->Size = 0;
  MyCutsCMP->Size = 0;
  
  CMGR_FreeMemCMgr (&MyCutsCMP);
  CMGR_FreeMemCMgr (&MyOldCutsCMP);
  
  return cuts;
}
