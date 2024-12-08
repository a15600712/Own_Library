/**
 * @file params.h
 * @brief Parameter definitions for the PQC library
 */
#ifndef PARAMS_H
#define PARAMS_H

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Ring dimension for polynomial operations
 */
#define PQC_LIB_N 4

/**
 * Field modulus value
 */
#define PQC_LIB_Q 17

/**
 * POLYNOMIAL matrix size
 */
#define PQC_LIB_MATRIX_K 3

/**
 * Logarithm of ring dimension
 */
#define PQC_LIB_LOG2_N (int64_t) log2(PQC_LIB_N)  // log2(256)

/**
 * Namespace macro for the PQC library functions
 */
#define PQC_LIB_NAMESPACE(x) PQC_LIB_##x

/**
 * Helper macros for modular arithmetic (currently commented out)
 */
// #define REDUCE(x)    ((x) < Q ? (x) : (x) - Q)  // Reduction modulo Q
// #define CADDQ(x)     ((x) < 0 ? (x) + Q : (x))  // Centered reduction

#endif /* PARAMS_H */