#include "./Cut_comb.ih"

/*
 * 
 */

CnstrMgrPointer Cut_comb::call_lysgard_strengthened_combs(vector<vector<double>> const &x)
{
  // create edge info
  vector<int> edgeTail = {{0}};
  vector<int> edgeHead = {{0}};
  vector<double> edgeX = {{0}};
    
  graphFunctions::transform_to_lysgard_graph_single_depot(x, edgeTail, edgeHead, edgeX);

  double const Qmin    = 0;   //accumulate(begin(d_demands), end(d_demands), 0) - (;
  int    const maxCuts = 10;
  
  CnstrMgrPointer myCutsCMP;
  CMGR_CreateCMgr(&myCutsCMP, maxCuts);

  double maxViolation = 0.0;
  
  COMBSEP_SeparateCombs(d_nCustomers, 
                        d_lysgard_demand.data(), 
                        d_vehicleCap,
                        Qmin,
                        edgeTail.size() - 1,
                        edgeTail.data(),
                        edgeHead.data(),
                        edgeX.data(),
                        maxCuts,  
                        &maxViolation,
                        myCutsCMP);
  
  return myCutsCMP;
}