#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <utility>

/*
 * This struct contains all data of a single output file
 * The constructor of this struct should be the only function
 * that reads the output files.
 */

struct ResultSingleFile
{
  bool fileFound = false;
  bool optimal   = false;
  
  std::string fileName;
  
  double LB     = -1;
  double UB     = -1;
  double LBroot = -1;
  double time   = -1;
  int    nodes  = -1;
  
  double gap    = -1;
  
  // Time spend in the call backs
  double timeLazyTotal = -1;
  double timeLazyGetLP = -1;
  double timeLazySeper = -1;
  double timeUserTotal = -1;
  double timeUserGetLP = -1;
  double timeUserSeper = -1;
  double timeHeurTotal = -1;
  
  std::vector<std::string> cut_name;
  std::vector<int> nCuts_lazy;
  std::vector<int> nCuts_user;
  
  std::vector<std::pair<double, int>> timeToSol_modelA;
  std::vector<std::pair<double, int>> timeToSol_modelC;
  
  ResultSingleFile() = delete;
  
  
  
  ResultSingleFile (std::string const &fileName_in)
  :
    fileName         (fileName_in),
    cut_name         (17),
    nCuts_lazy       (17),
    nCuts_user       (17),
    timeToSol_modelA (),
    timeToSol_modelC ()
  {
    std::ifstream file(fileName);  

    if (not file.is_open())
    {
      std::cout << "File not found: " << fileName << std::endl;
      
      return;
    }
    
    fileFound = true;
    
    std::string dummy;
    std::getline(file, dummy);
    
    file >> dummy >> LB 
         >> dummy >> UB
         >> dummy >> dummy >> LBroot
         >> dummy >> time
         >> dummy >> nodes;
    
    if (time > 18000)
      time = 18000;
         
    if (UB > 0 and UB - LB < 1)
      optimal = true;
    
    if (UB > 0)
      gap = 100 * (UB - LB) / LB;
    
    if (optimal)
    {
      LB = UB;
      gap = 0;
    }
    
    
    skipLines(file, 12);
    
    file >> dummy >> timeLazyTotal >> timeLazyGetLP >> timeLazySeper
         >> dummy >> timeUserTotal >> timeUserGetLP >> timeUserSeper
         >> dummy >> timeHeurTotal >> dummy >> dummy;
    
         
         
    // ------------------------------
    // --- Read number of cuts    ---
    // ------------------------------ 
         
    skipLines(file, 9);
    
    for (int idx = 0; idx < 17; ++idx)
    {
      file >> cut_name[idx];
      
      while (file >> dummy)
        if (dummy == std::string("||"))
          break;
      
      file >> dummy >> dummy >> nCuts_lazy[idx]
           >> dummy >> dummy >> dummy >> nCuts_user[idx];
    }
         

    // ------------------------------
    // --- Timing (model A)       ---
    // ------------------------------ 
    
    skipLines(file, 6);
    
    while (file >> dummy)
    {
      if (dummy == std::string("======="))
        break;
      
      std::string dummy2;
      
      file >> dummy2;
      
      timeToSol_modelA.emplace_back(std::stod(dummy), std::stoi(dummy2));
    }
   
   
    // ------------------------------
    // --- Timing (model C)       ---
    // ------------------------------ 
    
    skipLines(file, 2);
    
    while (file >> dummy)
    {
      if (dummy == std::string("======="))
        break;
      
      std::string dummy2;
      
      file >> dummy2;
      
      timeToSol_modelC.emplace_back(std::stod(dummy), std::stoi(dummy2));
    }    
    
    
    // ------------------------------
    // --- Some additional checks ---
    // ------------------------------     
         
    if (time > 30500)
      throw std::string("Too long time interval: " + to_string(time) + " (resultSingleFile.h)\n" + fileName + "\n\n");
    
    if (LB > UB and UB != 0)
      throw std::string("LB > UB (resultSingleFile.h)\n" + fileName + "\n\n");
    
//     if (UB == 0)
//       std::cout << "UB == 0 (resultSingleFile.h)\n" << fileName << endl;
    
  //   if (LB != UB and UB - LB < 1 and UB != 0)
  //     throw string("Gap smaller than 1 but not equal to 1 (resultSingleFile.h)\n" + fileName + "\n\n");
  };
  
  
  
  /*
   * Print the datamembers of this class
   * Just used for debugging
   */
  
  void printData() const
  {
    std::cout << "File         " << fileName << '\n'
              << "LB           " << LB       << '\n'
              << "UB           " << UB       << '\n'
              << "LB root      " << LBroot   << '\n'
              << "Time         " << time     << '\n'
              << "Nodes        " << nodes    << '\n'
          
              << "\n======= General timings ======\n\n"
          
              << "Lazy       " << setw(8) << timeLazyTotal
                               << setw(8) << timeLazyGetLP
                               << setw(8) << timeLazySeper << '\n'
              << "User       " << setw(8) << timeUserTotal
                               << setw(8) << timeUserGetLP
                               << setw(8) << timeUserSeper << '\n'
              << "Heuristic  " << setw(8) << timeHeurTotal << '\n'
          
              << "\n======= Overview cuts ========\n\n";
          
    for (size_t idx = 0; idx < size(cut_name); ++idx)
      cout << setw(13) << cut_name[idx]
            << setw(8) << nCuts_lazy[idx] 
            << setw(8) << nCuts_user[idx] << endl;
                
    cout << "\n======= Timings (model A) ========\n\n";
          
    for (auto const &v: timeToSol_modelA)
      cout << setw(10) << v.first
           << setw(10) << v.second << endl; 
    
    cout << "\n======= Timings (model C) ========\n\n";
          
    for (auto const &v: timeToSol_modelC)
      cout << setw(10) << v.first
           << setw(10) << v.second << endl;  
  }
};



