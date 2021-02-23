#include "graphFunctions.ih"


/* 
 * Build a graph that can be used by the Lysgard library
 * 
 * TODO return a tuple that can be unpacked
 */

void graphFunctions::transform_to_lysgard_graph_single_depot(vector<vector<double>> const &x, 
                                                             vector<int> &edgeTail,
                                                             vector<int> &edgeHead, 
                                                             vector<double> &edgeX)
{
  if (edgeTail.empty() or edgeHead.empty() or edgeX.empty())
    throw string("graphFunctions::transform_to_lysgard_graph_single_depot (error A)");
  
  // add customer edges
  for (int const i: d_iCustomers)
  {
    int const i_idx = i - d_nDepots + 1;
    
    for (int const j: d_iCustomers)
    {
      if (i >= j)
        continue;
      
      int const j_idx = j - d_nDepots + 1;
      
      if (x[i][j] + x[j][i] > d_eps)
      {
        if (x[i][j] + x[j][i] > 1.0 + d_eps)
        {
          cout << endl
               << "i = " << i << endl
               << "j = " << j << endl
               << "x[i][j] = " << x[i][j] << endl
               << "x[j][i] = " << x[j][i] << endl
               << "eps     = " << d_eps << endl;

          throw string("graphFunctions::transform_to_lysgard_graph_single_depot (error B)");
        }
        
        edgeTail.push_back(i_idx);
        edgeHead.push_back(j_idx);
        
        edgeX.push_back(x[i][j] + x[j][i]);
      }
    }
  }
//   cout << "Adding depot edges"<< endl;
  // add depot edges
  for (int const j: d_iCustomers)
  {
    double sum = 0;
    
    for (int const d: d_iDepots)
    {
      sum += x[d][j] + x[j][d];
     
//       if (x[j][d] > 0.01)
//        cout << j << "-" << d << " " <<  x[j][d] << endl;
//       if (x[d][j] > 0.01)
//        cout << d << "-" << j << " " <<  x[d][j] << endl;
     
    }
//     if (sum > 2.01)
//     {
//       cout << "error transform_to_lysgard_graph_single_depot " << endl;
//       throw string ("grpahFunctions::transform_to_lysgard_graph_single_depot (error C)\n");
//     }
    
    if (sum > d_eps)
    {
      edgeTail.push_back(d_nCustomers + 1); // + 1 extra is it is the depot
      edgeHead.push_back(j - d_nDepots + 1);
      edgeX.push_back(sum);
    }
  }
//       cout << endl << endl;

}
