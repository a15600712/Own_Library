/**
 * @file zetas.c
 * @brief Implementation of zeta value computation and bit manipulation functions
 * for polynomial operations in a finite field.
 */

#include "zetas.h"

#include "exp_mod.h"

/**
 * @brief Find the primitive nth root of unity (zeta) in the field Z_q
 *
 * This function searches for a value zeta that satisfies either
 * zeta^(2^k) = -1 (negacyclic case) or zeta^(2^(k-1)) = -1 (cyclic case)
 * in the field Z_q.
 *
 * @param negacyclic Flag to determine if looking for negacyclic or cyclic root
 * @return int64_t Returns the found zeta value, or 0 if none found
 */
int64_t zetafinder(bool negacyclic)
{
    int64_t k = 0;
    if (negacyclic)
    {
        k = PQC_LIB_LOG2_N;  // negacyclic: zeta^(2^(k))=-1
    }
    else
    {
        k = PQC_LIB_LOG2_N - 1;  // cyclic: zeta^(2^(k-1))=-1
    }

    int64_t power = (int64_t)pow(2, k);

    for (int64_t zeta = 0; zeta < PQC_LIB_Q; zeta++)
    {
        if (exp_mod(zeta, power) == PQC_LIB_Q - 1)  // if exist then return
        {
            return zeta;
        }
    }
    return 0;
}

/**
 * @brief Perform bit reversal operation on an integer
 *
 * This function reverses the least significant k bits of the input integer.
 * For example, if k=3, and t=6 (110 in binary), the result would be 3 (011 in binary).
 *
 * @param t The integer to be bit-reversed
 * @param k Number of bits to reverse
 * @return int64_t The bit-reversed value
 */
int64_t bit_reverse(int64_t t, int k)
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

/**
 * @brief Generate a table of powers of zeta with bit-reversed indices
 *
 * Creates a table where zetas[i] = zeta^(bit_reverse(i)).
 * This is used for efficient implementation of Number Theoretic Transform (NTT).
 *
 * @param zetas Output array to store the computed zeta values
 * @param size Size of the zetas array
 * @param zeta The primitive root of unity to use
 */
void gen_zetas_table(int64_t *zetas, int size, int64_t zeta)
{
    zetas[0] = 1;
    for (int i = 1; i < size; i++)
    {
        zetas[i] = exp_mod(zeta, bit_reverse(i, PQC_LIB_LOG2_N));
    }
}