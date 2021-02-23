#include "../main.ih"

/*
 * 
 * 
 */

void thread_modelA (Data dat, vector<shared_ptr<Cut>> const &cuts)
{
  try 
  {
    ModelA A(dat, cuts);
    A.solve();
  }
  
  catch (IloException const &error)
  {
    cout << "\n\n--------------------------\n\n" << error << endl << endl;
  }
}
