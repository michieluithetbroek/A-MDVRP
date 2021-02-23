#pragma once

#include <string>
#include <array>
#include <vector>

#include "./../helpers/IO_helpers.h"
#include "./resultSingleFile.h"

/*
 * This reads all instances of a specific problem class (e.g., A-MDTSP-I)
 * T
 */

struct MergedResultSetting
{
  // The actual settings
  int n1 = -5;
  int n2 = -5;
  int n3 = -5;
  
  // The performance statistics
  int nInstances  = 0;   // How many instances do we have
  int nNotFound   = 0;   // How many files are missing
  int nSolved     = 0;   // How many instances are solved to optimality
  int nNoSol      = 0;   // Number of instances not solved
  int nFeas       = 0;   // Number of instances with a feasible solution
  
  int nGap1       = 0;   // How many instances have an optimality gap <1%
  int nGap2       = 0;
  int nGap5       = 0;
  int nGap10      = 0;
  int nGap25      = 0;
  
  int nStopped    = 0;   // Number of instances that stopped due to memory
  
  double avgLB    = 0;
  double avgRoot  = 0;
  double avgTime  = 0;
  double avgNodes = 0;
  
  double avgTimeLazy = 0;
  double avgTimeUser = 0;
  double avgTimeHeur = 0;
  
  MergedResultSetting() = delete;
  
  MergedResultSetting (std::array<int, 3> const &s, 
                       std::vector<vector<int>> const &characs,
                       std::string const alg
                      )
  {
    // This is the path for the old results (before the revision)
    // We changed the name such that it includes more settings
    
//     std::string const folder("./../analysis/final/tuning/" 
//                              + getInstanceName() 
//                              + "/" + alg + "/" 
//                              + to_string(s[0]) + "_" 
//                              + to_string(s[1]) + "_" 
//                              + to_string(s[2]) + "/n");
  
    std::string const folder("./../analysis_new/tuning/" 
                                + getInstanceName() 
                                + "/" + alg + "/" 
                                + to_string(s[0]) + "_" 
                                + to_string(s[1]) + "_" 
                                + to_string(s[2]) + "/n");
    
    n1 = s[0];
    n2 = s[1]; 
    n3 = s[2];
    
    int constexpr nThreads  = 5;
    int constexpr sleepTime = 60;
    int constexpr repIdx    = 1;
    
    for (auto const el: characs)
    {      
      for (int rep = 0; rep != 3; ++rep)
      {
        ++nInstances;
        
        std::string const filename = folder 
                                     + std::to_string(el[1]) 
                                     + "m" + std::to_string(el[0]) 
                                     + "_" + std::to_string(rep)
                                     + "_nThreads-" + to_string(nThreads)
                                     + "_sleep-"    + to_string(sleepTime)
                                     + "_repIdx-"   + to_string(repIdx);
        
                                     
        // Read in solution file
        ResultSingleFile res(filename);
        
        if (not res.fileFound)
        {
          ++nNotFound;
          
          continue;
        }
        
        if (not res.optimal and res.time < 17900)
          ++nStopped;

        if (not res.optimal)
          res.time = 18000;
        
        
        avgLB    += res.LB;
        avgRoot  += res.LBroot;
        avgTime  += res.time;
        avgNodes += res.nodes;
        
        avgTimeLazy += res.timeLazyTotal;
        avgTimeUser += res.timeUserTotal;
        avgTimeHeur += res.timeHeurTotal;
        
        
        if (res.UB == 0)
        {
          ++nNoSol;
          
          continue;
        }
        
        ++nFeas;
        
        if (res.optimal)
          ++nSolved;
        
        if (res.gap <= 1)
          ++nGap1;
        
        if (res.gap <= 2)
          ++nGap2;
        
        if (res.gap <= 5)
          ++nGap5;
        
        if (res.gap <= 10)
          ++nGap10;
        
        if (res.gap <= 25)
          ++nGap25;
      }
    }
    
    double const nFound = nInstances - nNotFound;
    
    avgLB    /= nFound;
    avgRoot  /= nFound;
    avgTime  /= nFound;
    avgNodes /= nFound;
    
    avgTimeLazy /= nFound;
    avgTimeUser /= nFound;
    avgTimeHeur /= nFound;
  };
};
