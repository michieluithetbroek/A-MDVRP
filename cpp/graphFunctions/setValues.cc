#include "./graphFunctions.ih"

void graphFunctions::setValues(
                  int nDepots,
                  int nCustomers,
                  int nNodes,
                  vector<size_t> const &iDepots,
                  vector<size_t> const &iCustomers,
                  vector<size_t> const &iNodes
                )
{
  graphFunctions::d_nDepots    = nDepots;
  graphFunctions::d_nCustomers = nCustomers;
  graphFunctions::d_nNodes     = nNodes;
//   graphFunctions::d_vehicleCap = vehicleCap;
  
  graphFunctions::d_iDepots    = iDepots;
  graphFunctions::d_iCustomers = iCustomers;
  graphFunctions::d_iNodes     = iNodes;
  
//   cout << "\n\nhello from set values!\n"
//        << graphFunctions::d_nNodes << endl
//        << graphFunctions::d_nDepots << endl
//        << graphFunctions::d_nCustomers << endl << endl;
};
  