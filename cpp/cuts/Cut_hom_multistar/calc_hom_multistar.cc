#include "./Cut_hom_multistar.ih"

/*
 * TODO Why not returning the lhs as value?
 */ 

CutReturn Cut_hom_multistar::calc_hom_multistar(vector<int> const &Nlist,
                                                vector<int> const &Tlist,
                                                vector<int> const &Clist, 
                                                int A,
                                                int B,
                                                vector<vector<double>> const &x, 
                                                double &lhs)
{
  CutReturn cut;
  
  vector<int> v_N;
  vector<int> v_C;
  vector<int> v_T;
  
  for (size_t i = 1; i != Nlist.size(); ++i)
    if (Nlist[i] != 0)
      v_N.push_back(Nlist[i] + d_nDepots - 1);
 
  for (size_t i = 1; i != Tlist.size(); ++i)
    if (Tlist[i] != 0)
      v_T.push_back(Tlist[i] + d_nDepots - 1);
  
  for (size_t i = 1; i != Clist.size(); ++i)
    if (Clist[i] != 0)
      v_C.push_back(Clist[i] + d_nDepots - 1);
  
    
  for (int const n: v_N)
  {
    for (int const n1: d_iNodes)
    {      
      if (n == n1)
        continue;
      
      if (find(cbegin(v_N), cend(v_N), n1) != cend(v_N))
        continue;
      
      cut.add(-B, n, n1);
      cut.add(-B, n1, n);
      
      lhs += B * x[n][n1] + B * x[n1][n];  
    }
  }
  
//   cout << expr << endl << endl;
  
  for (int const t: v_T)
  {
    for (int const c: v_C)
    {
      if (t == c)
        continue;
      
      cut.add(A, t, c);
      
      lhs -= A * x[t][c];
      
      if (find(cbegin(v_C), cend(v_C), t) != cend(v_C) 
        and find(cbegin(v_T), cend(v_T), c) != cend(v_T))
        continue;
      
      cut.add(A, c, t);
      
      lhs -= A * x[c][t];
    }
  }
  

//   cout << "HOMO MULTISTAR INEQUALITY : " << endl;
//   cout << "N: ";
//   for (int i: v_N)
//     cout << i << " ";
//   cout << endl;
//   
//   cout << "T: ";
//   for (int i: v_T)
//     cout << i << " ";
//   cout << endl;
//   
//   cout << "C: ";
//   for (int i: v_C)
//     cout << i << " ";
//   cout << endl;cout << endl;
//   cout << expr;
//   cout << "LEFT HAND SIDE: " << lhs << endl;
//   cout << expr;

  return cut;
}