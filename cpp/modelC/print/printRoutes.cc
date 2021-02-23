#include "./../modelC.ih"



void ModelC::printRoutes() const
{
  vector<vector<atomwrapper<int>>> d_x = g_globalSol;
  
  vector<bool> visited(d_nNodes, false);    
  
  // Check all outgoing arcs
  for (int i: d_iDepots)
  {
    visited[i] = true;
    
    for (int j: d_iCustomers)
    {
      if (d_x[i][j]._a == 0)
        continue;
      
      // There is a route that starts with arc (i,j)
      // Now we follow this route
      cout << '\n' << i << " - " << j;
      
      int curr = j;
      int length = 0;
      
      while (true)
      {
        visited[curr] = true;
        
        int next = 0;
        for (; next < d_nNodes; ++next)
        {
           if (d_x[curr][next]._a == 0)
            continue;
        
          
          curr = next; 
          cout << " - " << curr ;
          ++length;
          break;
        }
        
        
        
        if (find(cbegin(d_iDepots), cend(d_iDepots), curr) != cend(d_iDepots))
        {
          if (i != curr)
            cout << " ------ INVALID ROUTE ------ ";
          
          if (length > d_data.d_tourMax or length < d_data.d_tourMin)
            cout << "-------------------- \n-------------------- " << length << endl;
          
          break;
        }
        
        
      }
    }
  }
  
  cout << endl << endl;
  
  for (bool val: visited)
    if (not val)
    {
      cout << "EHHHHH INVALID SOLUTION !?!?!?!?!?!? \n\n\n";
      throw string("Not each customer are visited!\n");
    }
}
