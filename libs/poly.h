/**
 * @file poly.h
 * @brief Polynomial data structure for ring operations
 */
#ifndef POLY_H
#define POLY_H

#include "params.h"

/**
 * Elements of R_q = Z_q[X]/(X^n + 1). Represents polynomial
 * coeffs[0] + X*coeffs[1] + X^2*coeffs[2] + ... + X^{n-1}*coeffs[n-1]
 */
typedef struct
{
    int64_t coeffs[PQC_LIB_N] = {0};    // Polynomial coefficients
    bool NTT_Form             = false;  // Flag indicating if polynomial is in NTT form
    bool Mont_Form            = false;  // Flag indicating if coefficients are in Montgomery form
    bool Nega_Cyclic          = true;   // Flag indicating if polynomial is negacyclic
} poly;

#endif /* POLY_H */