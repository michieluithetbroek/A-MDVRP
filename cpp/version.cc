#include "main.ih"
#include "icmconf"

#ifdef USE_VERSION
#include "VERSION"
#endif

#ifndef AUTHOR
#define AUTHOR "A.H. Schrotenboer and M.A.J. Uit het Broek"
#endif

#ifndef VERSION
#define VERSION "1.00.00"
#endif

#ifndef YEARS
#define YEARS "2018"
#endif

namespace Icmbuild
{
  char version[] = VERSION;
  char years[]   = YEARS;
  char author[]  = AUTHOR;
}
