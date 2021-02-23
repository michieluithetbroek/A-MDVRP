// #include "./../modelA.ih"

// [[deprecated]] void ModelG::printArcs(IloCplex const &cplex) const
// {
//   for (int i: d_iNodes)
//     for (int j: d_iNodes)
//       if (cplex.getValue(d_x[i][j]) > 0.001)
//         cout << i << " - " << j << ": " << cplex.getValue(d_x[i][j]) <<  endl;
// }

// [[deprecated]] void ModelA::printArcs(IloNumMatrix const &x) const
// {
//   for (int i: d_iNodes)
//     for (int j: d_iNodes)
//       if (x[i][j] > 0.001)
//         cout << i << " - " << j << ": " << x[i][j] <<  endl;
// }

// void ModelA::printArcs(numMatrix const &x) const
// {
//   for (int i: d_iNodes)
//     for (int j: d_iNodes)
//       if (x[i][j] > 0.001)
//         cout << i << " - " << j << ": " << x[i][j] <<  endl;
// }