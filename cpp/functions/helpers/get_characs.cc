#include "./../../main.ih"


/*
 * The settings (i.e., nDepots, nCustomers) that the instances 
 * have in our own benchmark.
 */

vector<vector<int>> get_characs (int instanceType)
{
  vector<vector<int>> characs;
  
  if (P_TYPE == PROBLEMTYPE::MDATSP)
  {
    characs = {
              {20, 200},
              {30, 200},
              {40, 200},
              {20, 300},
              {30, 300},
              {40, 300},
              {30, 350},
              {40, 350},
              {50, 350},
              {30, 375},
              {40, 375},
              {50, 375},
              {30, 400},
              {40, 400},
              {50, 400},
               }; // 15 instances, so index 0- 14
              
    if (3 * characs.size() != get_nInstances())
      throw string("get_nInstances.cc is incorrect (get_characs.cc - error 1)");
  }
  
  else if (P_TYPE == PROBLEMTYPE::MDAMTSP)
  {
    characs = {
              {5, 50},
              {5, 60},
              {5, 70},
              {5, 75},
              {5, 80},
              {5, 85},
              {5, 90},
              {5, 95},
              {5, 100},
              {10, 50},
              {10, 60},
              {10, 70},
              {10, 75},
              {10, 80},
              {10, 85},
              {10, 90},
              {10, 95},
              {10, 100},
              {20, 80},
              {20, 85},
              {20, 90},
              {20, 95},
              {20, 100}
              }; //23 instances, so index 1-22
              
    if (3 * characs.size() != get_nInstances())
      throw string("get_nInstances.cc is incorrect (get_characs.cc - error 2)");
  }
  
  else
  {
    characs = {
              {5, 40},
              {5, 45},
              {5, 50},
              {5, 55},
              {5, 60},
              {5, 65},
              {5, 70},
              {5, 75},
              {10, 40},
              {10, 45},
              {10, 50},
              {10, 55},
              {10, 60},
              {10, 65},
              {10, 70},
              {10, 75},
              {10, 80},
              {10, 85},
              {20, 75},
              {20, 80},
              {20, 85}
              }; // 21 instances, so index 1 - 20
              
    if (3 * characs.size() != get_nInstances())
      throw string("get_nInstances.cc is incorrect (get_characs.cc - error 3)");
  }
  
  return characs;
}
