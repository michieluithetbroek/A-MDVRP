// #include "./../modelA.ih"
// 
// void ModelA::showSolution(IloCplex const &cplex) const
// {
//   IloNumMatrix valsx(d_env, d_nNodes);
//   
//   for (int i: d_iNodes)
//   {
//     valsx[i] = IloNumArray(d_env, d_nNodes);
//     
//     for (int j: d_iNodes) 
//       valsx[i][j] = cplex.getValue(d_x[i][j]);
//   }
//   
//   cout.precision(2);
//   cout << "----------------LP RELAXATION------------------" << endl;
// 
//   cout << setw(3) << " " << " ";
//   for (int i: d_iNodes)
//     cout << setw(3) << i << " ";
//   
//   cout << endl;
//   
//   for (int i: d_iNodes)
//   {
//     cout << setw(3) << i << " ";
//     
//     for (int j: d_iNodes)
//       cout << setw(3) <<  ((valsx[i][j] < 0.00001) ? 0 : valsx[i][j]) << " ";
//     cout << endl;
//   }
//   
//   cout << endl << " depot variables " << endl;
//   
//   for (int i: d_iCustomers)
//     cout << i << ": " << cplex.getValue(d_u[i]) << endl;
//   
//   cout << "-------------------------------------" << endl;
// }
