/**
 * @file zetas.h
 * @brief Zeta value computation for NTT operations in the PQC library
 */
#ifndef PQC_LIB_ZETAS_H
#define PQC_LIB_ZETAS_H

#include "params.h"

// Function declarations with full namespace
int64_t PQC_LIB_zetafinder(bool negacyclic);
int64_t PQC_LIB_bit_reverse(int64_t t, int k);
int64_t* PQC_LIB_gen_zetas_table(int64_t zeta);

// Namespace definitions
#define zetafinder      PQC_LIB_zetafinder
#define bit_reverse     PQC_LIB_bit_reverse
#define gen_zetas_table PQC_LIB_gen_zetas_table

#endif /* PQC_LIB_ZETAS_H */