/**
 * @file ntt.h
 * @brief Number Theoretic Transform operations for the PQC library
 */
#ifndef PQC_LIB_NTT_H
#define PQC_LIB_NTT_H

#include "poly.h"

// Function declarations with full namespace
void PQC_LIB_ForwardNTT(poly* p, const int64_t zetas[]);
void PQC_LIB_ForwardNTT_Mont(poly* p);
void PQC_LIB_InverseNTT(poly* p, const int64_t zetas[]);
void PQC_LIB_InverseNTT_Mont(poly* p);

// Namespace definitions
#define ForwardNTT      PQC_LIB_ForwardNTT
#define ForwardNTT_Mont PQC_LIB_ForwardNTT_Mont
#define InverseNTT      PQC_LIB_InverseNTT
#define InverseNTT_Mont PQC_LIB_InverseNTT_Mont

#endif /* PQC_LIB_NTT_H */