#pragma once

#include <iosfwd>
#include <vector>
#include <string>

#include "./../global.h"

using namespace std;

struct Customer
{
  double x;
  double y;
  double w;
  
  Customer(double p_x, double p_y, int p_w)
  :
    x(p_x),
    y(p_y),
    w(p_w)
    {}
};

struct Depot
{
  double x;
  double y;
  
  Depot(double p_x, double p_y)
  :
    x(p_x),
    y(p_y)
  {}
};

struct Node
{
  double x;
  double y;
  int w;
  
  Node(double p_x, double p_y, int p_w)
  :
    x(p_x),
    y(p_y),
    w(p_w)
    {}  
};

struct Data
{
  int d_instance;  // TODO used?
  
  int d_nDepots;
  int d_nCustomers;
  int d_nNodes;
  
  int d_vehicleCap;
  int d_tourMin;
  int d_tourMax;
  
  PROBLEMTYPE d_inst; // TODO used? We also have this globally
  ASYCLASS    d_asy;  // TODO used? 
  
  vector<int> d_demands;
  vector<int> d_depotCost;
  
  vector<size_t> d_iDepots;
  vector<size_t> d_iCustomers;
  vector<size_t> d_iNodes;
  
  vector<Depot>    d_depots;
  vector<Customer> d_customers;
  vector<Node>     d_nodes;          // TODO do we need this?
  
  vector<vector<double>> d_cost;
  
public:
  
  Data () = delete;
  
  // Constructor to read our own instances
  Data (PROBLEMTYPE inst, ASYCLASS asy, 
       int instance, int nCustomers, int nDepots);

  // Constructor to read Santos instances
  Data (int idx_instance); 

  void print();
  
  vector<int> lysgard_demand() const;
  
private:
  
  void readFile_own ();
  void readFile_santos (int instance, int nDepots, int nRemoveDepots);
  
  void setData();
  void setSettings();
  
  void check() const;
  
  void reset_time_and_count_globals() const;
  
  void create_initial();
};
