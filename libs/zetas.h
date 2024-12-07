#ifndef ZETAS_H
#define ZETAS_H

#include "params.h"

/*
 * Namespace definitions for PQC library functions
 */
#define zetafinder      PQC_LIB_NAMESPACE(zetafinder)
#define bit_reverse     PQC_LIB_NAMESPACE(bit_reverse)
#define gen_zetas_table PQC_LIB_NAMESPACE(gen_zetas_table)

/**
 * Find zeta value based on negacyclic parameter
 * @param negacyclic boolean flag for negacyclic mode
 * @return int64_t zeta value
 */
int64_t zetafinder(bool negacyclic);

/**
 * Perform bit reversal on an integer
 * @param t integer to reverse
 * @param k number of bits
 * @return int64_t reversed value
 */
int64_t bit_reverse(int64_t t, int k);

/**
 * Generate table of zeta values
 * @param zetas output array for zeta values
 * @param size size of the array
 * @param zeta initial zeta value
 */
void gen_zetas_table(int64_t *zetas, int size, int64_t zeta);

#endif /* ZETAS_H */