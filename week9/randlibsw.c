#include "randlib.h"
#include <stdio.h>
#include <stdlib.h>
static void software_rand64_init (void) __attribute__((constructor));
static void software_rand64_fini (void) __attribute__((destructor));
/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
static void
software_rand64_init (void)
{
  urandstream = fopen ("/dev/urandom", "r");
  if (! urandstream)
    abort ();
}

extern unsigned long long rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

/* Finalize the software rand64 implementation.  */
static void
software_rand64_fini (void)
{
  fclose (urandstream);
}
