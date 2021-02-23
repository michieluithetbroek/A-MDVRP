#include "main.ih"
#include <thread>


/* ======================================
 * ======================================
 * =====================================
 * Final run settings: Based on first argument to run paper results.
 * 
 * argv[1] = 1 
 *      -> Create and run the MDATSP instances of our own benchmark
 *      argv[2]: A = class A
 *      argv[2]: B = class B
 *      argv[2]: C = class C-CC
 *      argv[2]: D = class C-R
 *      argv[2]: E = class C-RC 
 * 
 * 
 *  
 * ======================================= */


/* --------------------------------------------------------
 * 
 * [1] = 0: Run x_ij formulation
 *     [2]: nDepots
 *     [3]: nCustomers
 *     [4]: Instance
 *     [5..6]: if argument = cap -> include cap sep
 *             if argument = depot -> include depot sep
 *             if argument = seq  -> depot sep only if cap_sep did not find anything
 *     both cap and depot could be used, in any order
 * 
 * [1] = 1: Run x_ijk formulation 
 *     [2]: nDepots
 *     [3]: nCustomers
 *     [4]: Instance
 * 
 * [1] = 9: generate instances 
 *     [2]: nDepots
 *     [3]: nCustomers
 * 
 * 
 * --------------------------------------------------------
 */

int main(int argc, char **argv)
try
{
  // ----------------------------
  // --- Read input arguments ---
  // ----------------------------
  
  string const whichRun(argv[1]);
  
  
  
  
  int instanceType = -1;
  int idx_instance = -1;
  
  if (argc == 7)
  {
    instanceType = stoi(argv[2]);
    idx_instance = stoi(argv[3]);
  }
  
  
  
  // ----------------------------
  // --- Run the program      ---
  // ----------------------------
  
  if (whichRun == string("root"))
  {
    if (argc != 5)
      throw string("Root expects three additional parameters\n[int cutPass, bool withCplexCuts, bool withGurobi] (main.cc)");
    
    int  cutPass       = stoi(argv[2]);
    bool withCplexCuts = stoi(argv[3]);
    bool withGurobi    = stoi(argv[4]);
    
    run_roots(cutPass, withCplexCuts, withGurobi);
  }
  
  else if (whichRun == string("base"))
  {
    int cutPass = stoi(argv[4]);
    int cutA    = stoi(argv[5]);
    int cutB    = stoi(argv[6]);
    
    run_base (instanceType, idx_instance, cutPass, cutA, cutB);
  }
  
  else if (whichRun == string("base_withCuts"))
  {
    int cutPass = stoi(argv[4]);
    int cutA    = stoi(argv[5]);
    int cutB    = stoi(argv[6]);
    
    run_base_plusCuts(instanceType, idx_instance, cutPass, cutA, cutB); 
  }
  
  else if (whichRun == string("base_withGurobi"))
  {
    int cutPass = stoi(argv[4]);
    int cutA    = stoi(argv[5]);
    int cutB    = stoi(argv[6]);
    
    run_base_plusGurobi (instanceType, idx_instance, cutPass, cutA, cutB);
  }
  
  else if (whichRun == string("base_withBoth"))
  {
    int cutPass = stoi(argv[4]);
    int cutA    = stoi(argv[5]);
    int cutB    = stoi(argv[6]);
    
    run_base_plusBoth (instanceType, idx_instance, cutPass, cutA, cutB);
  }
  
  else if (whichRun == string("run-santos"))
  {
    int const idx_instance = stoi(argv[2]);
    int const determinstic = stoi(argv[3]);
    int const idx_rep      = stoi(argv[4]);
    
    run_benchmark_santos (idx_instance, determinstic, idx_rep);
  }
  
  
  else if (whichRun == string("process-allSolTime"))
    process_allSolTime();
  
  else if (whichRun == string("process-allSolTime"))
    process_allSolTime();
  
  else if (whichRun == string("process-compareBoth"))
    process_compareBoth();
  
  else if (whichRun == string("process-cuts"))
    process_output_files_for_cuts();
  
  else if (whichRun == string("process-roots"))
    process_all_roots();
  
  else if (whichRun == string("process"))
    process_output_files(stoi(argv[2]));

  else if (whichRun == string("process-allSettings-short"))
    process_allSettings_short();
  
  else if (whichRun == string("process-allSettings-long"))
    process_allSettings_long();
  
  
  
  
  // below for creating instances
  
  else if (stoi(argv[1]) == 1)
  {
    create_MDATSP_benchmarkA();
    create_MDATSP_benchmarkB();
    create_MDATSP_benchmarkC_RC();
  
    create_MDAmTSP_benchmarkA();
    create_MDAmTSP_benchmarkB();
    create_MDAmTSP_benchmarkC_RC();
  
    create_MDACVRP_benchmarkA();
    create_MDACVRP_benchmarkB();
    create_MDACVRP_benchmarkC_RC();
  
    create_ACLRP_benchmarkA();
    create_ACLRP_benchmarkB();
    create_ACLRP_benchmarkC_RC();
  }
  
  else
    throw string("Unknown argument (main.cc)");

}

catch (string const &error)
{
  cout << "\n\n--------------------------\n\n" << error << endl << endl;
}

catch (IloException const &error)
{
  cout << "\n\n--------------------------\n\n" << error << endl << endl;
  cout << error << endl;
}
