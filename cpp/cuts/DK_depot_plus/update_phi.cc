#include "./DK_depot_plus.ih"

double DK_depot_plus::update_phi (vector<vector<double>> const &x, 
                                 vector<int> const &seq,
                                 int n, double phi, int k) const
{
  int const i = seq[0];
  int const j = seq[n - 2];   // The previous 'last' node (k-1 in paper)
  int const b = seq[n - 1];   // The new inserted node
  
  double next_phi = phi - 1
                    - x[k][j]              // Remove old arc between k and j
                    + x[i][b]              // Add arc from first to new customer
                    + x[k][b] + x[b][j]    // Add arcs to left 
                    + x[b][k];             // Add arc to right
  
  // Make complete to the right
  for (int h = 0; h < n - 1; ++h)
    next_phi += x[seq[h]][b];
  
  return next_phi;
}
