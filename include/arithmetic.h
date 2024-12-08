/**
 * @file arithmetic.h
 * @brief Modular arithmetic operations for the PQC library
 */
#ifndef PQC_LIB_ARITHMETIC_H
#define PQC_LIB_ARITHMETIC_H

#include "params.h"

// Function declarations with full namespace
int64_t PQC_LIB_centered_reduce(int64_t x);
int64_t PQC_LIB_exp_mod(int64_t base, int64_t exp);
int64_t PQC_LIB_add_mod(int64_t a, int64_t b);
int64_t PQC_LIB_subtract_mod(int64_t a, int64_t b);
int64_t PQC_LIB_multiply_mod(int64_t a, int64_t b);
int64_t PQC_LIB_divide_mod(int64_t a, int64_t b);
int64_t PQC_LIB_mod_inverse(int64_t a);

// Namespace definitions
#define centered_reduce PQC_LIB_centered_reduce
#define exp_mod         PQC_LIB_exp_mod
#define add_mod         PQC_LIB_add_mod
#define subtract_mod    PQC_LIB_subtract_mod
#define multiply_mod    PQC_LIB_multiply_mod
#define divide_mod      PQC_LIB_divide_mod
#define mod_inverse     PQC_LIB_mod_inverse

#endif /* PQC_LIB_ARITHMETIC_H */
