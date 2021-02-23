#include "./DK_length_min.ih"

double DK_length_min::update_phi (vector<vector<double>> const &x, 
                                 vector<int> const &seq,
                                 int n, double phi, int k) const
{
  int const i = seq[0];
  int const j = seq[n - 2];   // The previous 'last' node (k-1 in paper)
  int const b = seq[n - 1];   // The new inserted node
  
  double next_phi = phi - 1
                    - x[j][k]              // Remove old arc between j and k
                    + x[b][i]              // Add arc from new customer to first
                    + x[b][k] + x[j][b]    // Add arcs to right 
                    + x[k][b];             // Add arc to left
  
  // Make complete to the left
  for (int h = 0; h < n - 1; ++h)
    next_phi += x[b][seq[h]];
  
  return next_phi;
}