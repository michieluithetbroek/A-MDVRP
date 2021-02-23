#include "mycallbackcompact.ih"

void MyCallbackcompact::callback_user()
{
  if (g_modelSolved)
    abort();
}