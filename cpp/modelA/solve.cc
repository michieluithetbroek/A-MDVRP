#include "modelA.ih"

/*
 * Note the ugly catch throw construction.
 * We have to catch within the callbacks because CPLEX does not 
 * catch our own throw std::string statements. However, we also
 * have to throw again because we want CPLEX to terminate when
 * an exception is thrown.
 * 
 */


ILOINCUMBENTCALLBACK1(CALLBACK_INC, ModelA &, model)
{
  try
  {
    auto const currTime    = chrono::high_resolution_clock::now();
    dur_t const delta_time = currTime - gg_startTime_modelA;
         
    gg_timeToSol_modelA.emplace_back(delta_time, getObjValue());
  }
  
  catch (IloException e)
  {
    cout << "\n--\n-- IloException in incumbent callback: " << e << "\n--\n" << endl;
    throw;
  }
  
  catch (string e)
  {
    cout << "\n--\n-- Other exception in incumbent callback: " << e << "\n--\n" << endl;
    throw;
  }
}


ILOHEURISTICCALLBACK1(CALLBACK_HEUR, ModelA &, model)
{
  try
  {
    if (g_cutOff >= getIncumbentObjValue() or g_cutOff > 9999999)
      return;
    
    auto const start = chrono::high_resolution_clock::now();
    
//     cout << " --- Entering heuristic solution callback " << endl
//          << "     " << g_cutOff << " -- " << getIncumbentObjValue()  << endl
//          << "     " << getStatus() << endl << endl;

    IloNumArray vals    = IloNumArray(model.d_env);
    IloNumVarArray vars = IloNumVarArray(model.d_env);
    
    for (int i = 0; i != model.d_nNodes; ++i)
    {
      for (int j = 0; j != model.d_nNodes; ++j)
      {
        vals.add(g_globalSol[i][j]._a);
        vars.add(model.d_x[i][j]);
      }
    }

    setSolution(vars, vals, g_cutOff);

    vals.end();
    vars.end();

//     cout << " --- Leaving heuristic solution callback " << endl
//          << "     " << g_cutOff << " -- " << getIncumbentObjValue()  << endl
//          << "     " << getStatus() << endl << endl;
    
    gg_timer_callback_heuristic += chrono::high_resolution_clock::now() - start;
  }

  catch (IloException e)
  {
    cout << "\n--\n-- IloException in heuristic callback: " << e << "\n--\n" << endl;
    throw;
  }
  
  catch (string e)
  {
    cout << "\n--\n-- Other exception in heuristic callback: " << e << "\n--\n" << endl;
    throw;
  }
}


ILOLAZYCONSTRAINTCALLBACK1(CALLBACK_LAZY, ModelA &, model)
{
  try
  {
    auto const start = chrono::high_resolution_clock::now();
    
    g_nodes = getNnodes();

    if (g_nodes == 0)
      g_LBRoot = getBestObjValue();
    
    
    
    // -----------------------------------
    // --- Read x values (Lazy)        ---
    // -----------------------------------
    
    auto const start1 = chrono::high_resolution_clock::now();
    
    IloNumMatrix x_val2(model.d_env);
    
    for (int const i: model.d_iNodes)
    {
      IloNumArray x_tmp(model.d_env);
      getValues(x_tmp, model.d_x[i]);
      x_val2.add(x_tmp);
    }

    numMatrix x_val(model.d_nNodes, vector<double>(model.d_nNodes, 0));
    
    for (int const idx: model.d_iNodes)
      for (int const jdx: model.d_iNodes) 
        x_val[idx][jdx] = x_val2[idx][jdx];

    gg_timer_callback_lazy1 += chrono::high_resolution_clock::now() - start1;
    

    
    // -----------------------------------
    // --- Add lazy cuts               ---
    // -----------------------------------
    
    bool constexpr sequential = true;
    
    for (auto const &cut_ptr: model.d_cuts)
    {
      if (not cut_ptr->lazy())
        continue;
      
      auto const cuts = cut_ptr->getCuts(model.d_env, model.d_x, x_val, true);
      
      for (auto const &cut: cuts)
      {
//         cout << cut_ptr->name() << "      " << cut << endl;
        add(cut);
      }
      
      bool const found_cut = not cuts.empty();
      
      if (found_cut and (sequential or cut_ptr->stopIfCutFound()))
        break;
    }
    
    gg_timer_callback_lazy += chrono::high_resolution_clock::now() - start;
  }

  catch (IloException e)
  {
    cout << "\n--\n-- IloException in lazy callback: " << e << "\n--\n" << endl;
    throw;
  }
  
  catch (string e)
  {
    cout << "\n--\n-- Other exception in lazy callback: " << e << "\n--\n" << endl;
    throw;
  }
}


ILOUSERCUTCALLBACK1(CALLBACK_USER,
                    ModelA &, model
                   )
{
  try
  {
    auto const start = chrono::high_resolution_clock::now();
    
    g_nodes = getNnodes();

    if (not isAfterCutLoop())
      return;
    
    if (g_nodes > g_userSettingA and g_nodes % g_userSettingB != 0)
      return;
    
    if (g_nodes == 0)
      g_LBRoot = getBestObjValue();
    

    
    // -----------------------------------
    // --- Read x values (User)        ---
    // -----------------------------------
    
    auto const start1 = chrono::high_resolution_clock::now();

    IloNumMatrix x_val2(model.d_env);
    
    for (int const i: model.d_iNodes)
    {
      IloNumArray x_tmp(model.d_env);
      getValues(x_tmp, model.d_x[i]);
      x_val2.add(x_tmp);
    }
    
    numMatrix x_val(model.d_nNodes, vector<double>(model.d_nNodes, 0));
    
    for (int const idx: model.d_iNodes)
      for (int const jdx: model.d_iNodes) 
        x_val[idx][jdx] = x_val2[idx][jdx];

    gg_timer_callback_user1 += chrono::high_resolution_clock::now() - start1;



    // -----------------------------------
    // --- Add user cuts               ---
    // -----------------------------------
    
    bool constexpr sequential = true;
    
    for (auto const &cut_ptr: model.d_cuts)
    {
      if (not cut_ptr->user())
        continue;
    
      if (g_nodes > 0 and cut_ptr->onlyRootNode())
        continue;
      
      auto const cuts = cut_ptr->getCuts(model.d_env, model.d_x, x_val, false);
      
      for (auto const &cut: cuts)
        add(cut);
      
      bool const found_cut = not cuts.empty();
      
      if (found_cut and (sequential or cut_ptr->stopIfCutFound()))
        break;
    }

    gg_timer_callback_user += chrono::high_resolution_clock::now() - start;
  }
  
  catch (IloException e)
  {
    cout << "\n--\n-- IloException in user callback: " << e << "\n--\n" << endl;
    throw;
  }
  
  catch (string e)
  {
    cout << "\n--\n-- Other exception in lazy callback: " << e << "\n--\n" << endl;
    throw;
  }
}



void ModelA::solve()
{
  if (g_onlyRoot)
    throw string("solve_root should be used (modelA::solve.cc)");  
  
  if (g_cplexFocusLB and not g_useGurobi)
    throw string("Wrong settings are used A (modelA::solve.cc)");  
  
  
  
  IloCplex cplex(d_model);
  addOwnLazyConstraints(cplex);

  
  
  // ------------------------------------
  // --- Set CPLEX settings           ---
  // ------------------------------------
  
  cplex.setParam (IloCplex::TiLim,                          g_timeLimit);
  cplex.setParam (IloCplex::Param::Threads,                 g_nThreads);
  cplex.setParam (IloCplex::Param::WorkMem,                 g_workMem);
  cplex.setParam (IloCplex::Param::MIP::Limits::TreeMemory, g_treeMemory);
  cplex.setParam (IloCplex::EpGap,                          g_epGap); 
  cplex.setParam (IloCplex::EpAGap,                         g_epAGap); 
  cplex.setParam (IloCplex::Param::MIP::Display,            g_verbosity);
  cplex.setParam (IloCplex::CutPass,                        g_cutPasses);
  cplex.setParam (IloCplex::Param::Parallel,                g_parallelMode);
  cplex.setParam (IloCplex::NodeFileInd,                    2);
  cplex.setParam (IloCplex::WorkDir,                        g_nodeFileDir.c_str());
   


  //cplex.setParam (IloCplex::Param::RootAlgorithm, CPX_ALG_CONCURRENT);
  //cplex.setParam (IloCplex::Param::RootAlgorithm, CPX_ALG_BARRIER);
  //cplex.setParam (IloCplex::Param::MIP::Strategy::Probe,    3);  


  d_env.setNormalizer(false);  

  if (g_cplexFocusLB)
    cplex.setParam (IloCplex::Param::Emphasis::MIP , 3);
  
  /*
   * IloCplex::NodeFileInd
   *   0 No Node File
   *   1 Node File in Memory (Compressed)
   *   2 Node File on Disk
   *   3 Node File on Disk (Compressed)
   * 
   */
  

  // ------------------------------------
  // --- Enable cplex cuts            ---
  // ------------------------------------
  
  // - 1 = not, 0 = auto, 1 - 2(3) is from moderately aggressive to aggressive

  int const cutSetting = (g_cplexCuts ? 0 : -1);

  cplex.setParam (IloCplex::Param::MIP::Cuts::Cliques,      cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::Covers,       cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::Disjunctive,  cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::FlowCovers,   cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::PathCut,      cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::Gomory,       cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::GUBCovers,    cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::LocalImplied, cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::Implied,      cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::LiftProj,     cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::MIRCut,       cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::MCFCut,       cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::ZeroHalfCut,  cutSetting);  
  cplex.setParam (IloCplex::NodeLim,                        g_nMaxNodes);
  
  
  // ------------------------------------
  // --- Link callback functions      ---
  // ------------------------------------
  
  cplex.use(CALLBACK_LAZY (d_env, *this));
  cplex.use(CALLBACK_USER (d_env, *this));
  cplex.use(CALLBACK_HEUR (d_env, *this));
  cplex.use(CALLBACK_INC  (d_env, *this)); 
  
  
  // ------------------------------------
  // --- provide initial solution     ---
  // ------------------------------------
  
  /* 
   * The magic cplex parameter can be found at
   * https://www.ibm.com/support/knowledgecenter/SSSA5P_12.7.0/ilog.odms.cplex.help/refcppcplex/html/enumerations/IloCplex_MIPStartEffort.html
   * 
   */
  
  if (g_useGurobi)
  {
    cout << " -- CPLEX starts sleeping for " << g_sleepTime << " seconds" << endl;
    std::this_thread::sleep_for (std::chrono::seconds(g_sleepTime));
    cout << " -- CPLEX Continues" << endl;
    
    
    // TODO Dit kan in een losse functie: getGlobalBestSolution
    // Die kan dan een IloNumArray en IloNumVarArray terug geven
    // Dan ook gebruiken in de heuristic callback en solve_roots
    
    IloNumArray vals    = IloNumArray(d_env);
    IloNumVarArray vars = IloNumVarArray(d_env);

    for (int i = 0; i != d_nNodes; ++i)
    {
      for (int j = 0; j != d_nNodes; ++j)
      {
        int const value = g_globalSol[i][j]._a;
        
        vals.add(value);
        vars.add(d_x[i][j]);
      }
    }
    
    cplex.addMIPStart(vars, vals);
    
    vals.end();
    vars.end();
  }

  
  
  // ------------------------------------
  // --- Start CPLEX                  ---
  // ------------------------------------
 
  gg_startTime_modelA = chrono::high_resolution_clock::now();
  
  cplex.solve();
  
  dur_t const time_total = chrono::high_resolution_clock::now() - gg_startTime_modelA; 
  
  g_UB = 0;
  
  if (cplex.getStatus() != IloAlgorithm::Unknown)
    g_UB = cplex.getObjValue();

  g_LB          = cplex.getBestObjValue();  
  g_runTime     = time_total.count();
  g_nodes       = cplex.getNnodes();
  g_modelSolved = true; 
  
  printRoutes(cplex);

  check_correctness();
  
  cplex.end();
  d_model.end();
  d_env.end();
}



void ModelA::solve_root()
{
  if (not g_onlyRoot)
    throw string("ModelA::solve() should be used (modelA::solve_root.cc)"); 
  
  
  
  IloCplex cplex(d_model);
  addOwnLazyConstraints(cplex);

  cplex.setParam (IloCplex::TiLim,                          g_timeLimit);
  
  cplex.setParam (IloCplex::Param::Threads,                 g_nThreads);
  cplex.setParam (IloCplex::Param::WorkMem,                 g_workMem);
  cplex.setParam (IloCplex::Param::MIP::Limits::TreeMemory, g_treeMemory); 
  cplex.setParam (IloCplex::EpGap,                          g_epGap); 
  cplex.setParam (IloCplex::EpAGap,                         g_epAGap); 
  cplex.setParam (IloCplex::Param::MIP::Display,            g_verbosity); 
  cplex.setParam (IloCplex::Param::MIP::Limits::CutPasses,  g_cutPasses);
  cplex.setParam (IloCplex::Param::Parallel,                g_parallelMode);
  cplex.setParam (IloCplex::NodeFileInd,                    2);
  cplex.setParam (IloCplex::WorkDir,                        g_nodeFileDir.c_str());
  
  d_env.setNormalizer(false);  

  if (g_cplexFocusLB)
    cplex.setParam (IloCplex::Param::Emphasis::MIP, 3);
  

  
  // ------------------------------------
  // --- Disable cplex cuts           ---
  // ------------------------------------
  
  // - 1 = not, 0 = auto, 1 - 2(3) is from moderately aggressive to very aggressive 
  
  int const cutSetting = (g_cplexCuts ? 0 : -1);
  
  cplex.setParam (IloCplex::Param::MIP::Cuts::Cliques,      cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::Covers,       cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::Disjunctive,  cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::FlowCovers,   cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::PathCut,      cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::Gomory,       cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::GUBCovers,    cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::LocalImplied, cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::Implied,      cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::LiftProj,     cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::MIRCut,       cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::MCFCut,       cutSetting); 
  cplex.setParam (IloCplex::Param::MIP::Cuts::ZeroHalfCut,  cutSetting); 
  
  cplex.setParam (IloCplex::NodeLim,                        0);
  cplex.setParam (IloCplex::Param::Preprocessing::Presolve, 0); 

  
  
  // ------------------------------------
  // --- Link callback functions      ---
  // ------------------------------------
  
  cplex.use(CALLBACK_LAZY (d_env, *this));
  cplex.use(CALLBACK_USER (d_env, *this));
  cplex.use(CALLBACK_HEUR (d_env, *this)); 
  //cplex.use(CALLBACK_INC  (d_env, *this)); 
  
  
  // ------------------------------------
  // --- provide initial solution     ---
  // ------------------------------------
  
  /*
   * The magic cplex parameter can be found at
   * https://www.ibm.com/support/knowledgecenter/SSSA5P_12.7.0/ilog.odms.cplex.help/refcppcplex/html/enumerations/IloCplex_MIPStartEffort.html
   * 
   */
  
  if (g_useGurobi)
  {
    cout << " -- CPLEX starts sleeping for " << g_sleepTime << " seconds" << endl;
    std::this_thread::sleep_for (std::chrono::seconds(g_sleepTime));
    cout << " -- CPLEX Continues" << endl;
    
    IloNumArray vals    = IloNumArray(d_env);
    IloNumVarArray vars = IloNumVarArray(d_env);

    for (int i = 0; i != d_nNodes; ++i)
    {
      for (int j = 0; j != d_nNodes; ++j)
      {
        int const value = g_globalSol[i][j]._a;
        
        vals.add(value);
        vars.add(d_x[i][j]);
      }
    }
    
    cplex.addMIPStart(vars, vals);
    
    vals.end();
    vars.end();
  }
  
  
  
  // ------------------------------------
  // --- Start CPLEX                  ---
  // ------------------------------------
  
  gg_startTime_modelA = chrono::high_resolution_clock::now();
  
  cplex.solve();
  
  dur_t const time_total = chrono::high_resolution_clock::now() - gg_startTime_modelA;
  
  g_UB = 0;
  
  if (cplex.getStatus() != IloAlgorithm::Unknown)
    g_UB = cplex.getObjValue();
  
  g_LB          = cplex.getBestObjValue();  
  g_runTime     = time_total.count();
  g_nodes       = cplex.getNnodes();
  g_modelSolved = true;

  printRoutes(cplex);

  cplex.end();

  d_model.end();
  d_env.end();
}
