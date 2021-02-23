#include "./../main.ih"


/*
  * We use std::make_shared such that the Cut objects
  * are automatically destroyed when modelA goes out of scope
  * 
  * The cuts are performed in the order that they are added to the vector
  * 
  * Parameters:
  *   int    Relative priority of the cut (lower is more priority)
  *   bool   Cut called in lazy callback?
  *   bool   Cut called in user callback?
  *   bool   stop if cut found, regardless the value of the bool 'sequential' in solve.cc
  *   bool   apply cut only in root node
  * 
  * 
  * There are two versions.
  * In the first function we can manually set the vector
  * The second function takes an vector with integers (0 = false) as input
  * 
  */


/*
 * ALERT Do not change the order in which the elements are added to the vector!!
 * You should use the priority index for this
 * 
 * Parameters
 *   s1    settings
 *   s2    Is there a bound on the route size?
 * 
 */

vector<shared_ptr<Cut>> make_cut_vector(Data const &data, array<bool, 12> const &s, bool s2)
{
  if (not g_onlyRoot)
    throw string("This are the settings that only solve the root node (make_cut_vector.cc)");
  
  vector<shared_ptr<Cut>> tmp_vector;

  // Model defining
  tmp_vector.emplace_back( make_shared<Cut_cap>                 (0,  true,  true,  false, true, data));
  tmp_vector.emplace_back( make_shared<Laporte>                 (1,  false, false, false, true, data));
  
  tmp_vector.emplace_back( make_shared<Laporte_single_customer> (2,  s[0],  s[0],  false, true, data));
  tmp_vector.emplace_back( make_shared<DK_depot_plus>           (3,  s[1],  s[1],  false, true, data));
  tmp_vector.emplace_back( make_shared<DK_depot_min>            (4,  s[2],  s[2],  false, true, data));
  
  tmp_vector.emplace_back( make_shared<DK_length_plus>          (5,  s2,    s2,    false, true, data));
  tmp_vector.emplace_back( make_shared<DK_length_min>           (6,  s2,    s2,    false, true, data));
  
  // Additional cuts
  tmp_vector.emplace_back( make_shared<DK_plus>                 (7,  false, s[3],  false, true, data));
  tmp_vector.emplace_back( make_shared<DK_min>                  (8,  false, s[4],  false, true, data));

  tmp_vector.emplace_back( make_shared<Cut_cat>                 (9,  false, s[5],  false, true, data));
  tmp_vector.emplace_back( make_shared<Cut_gen_large_multistar> (10, false, s[6],  false, true, data));
  tmp_vector.emplace_back( make_shared<Cut_hypotour>            (13, false, false, false, true, data));
  tmp_vector.emplace_back( make_shared<Cut_hom_multistar>       (12, false, s[8],  false, true, data));
  tmp_vector.emplace_back( make_shared<Cut_framed_cap>          (11, false, s[9],  false, true, data));
  
  tmp_vector.emplace_back( make_shared<Cut_comb>                (14, false, s[10], false, true, data));
  tmp_vector.emplace_back( make_shared<Cut_Tcomb>               (15, false, false, false, true, data));
  tmp_vector.emplace_back( make_shared<Cut_T1comb>              (16, false, s[12], false, true, data));
  
  sort (begin(tmp_vector), end(tmp_vector), [](auto const &lhs, auto const &rhs)
  {
    return lhs->priority() < rhs->priority();
  });
  
  return tmp_vector;
}




vector<shared_ptr<Cut>> make_cut_vector_0 (Data const &data)
{
  
  vector<shared_ptr<Cut>> tmp_vector;
  
  tmp_vector.emplace_back( make_shared<Cut_cap>                 (0,  true,  true,  true,  false, data) );
  tmp_vector.emplace_back( make_shared<Laporte>                 (1,  false, false, false, false, data) );
  tmp_vector.emplace_back( make_shared<Laporte_single_customer> (2,  true,  true,  false, false, data) );

  tmp_vector.emplace_back( make_shared<DK_depot_plus>           (6,  false,  false,  false, false, data) );
  tmp_vector.emplace_back( make_shared<DK_depot_min>            (7,  false,  false,  false, false, data) );
  
  if (P_TYPE == PROBLEMTYPE::MDAMTSP)
  {
    tmp_vector.emplace_back( make_shared<DK_length_plus>        (8, true,  false, false, false, data) );
    tmp_vector.emplace_back( make_shared<DK_length_min>         (9, true,  false, false, false, data) );
  }
  else
  {
    tmp_vector.emplace_back( make_shared<DK_length_plus>        (8, false,  false, false, false, data) );
    tmp_vector.emplace_back( make_shared<DK_length_min>         (9, false,  false, false, false, data) );
  }
  
  tmp_vector.emplace_back( make_shared<Cut_cat>                 (10, false, false, false, false, data) );
  
  tmp_vector.emplace_back( make_shared<DK_plus>                 (11, false, false, false, false, data) );
  tmp_vector.emplace_back( make_shared<DK_min>                  (12, false, false, false, false, data) );

  
  
  tmp_vector.emplace_back( make_shared<Cut_gen_large_multistar> (13, false, false, false, false,  data) );
  tmp_vector.emplace_back( make_shared<Cut_hypotour>            (14, false, false, false, false,  data) );
  tmp_vector.emplace_back( make_shared<Cut_hom_multistar>       (15, false, false, false, false,  data) );
  tmp_vector.emplace_back( make_shared<Cut_framed_cap>          (16, false, false, false, false,  data) );
    
  
  tmp_vector.emplace_back( make_shared<Cut_comb>                (17, false, false, false, false, data) );
  tmp_vector.emplace_back( make_shared<Cut_Tcomb>               (18, false, false, false, false, data) );
  tmp_vector.emplace_back( make_shared<Cut_T1comb>              (19, false, false, false, false, data) );

  
  sort (begin(tmp_vector), end(tmp_vector), [](auto const &lhs, auto const &rhs)
  {
    return lhs->priority() < rhs->priority();
  });
  
  return tmp_vector;
}

vector<shared_ptr<Cut>> make_cut_vector_1 (Data const &data)
{
  bool const use_cap_cuts = (P_TYPE != PROBLEMTYPE::MDATSP);

  vector<shared_ptr<Cut>> tmp_vector;
  
  tmp_vector.emplace_back( make_shared<Cut_cap>                 (0,  true,  true,  true,  false, data) );
  tmp_vector.emplace_back( make_shared<Laporte>                 (1,  false, false, false, false, data) );
  tmp_vector.emplace_back( make_shared<Laporte_single_customer> (2,  true,  true,  false, false, data) );

  tmp_vector.emplace_back( make_shared<DK_depot_plus>           (6,  true,  true,  false, false, data) );
  tmp_vector.emplace_back( make_shared<DK_depot_min>            (7,  true,  true,  false, false, data) );
  
  if (P_TYPE == PROBLEMTYPE::MDAMTSP)
  {
    tmp_vector.emplace_back( make_shared<DK_length_plus>        (8,  true,  true, false, false, data) );
    tmp_vector.emplace_back( make_shared<DK_length_min>         (9,  true,  true, false, false, data) );
  }
  else
  {
    tmp_vector.emplace_back( make_shared<DK_length_plus>        (8,  false,  false, false, false, data) );
    tmp_vector.emplace_back( make_shared<DK_length_min>         (9,  false,  false, false, false, data) );
  }
  
  tmp_vector.emplace_back( make_shared<Cut_cat>                 (10, false, true,  false, false, data) );
  
  tmp_vector.emplace_back( make_shared<DK_plus>                 (11, false, true,  false, false, data) );
  tmp_vector.emplace_back( make_shared<DK_min>                  (12, false, true,  false, false, data) );

  tmp_vector.emplace_back( make_shared<Cut_gen_large_multistar> (13, false, use_cap_cuts,  false, false,  data) );
  tmp_vector.emplace_back( make_shared<Cut_hypotour>            (14, false, false, false, false,  data) );
  tmp_vector.emplace_back( make_shared<Cut_hom_multistar>       (15, false, use_cap_cuts,  false, false,  data) );
  tmp_vector.emplace_back( make_shared<Cut_framed_cap>          (16, false, use_cap_cuts,  false, false,  data) );
  
  tmp_vector.emplace_back( make_shared<Cut_comb>                (17, false, true,  false, false, data) );
  tmp_vector.emplace_back( make_shared<Cut_Tcomb>               (18, false, false, false, false, data) );
  tmp_vector.emplace_back( make_shared<Cut_T1comb>              (19, false, true,  false, false, data) );
  
  sort (begin(tmp_vector), end(tmp_vector), [](auto const &lhs, auto const &rhs)
  {
    return lhs->priority() < rhs->priority();
  });
  
  return tmp_vector;
}
