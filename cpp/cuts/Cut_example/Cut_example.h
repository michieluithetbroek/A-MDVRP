#pragma once

#include "./../cut.h"

class Cut_example: public Cut
{

  public:
    
    Cut_example (int priority, bool lazy, bool user, 
                 bool stopIfFound, bool onlyRootNode, Data const &data)
    : 
      Cut (priority, lazy, user, stopIfFound, onlyRootNode, std::string("Cut_example"))
    {};
  
  private:

    // ----------------------------
    // --- Virtual function     ---
    // ----------------------------
    
    std::vector<CutReturn> findCuts(std::vector<std::vector<double>> const &x);
    
    
    
    // ----------------------------
    // --- Helper functions     ---
    // ----------------------------
    

};