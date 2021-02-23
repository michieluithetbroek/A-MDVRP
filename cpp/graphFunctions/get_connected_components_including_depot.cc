#include "./graphFunctions.ih"

void graphFunctions::get_connected_components_including_depot(vector<vector<double>> const &x,
                                                              int *ncomp, 
                                                              int **compscount, 
                                                              int **comps)
{
  vector<int> elist;
  vector<double> xlist;
  
  // count number of edges in auxiliary graph
  for (int const i: d_iNodes)
  {
    for (int const j: d_iNodes)
    {
      if (x[i][j] > d_eps) 
      {
        elist.push_back(i);
        elist.push_back(j);
        xlist.push_back(x[i][j]);
      }
    }
  }
  
  CCcut_connect_components(d_nNodes, xlist.size(), elist.data(), 
                           xlist.data(), ncomp, compscount, comps);
}