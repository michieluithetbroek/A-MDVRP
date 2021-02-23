#include "./Cut_framed_cap.ih"

/*
 * 
 */

CnstrMgrPointer Cut_framed_cap::call_lysgard_framed_cap(vector<vector<double>> const &x)
{
  vector<int> edgeTail = {{0}};
  vector<int> edgeHead = {{0}};
  vector<double> edgeX = {{0}};
  
  graphFunctions::transform_to_lysgard_graph_single_depot(x, edgeTail, edgeHead, edgeX);
      
  CnstrMgrPointer myCutsCMP;
  CnstrMgrPointer myOldCutsCMP;
  
  int constexpr dim              = 100;
  int constexpr maxNoOfTreeNodes = 20000;
  int constexpr maxNoOfCuts      = 100;
  
  CMGR_CreateCMgr(&myOldCutsCMP, dim);
  CMGR_CreateCMgr(&myCutsCMP, dim);

  double violation = 0.0;
  
  FCISEP_SeparateFCIs(d_nCustomers, 
                      d_lysgard_demand.data(), 
                      d_vehicleCap,
                      edgeTail.size() - 1,
                      edgeTail.data(),
                      edgeHead.data(),
                      edgeX.data(),
                      myOldCutsCMP,
                      maxNoOfTreeNodes,
                      maxNoOfCuts,                     
                      &violation,
                      myCutsCMP
                     );
  
  myOldCutsCMP->Size = 0;
  
  CMGR_FreeMemCMgr (&myOldCutsCMP);
    
  return myCutsCMP;
}
