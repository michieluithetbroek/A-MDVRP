#include "mycallbackcompact.ih"

void MyCallbackcompact::callback()
{
  try 
  {
    switch (where)
    {
      case GRB_CB_MIP:
        callback_user();
        break;
      
      case GRB_CB_MIPSOL:
        callback_lazy();
        break;
    }
    
    // Immediately stop if CPLEX has stopped
    if (g_modelSolved)
      abort();
  }
  
  catch (GRBException e) 
  {
    cout << "Error number: " << e.getErrorCode() << " ------- ";
    cout << e.getMessage() << endl;
  } 
  
  catch (string &e) 
  {
    cout << "Error during Gurobi callback\n" << e << endl;
  } 
  
  catch (...) 
  {
    cout << "Unknown error during Gurobi callback" << endl;    
  }
}
