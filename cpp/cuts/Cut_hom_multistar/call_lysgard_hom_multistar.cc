#include "./Cut_hom_multistar.ih"

/*  
 * 
 */
 
CnstrMgrPointer Cut_hom_multistar::call_lysgard_hom_multistar(vector<vector<double>> const &x)
{
  vector<int> edgeTail = {{0}};
  vector<int> edgeHead = {{0}};
  vector<double> edgeX = {{0}};
    
  graphFunctions::transform_to_lysgard_graph_single_depot(x, edgeTail, edgeHead, edgeX);
      
  int constexpr dim     = 100;
  int constexpr maxCuts = 100;
  
  CnstrMgrPointer myCutsCMP;
  CnstrMgrPointer MyOldCutsCMP;
  
  CMGR_CreateCMgr (&MyOldCutsCMP, dim);
  CMGR_CreateCMgr (&myCutsCMP, dim);

  double maxViolation = 0.0;
  
  MSTARSEP_SeparateMultiStarCuts(d_nCustomers, 
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
  
  return myCutsCMP;
}