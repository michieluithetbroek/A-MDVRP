#include "../main.ih"

void print_cut_overview (string filename, Data const &dat, vector<shared_ptr<Cut>> cuts_ptr)
{
  cout << "\nprinting into file " << filename << endl << endl;
  ofstream file(filename);
  
  int constexpr lcl = 12;
  
  file << setprecision(2) << fixed;
  
  file << setw(lcl) << "Instance: "  << filename << '\n'
       << setw(lcl) << "LB:       "  << g_LB << '\n'
       << setw(lcl) << "UB:       "  << g_UB << '\n'
       << setw(lcl) << "LB root:  "  << g_LBRoot << '\n'
       << setw(lcl) << "Time:     "  << g_runTime << '\n'
       << setw(lcl) << "Nodes:    "  << g_nodes << '\n'
       << setw(lcl) << "Q:        "  << dat.d_vehicleCap << '\n'
       << setw(lcl) << "l:        "  << dat.d_tourMin << '\n'
       << setw(lcl) << "u:        "  << dat.d_tourMax << '\n'
       << setw(lcl) << "n:        "  << dat.d_nCustomers << '\n'
       << setw(lcl) << "m:        "  << dat.d_nDepots    << '\n';
    
  file << "\n\n\n======= General timings ======\n\n";
  
  double total_lazySeperation = 0;
  double total_userSeperation = 0;
  
  for (auto ptr: cuts_ptr)
  {
    total_lazySeperation += ptr->time_lazy().count();
    total_userSeperation += ptr->time_user().count();
  }
  
  int constexpr lcl2 = 15;
  
  file << "           " << setw(10)   << "Total" << setw(10) << "Get LP" << setw(lcl2) << "Seperation" << endl
       << "Lazy       " << setw(10)   << gg_timer_callback_lazy.count() 
                        << setw(10)   << gg_timer_callback_lazy1.count() 
                        << setw(lcl2) << total_lazySeperation 
                        << endl
       << "User       " << setw(10)   << gg_timer_callback_user.count() 
                        << setw(10)   << gg_timer_callback_user1.count()
                        << setw(lcl2) << total_userSeperation 
                        << endl
       << "Heuristic  " << setw(10)   << gg_timer_callback_heuristic.count() 
                        << setw(10)   << " - " 
                        << setw(lcl2) << " - " << endl;
  
  file << "\n\n\n======= Overview cuts ========\n\n";   
                        
  file << "\n\n"
       << setw(lcl) << "Cut type"
       << "   L  U   || "
       << setw(10) << "time"
       << setw(10) << "#called"
       << setw(10) << "#cuts"
       << "  ||  "
       << setw(10) << "time"
       << setw(10) << "#called"
       << setw(10) << "#cuts" << endl;
       
  for (auto ptr: cuts_ptr)
  {
    file << left << setw(lcl) << ptr->name() << right
         << "   " << (ptr->lazy() ? '*' : ' ') << "  " << (ptr->user() ? '*' : ' ') << "   || "
         << setw(10) << ptr->time_lazy().count()
         << setw(10) << ptr->cnt_lazy()
         << setw(10) << ptr->nCuts_lazy()
         << "  ||  "
         << setw(10) << ptr->time_user().count()
         << setw(10) << ptr->cnt_user()
         << setw(10) << ptr->nCuts_user() << endl;
  }


  file << "\n\n\n======= Time to objective (model A) ========\n\n";
  
  file << fixed << setprecision(2);
  
  for (auto const &v: gg_timeToSol_modelA)
    file << setw(10) << v.first.count() << " " << setw(10) << v.second << '\n';
  
  file << "\n======= Time to objective (model C) ========\n\n";
  
  for (auto const &v: gg_timeToSol_modelC)
    file << setw(10) << v.first.count() << " " << setw(10) << v.second << '\n';
  
  file << "\n======= Solution =============\n";
  
  for (vector<int> const &el: g_finalSol)
  {
    for (int el1: el)
      file << el1 << " ";
    file << endl;
  }
}
