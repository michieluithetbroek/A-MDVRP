#pragma once

#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int>> get_characs (int instanceType);

string get_filename(int dep, int cust, int rep, string folder);
string getInstanceName();

string getPrintInstanceName();
string getPrintInstanceName(int n, int m, int rep);

int    get_nInstances();

void set_global_enums (int instanceType);

void skipLines(std::ifstream &fstr, int nLines);
