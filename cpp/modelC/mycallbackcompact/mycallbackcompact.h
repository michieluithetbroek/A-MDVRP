#pragma once

#include "gurobi_c++.h"
#include "./../modelC.h"

#include <vector>

class MyCallbackcompact: public GRBCallback
{
  public:
    ModelC *d_model;
    
    MyCallbackcompact(ModelC *model);
   
  private:  
    void callback_lazy();
    void callback_user();
  
  protected:
    void callback();
};
