// zetas.c
#include "zetas.h"
#include "exp_mod.h"
#include <math.h>

int64_t zetafinder(bool negacyclic) {
  int64_t k = 0;
  if (negacyclic) {
    k = LOG2_N; // negacyclic: zeta^(2^(k-1))=-1
  } else {
    k = LOG2_N - 1; // cyclic: zeta^(2^(k))=-1
  }

  int64_t power = (int64_t)pow(2, k);

  for (int64_t zeta = 0; zeta < Q; zeta++) {
    if (exp_mod(zeta, power) == Q - 1) // if exist then return
    {
      return zeta;
    }
  }
  return 0;
}

int64_t bit_reverse(int64_t t, int k) {
  int64_t reverse = 0;
  for (int i = 0; i < k; i++) {
    if (t & 1) {
      reverse = reverse << 1;
      reverse = reverse | 1;
      t = t >> 1;
    } else {
      reverse = reverse << 1;
      t = t >> 1;
    }
  }
  return reverse;
}

void gen_zetas_table(int64_t *zetas, int size, int64_t zeta) {
  zetas[0] = 1;
  for (int i = 1; i < size; i++) {
    zetas[i] = exp_mod(zeta, bit_reverse(i, LOG2_N));
  }
}