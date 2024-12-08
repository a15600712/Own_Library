/**
 * @file ntt.c
 * @brief Implementation of Number Theoretic Transform operations
 */
#include "ntt.h"

#include "arithmetic.h"  // Fixed spelling

void PQC_LIB_ForwardNTT(poly* p, const int64_t zetas[])
{
    if (!p || !zetas || p->NTT_Form || !p->Nega_Cyclic)
        return;

    unsigned int len, start, j, k = 0;
    int64_t zeta, t;

    for (len = PQC_LIB_N / 2; len > 0; len >>= 1)
    {
        for (start = 0; start < PQC_LIB_N; start = j + len)
        {
            zeta = zetas[++k];
            for (j = start; j < start + len; ++j)
            {
                t                  = PQC_LIB_multiply_mod(zeta, p->coeffs[j + len]);
                p->coeffs[j + len] = PQC_LIB_subtract_mod(p->coeffs[j], t);
                p->coeffs[j]       = PQC_LIB_add_mod(p->coeffs[j], t);
            }
        }
    }
    p->NTT_Form = true;
}

void PQC_LIB_InverseNTT(poly* p, const int64_t zetas[])
{
    if (!p || !zetas || !p->NTT_Form)
        return;

    unsigned int start, len, j, k = PQC_LIB_N;
    int64_t t, zeta;
    int64_t count = 0;

    for (len = 1; len < PQC_LIB_N; len <<= 1)
    {
        for (start = 0; start < PQC_LIB_N; start = j + len)
        {
            zeta = -zetas[--k];
            for (j = start; j < start + len; ++j)
            {
                t                  = p->coeffs[j];
                p->coeffs[j]       = PQC_LIB_add_mod(t, p->coeffs[j + len]);
                p->coeffs[j + len] = PQC_LIB_subtract_mod(t, p->coeffs[j + len]);
                p->coeffs[j + len] = PQC_LIB_multiply_mod(zeta, p->coeffs[j + len]);
            }
        }
        count++;
    }

    int64_t scale = PQC_LIB_mod_inverse(1 << count);
    for (int i = 0; i < PQC_LIB_N; i++)
    {
        p->coeffs[i] = PQC_LIB_multiply_mod(scale, p->coeffs[i]);
    }

    p->NTT_Form = false;
}