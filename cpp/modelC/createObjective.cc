#include "modelC.ih"

void ModelC::createObjective()
{
  d_model.set(GRB_StringAttr_ModelName, "MDAVRP-Gurobi");
  d_model.set(GRB_IntAttr_ModelSense, GRB_MINIMIZE);
}
