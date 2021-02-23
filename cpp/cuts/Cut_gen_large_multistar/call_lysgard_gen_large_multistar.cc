#include "./Cut_gen_large_multistar.ih"

vector<int> Cut_gen_large_multistar::call_lysgard_gen_large_multistar(vector<vector<double>> const &x)
{
  vector<int> edgeTail = {{0}};
  vector<int> edgeHead = {{0}};
  vector<double> edgeX = {{0}};
  
  graphFunctions::transform_to_lysgard_graph_single_depot(x, edgeTail, edgeHead, edgeX);
   
  int constexpr dim = 100;
  
  CnstrMgrPointer myCutsCMP;
  CnstrMgrPointer MyOldCutsCMP;
  
  CMGR_CreateCMgr (&MyOldCutsCMP, dim);
  CMGR_CreateCMgr (&myCutsCMP, dim);

  double violation = 0.0;
  int custListSize = 0;
  vector<int> custList(d_nCustomers + 1, 0);

  GLMSEP_SeparateGLM(d_nCustomers, 
                     d_lysgard_demand.data(), 
                     d_vehicleCap,
                     edgeTail.size() - 1,
                     edgeTail.data(),
                     edgeHead.data(),
                     edgeX.data(),
                     custList.data(),
                     &custListSize,  
                     &violation);
  
  if (custListSize == 0)
  {
    MyOldCutsCMP->Size = 0;
    myCutsCMP->Size = 0;
    
    CMGR_FreeMemCMgr (&myCutsCMP);
    CMGR_FreeMemCMgr (&MyOldCutsCMP);
    
    return vector<int>();
  }
  
//   cout << "violoation: " << violation << endl;
//   cout << "custListSize: " << custListSize << endl;
  
  vector<int> v_N;
  
  for (int idx = 1; idx <= custListSize; ++idx)
    v_N.push_back(custList[idx]);
  
  MyOldCutsCMP->Size = 0;
  myCutsCMP->Size = 0;

  CMGR_FreeMemCMgr (&myCutsCMP);
  CMGR_FreeMemCMgr (&MyOldCutsCMP);
  
  return v_N;
}