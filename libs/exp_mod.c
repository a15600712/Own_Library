/**
 * @file exp_mod.c
 * @brief Implementation of modular exponentiation using fast squaring method
 */

#include "exp_mod.h"

/**
 * @brief Compute (base^exp) mod Q using fast modular exponentiation
 *
 * This function uses the square-and-multiply algorithm to efficiently
 * compute modular exponentiation with reduced number of multiplications.
 *
 * @param base The base number
 * @param exp The exponent
 * @return int64_t Result of (base^exp) mod Q
 */
int64_t exp_mod(int64_t base, int64_t exp)
{
    if (exp <= 0)
    {
        return 1;
    }

    if (exp == 1)
    {
        int64_t tmp = base % PQC_LIB_Q;
        return tmp < 0 ? tmp + PQC_LIB_Q : tmp;
    }

    int64_t tmp = exp_mod(base, exp / 2);
    tmp         = (tmp * tmp) % PQC_LIB_Q;

    if ((exp & 1) == 1)
    {
        return ((base % PQC_LIB_Q) * tmp) % PQC_LIB_Q;
    }
    else
    {
        return tmp;
    }
}