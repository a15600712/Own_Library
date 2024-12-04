// exp_mod.c
#include "exp_mod.h"

int64_t
exp_mod(int64_t base,
        int64_t exp) // Exponential Squaring (Fast Modulo Multiplication)
{
  if (exp <= 0) {
    return 1;
  }
  if (exp == 1) {
    int64_t tmp = base % Q;
    return tmp < 0 ? tmp + Q : tmp;
  }

  int64_t tmp = exp_mod(base, exp / 2);
  tmp = (tmp * tmp) % Q;

  if ((exp & 1) == 1) {
    return ((base % Q) * tmp) % Q;
  } else {
    return tmp;
  }
}