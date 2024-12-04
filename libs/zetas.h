// zetas.h
#ifndef ZETAS_H
#define ZETAS_H

#include "params.h"
#include <stdbool.h>
#include <stdint.h>

// Function declarations
int64_t zetafinder(bool negacyclic);
int64_t bit_reverse(int64_t t, int k);
void gen_zetas_table(int64_t *zetas, int size, int64_t zeta);

#endif // ZETAS_H