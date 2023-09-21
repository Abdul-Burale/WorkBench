/*
 * Commonly used utility functions.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void *checked_malloc(int len){
  void *p = malloc(len);
  assert(p);
  return p;
}
