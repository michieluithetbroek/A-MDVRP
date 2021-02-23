#include "./cut.ih"

/*
 * 
 */

Cut::Cut (int priority, bool lazy, bool user, bool stopIfFound, bool onlyRootNode, string const &name)
:
  d_priority       (priority),
  d_lazy           (lazy),
  d_user           (user),
  d_stopIfCutFound (stopIfFound),
  d_onlyRootNode   (onlyRootNode),
  d_cnt_lazy       (0),
  d_cnt_user       (0),
  d_nCuts_lazy     (0),
  d_nCuts_user     (0),
  d_time_lazy      (dur_t::zero()),
  d_time_user      (dur_t::zero()),
  d_name           (name)
{};