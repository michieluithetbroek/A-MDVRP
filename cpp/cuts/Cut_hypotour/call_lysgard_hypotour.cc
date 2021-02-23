#include "./Cut_hypotour.ih"

/* 
 * Hypotour  (chapter 8)
 */

CnstrMgrPointer Cut_hypotour::call_lysgard_hypotour(vector<vector<double>> const &x)
{
  vector<int> edgeTail = {{0}};
  vector<int> edgeHead = {{0}};
  vector<double> edgeX = {{0}};
  cout << "hypo --- "<< endl;
  graphFunctions::transform_to_lysgard_graph_single_depot(x, edgeTail, edgeHead, edgeX);
  
  int constexpr dim     = 10;
  int constexpr maxCuts = 10;
  CnstrMgrPointer myCutsCMP;
  CnstrMgrPointer MyOldCutsCMP;
  
  CMGR_CreateCMgr (&MyOldCutsCMP, dim);
  CMGR_CreateCMgr (&myCutsCMP, dim);
  for (int i = 1; i != edgeX.size(); ++i)
  {
    cout << edgeTail[i] << "-" << edgeHead[i] << ": " << edgeX[i] << endl;
  }

  double maxViolation = 0.0;
  
  HTOURSEP_SeparateHTours(d_nCustomers, 
                          d_lysgard_demand.data(), 
                          d_vehicleCap,
                          edgeTail.size() - 1,
                          edgeTail.data(),
                          edgeHead.data(),
                          edgeX.data(),
                          MyOldCutsCMP,
                          maxCuts,
                          &maxViolation,  
                          myCutsCMP);
  
  MyOldCutsCMP->Size = 0;
  CMGR_FreeMemCMgr (&MyOldCutsCMP);
  cout << "maxViolation: " << maxViolation << endl; 
  return myCutsCMP;
}
