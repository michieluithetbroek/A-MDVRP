#include "../main.ih"

/*
 * This sets the globals to the corresponding type
 * It returns tuple(nDepots, nCustomers)
 * 
 * TODO do we really need this?
 */

tuple<size_t, size_t> hash_and_set_globals(size_t const instType, 
                                           size_t const idx_inst)
{
  if (instType < 0 or instType >= 13)
    throw string("Unknown instance type (run_and_hash_and_set_globals.cc)");
  
  set_global_enums(instType);
  auto const characs = get_characs(instType);
  
  if (idx_inst >= get_nInstances())
    throw string ("Wrong instance index (hash_and_set_globals)");
  
  cout << " We will run instances: " << instType << " - " << idx_inst << endl;

  return make_tuple(characs[idx_inst][0], characs[idx_inst][1]);
}



/*
 * 
 * 
 */



void run_single_instance (Data const &dat, string const fileName, int cutSetting)
{
  // TODO this should be processed by the make_cut_vector function
  vector<shared_ptr<Cut>> cuts;
  
  if (cutSetting == 0)
    cuts = make_cut_vector_0(dat);
  
  else
    cuts = make_cut_vector_1(dat);
  
  thread t1(thread_modelA, dat, cuts);
  
  if (g_useGurobi)
  {
    thread t2(thread_modelC, dat);
    t2.join(); 
  }
  
  t1.join();
  
  print_cut_overview (fileName, dat, cuts);
}

/*
 * Runs our own instances, it runs all three replications.
 * 
 */


void run_single_instance_own (int instType, int idx_inst, 
                              string folder, int cutSetting)
{
  auto const el = hash_and_set_globals(instType, idx_inst);
  
  int const nDepots    = get<0>(el);
  int const nCustomers = get<1>(el);
  
  // Repeat the same instance setting three times
  // that is, same number of customers and depots

  for (int rep = 0; rep != 3; ++rep)
  {
    // Repeat the same instance 
    // to cope with the volatility in run time

    for (int repIdx = 0; repIdx != 3; ++repIdx)
    {
      string const filename = folder 
                             + to_string(g_cutPasses)    + "_" 
                             + to_string(g_userSettingA) + "_" 
                             + to_string(g_userSettingB) + "/n"

                             + to_string(nCustomers)     + "m" 
                             + to_string(nDepots)        + "_" 
                             + to_string(rep)
                             + "_nThreads-"
                             + to_string(g_nThreads)
                             + "_sleep-"
                             + to_string(g_sleepTime) 
                             + "_repIdx-"
                             + to_string(repIdx);
    
      Data dat(P_TYPE, DATA_ASYMMETRY, rep, nCustomers, nDepots);
    
      run_single_instance(dat, filename, cutSetting);
    }
  }
}
