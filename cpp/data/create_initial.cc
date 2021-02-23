#include "data.ih"

/* 
 * Quick 'ALNS' to create an initial solution
 * Currently not used by our algorithm
 * This should of course not be part of the Data struct
 * but we were to lazy to create a new class for something
 * that would not be part of the final algorithm.
 */  

vector<vector<size_t>> create_emptySol(vector<size_t> const &iDepots)
{
  vector<vector<size_t>> curr_sol;
  curr_sol.reserve(iDepots.size());

  for (size_t idx: iDepots)
    curr_sol.push_back({idx, idx});
  
  return curr_sol;
}



double get_costs(vector<vector<size_t>> const &routes, 
                 vector<vector<double>> const &d_cost)
{
  double total_cost = 0;
  
  for (auto const &route: routes)
    for (size_t idx = 0; idx < route.size() - 1; ++idx)
      total_cost += d_cost[route[idx]][route[idx + 1]];
      
  return total_cost;
}



pair<size_t, size_t> get_best_loc (vector<vector<size_t>> const &curr_sol, 
                                   vector<vector<double>> const &d_cost,
                                   size_t const idx_cust)
{
  double best_cost      = numeric_limits<double>::max();
  size_t best_idx_route = -1;
  size_t best_idx_loc   = -1;
  
  for (size_t idx_route = 0; idx_route < curr_sol.size(); ++idx_route)
  {
    vector<size_t> const &route = curr_sol[idx_route];
    
    for (size_t idx_loc = 1; idx_loc < route.size(); ++idx_loc)
    {
      size_t const idx_prev = route[idx_loc - 1];
      size_t const idx_next = route[idx_loc];
      
      double const cost = d_cost[idx_prev][idx_cust]
                          + d_cost[idx_cust][idx_next]
                          - d_cost[idx_prev][idx_next];
    
      if (cost < best_cost)
      {
        best_cost      = cost;
        best_idx_route = idx_route;
        best_idx_loc   = idx_loc;
      }
    }
  }
  
  return make_pair(best_idx_route, best_idx_loc);
}




vector<vector<size_t>> insert_into_sol (vector<vector<size_t>> const &curr_sol,
                                        vector<vector<double>> const &cost,
                                        vector<size_t> const &iCustomers)
{
  vector<vector<size_t>> new_sol = curr_sol;
  
  for (size_t idx_cust: iCustomers)
  {
    auto const el = get_best_loc(new_sol, cost, idx_cust);
    size_t idx_route = el.first;
    size_t idx_loc = el.second;

    // insert the customer
    vector<size_t> &route = new_sol[idx_route];
    route.insert(begin(route) + idx_loc, idx_cust);
  }
  
  return new_sol;
}


void improve_solution (vector<vector<size_t>> curr_sol,
                      vector<vector<double>> const &cost,
                      size_t n_improvements,
                      mt19937 &rng,
                      bool print)
{
  size_t const nDepots = curr_sol.size();
  
  std::uniform_int_distribution<int> get_random_route(0, nDepots - 1);
  
  // remove single customer
  
  
  double best_cost = get_costs(curr_sol, cost);
  
  for (size_t idx = 0; idx < n_improvements; ++idx)
  {
    int const idx_random_route = get_random_route(rng);
    vector<size_t> &route      = curr_sol[idx_random_route];

    // Skip empty routes
    if (route.size() <= 2)
      continue;
    
    std::uniform_int_distribution<int> get_random_cust(1, route.size() - 2);
    
    // remove random customer
    size_t const pos_random_cust = get_random_cust(rng);
    size_t const idx_random_cust = route[pos_random_cust];
    
    route.erase(begin(route) + pos_random_cust);
    
    curr_sol = insert_into_sol(curr_sol, cost, {idx_random_cust});

    double const new_cost = get_costs(curr_sol, cost);
    
    if (new_cost < best_cost)
    {
      best_cost = new_cost;
      
      if (print)
        cout << "improved initial: " << best_cost << "  (" << idx << ")" << endl;
    }
  }
}



void Data::create_initial()
{
  size_t constexpr n_initials = 20000;
       
  double cost_best_sol = numeric_limits<double>::max();     
  vector<vector<size_t>> best_sol;
  
  vector<size_t> tmp_iCustomers(d_iCustomers);
  
  std::random_device rd;
  std::mt19937 rng(rd());
  
  
  
  // ----------------------------------
  // --- Create n initial solutions ---
  // ----------------------------------
  
  for (size_t idx_try = 0; idx_try < n_initials; ++idx_try)
  {
    shuffle(begin(tmp_iCustomers), end(tmp_iCustomers), rng);
    
    auto curr_sol = insert_into_sol (create_emptySol(d_iDepots), d_cost, tmp_iCustomers);

    improve_solution (curr_sol, d_cost, 50, rng, false);
  
    double const total_cost = get_costs(curr_sol, d_cost);
      
    if (total_cost < cost_best_sol)
    {
      cost_best_sol = total_cost;
      best_sol = curr_sol;
      
      cout << "new initial: " << setw(8) << cost_best_sol << "  (" << idx_try << ")" << endl;
    }
  }
  
  cout << endl << cost_best_sol << endl << endl;

  improve_solution (best_sol, d_cost, 50000, rng, true);
  
  
  for (auto const &v: best_sol)
  {
    for (auto i: v)
      cout << i << " ";
    cout << endl;
  }
  
  throw string("Data::create_initial.cc");
}


