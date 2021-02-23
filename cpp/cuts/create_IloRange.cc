#include "./cut.ih"

/*
 * This function translates vector<CutReturn> into vector<IloRange>
 * Hereby we keep the implementation of the cuts themselves 
 * independent of the solver that is used.
 */

vector<IloRange> Cut::createIloRange(IloEnv const &env, 
                                     IloArray<IloNumVarArray> const &variables,
                                     vector<CutReturn> const &cuts_in) const
{
  vector<IloRange> cuts_out;
  cuts_out.reserve(cuts_in.size());
  
  for (auto const &cut: cuts_in)
  {
    IloExpr expr(env);
    
    for (auto const &coef: cut.coeff)
      expr += coef[0] * variables[coef[1]][coef[2]];
    
    expr = normalize(expr);
    
    cuts_out.emplace_back(expr <= cut.rhs);
  }
  
  return cuts_out;
}
