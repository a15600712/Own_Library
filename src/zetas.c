/**
 * @file zetas.c
 * @brief Implementation of zeta value computations
 */
#include "zetas.h"

#include "arithmetic.h"  // Fixed spelling

int64_t PQC_LIB_bit_reverse(int64_t t, int k)
{
    int64_t reverse = 0;
    for (int i = 0; i < k; i++)
    {
        if (t & 1)
        {
            reverse = reverse << 1;
            reverse = reverse | 1;
            t       = t >> 1;
        }
        else
        {
            reverse = reverse << 1;
            t       = t >> 1;
        }
    }
    return reverse;
}

int64_t PQC_LIB_zetafinder(bool negacyclic)
{
    int64_t k     = negacyclic ? PQC_LIB_LOG2_N : PQC_LIB_LOG2_N - 1;
    int64_t power = 1 << k;

    for (int64_t zeta = 0; zeta < PQC_LIB_Q; zeta++)
    {
        if (PQC_LIB_exp_mod(zeta, power) == PQC_LIB_Q - 1)
        {
            return zeta;
        }
    }
    return 0;
}

int64_t* PQC_LIB_gen_zetas_table(int64_t zeta)
{
    int64_t h      = PQC_LIB_LOG2_N + 1;
    int64_t size   = 1 << h;
    int64_t* zetas = (int64_t*)malloc(size * sizeof(int64_t));

    if (!zetas)
        return NULL;

    zetas[0] = 1;
    for (int i = 1; i < size; i++)
    {
        zetas[i] = PQC_LIB_exp_mod(zeta, PQC_LIB_bit_reverse(i, PQC_LIB_LOG2_N));
    }

    return zetas;
}