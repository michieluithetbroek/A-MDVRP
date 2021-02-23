#include "modelC.ih"

void ModelC::solve(int solvingTime)
{  
  double mipGap  = 0.05;
  double maxTime = 20;
  
  if (solvingTime == 1)
    maxTime = (d_delta < (int) d_iCustomers.size() ? 300 : 999999);
  
  else if (solvingTime >= 2)
    maxTime = (d_delta < (int) d_iCustomers.size() ? 600 : 999999);
  
  if (DATA_ASYMMETRY == ASYCLASS::SANTOS)
  {
    maxTime = 17500;
    mipGap  = 0.00; 
  }
  
  d_model.set (GRB_DoubleParam_TimeLimit,     maxTime);   // g_timeLimit / 10);
  d_model.set (GRB_IntParam_PreCrush,         0);         // User callback
  
  d_model.set (GRB_IntParam_Threads,          1);         // Number of threads
  d_model.set (GRB_DoubleParam_Heuristics,    1.0);
  d_model.set (GRB_IntParam_MIPFocus,         1);         // 1 = focus on solutions
  d_model.set (GRB_DoubleParam_MIPGap,        mipGap);
  d_model.set (GRB_IntParam_OutputFlag,       0);         // 0 = no terminal output
  
  d_model.set (GRB_DoubleParam_NodefileStart, 1);      // In GB!
  d_model.set (GRB_StringParam_NodefileDir,   g_nodeFileDir);

//   d_model.set(GRB_IntParam_Method, GRB_METHOD_BARRIER);
  
  MyCallbackcompact cb(this);
  d_model.setCallback(&cb);
  
  d_model.optimize();
  
//   printRoutes();
}
