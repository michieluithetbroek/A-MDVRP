#include "./cut.ih"

/*
 * We have to normalize cuts before adding them to CPLEX
 * That is, replace x1 + x1 by 2*x1
 */

struct CompareIloNumVar
{
   bool operator() (IloNumVar const &v1, IloNumVar const &v2) const 
   {
      return v1.getId() < v2.getId();
   }
};

IloExpr Cut::normalize(IloExpr const &expr) const
{
   map<IloNumVar, IloNum, CompareIloNumVar> coefs;
   
   for (auto it(expr.getLinearIterator()); it.ok(); ++it)
   {
      auto const c = coefs.find(it.getVar());
      
      if (c == cend(coefs))
        coefs.insert({it.getVar(), it.getCoef()});
      
      else
         c->second += it.getCoef();
   }
   
   
   
   IloExpr e(expr.getEnv());
   
   // TODO why is this not a range-based for-loop?
   for (auto it = coefs.cbegin(); it != coefs.cend(); ++it)
      e += it->first * it->second;
   
   return e;
}
