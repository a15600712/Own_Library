/**
 * @file arithmetic.c
 * @brief Implementation of modular arithmetic operations
 */
#include "arithmetic.h"
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
int64_t PQC_LIB_exp_mod(int64_t base, int64_t exp)
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

// Addition modulo, centered
int64_t PQC_LIB_add_mod(int64_t a, int64_t b)
{
    int64_t result = (a % PQC_LIB_Q + b % PQC_LIB_Q) % PQC_LIB_Q;
    return PQC_LIB_centered_reduce(result);
}

// Subtraction modulo, centered
int64_t PQC_LIB_subtract_mod(int64_t a, int64_t b)  // a-b
{
    int64_t result = (a % PQC_LIB_Q - b % PQC_LIB_Q) % PQC_LIB_Q;
    return PQC_LIB_centered_reduce(result);
}

// Multiplication modulo, centered
int64_t PQC_LIB_multiply_mod(int64_t a, int64_t b)
{
    int64_t result = (a % PQC_LIB_Q * b % PQC_LIB_Q) % PQC_LIB_Q;
    return PQC_LIB_centered_reduce(result);
}

// Add this at beginning of arithmetic.c:
/**
 * @brief Reduce a value modulo Q to the centered range [-Q/2, Q/2)
 *
 * @param x Value to reduce
 * @return int64_t Reduced value in centered range
 */
int64_t PQC_LIB_centered_reduce(int64_t x)
{
    x = x % PQC_LIB_Q;
    // If x > Q/2, subtract Q to get into range [-Q/2, Q/2)
    if (x > PQC_LIB_Q / 2)
    {
        x -= PQC_LIB_Q;
    }
    // If x <= -Q/2, add Q to get into range [-Q/2, Q/2)
    else if (x <= -PQC_LIB_Q / 2)
    {
        x += PQC_LIB_Q;
    }
    return x;
}

// Helper function: Modular inverse using Extended Euclidean Algorithm
int64_t PQC_LIB_mod_inverse(int64_t a)
{
    int64_t t = 0, new_t = 1;
    int64_t r = PQC_LIB_Q, new_r = a;

    while (new_r != 0)
    {
        int64_t quotient = r / new_r;

        // Update t and new_t
        int64_t tmp = t - quotient * new_t;
        t           = new_t;
        new_t       = tmp;

        // Update r and new_r
        tmp   = r - quotient * new_r;
        r     = new_r;
        new_r = tmp;
    }

    if (r > 1)  // No modular inverse exists
    {
        return -1;
    }

    return t < 0 ? t + PQC_LIB_Q : t;
}

// Division modulo, centered
int64_t PQC_LIB_divide_mod(int64_t a, int64_t b)
{
    int64_t b_inv = mod_inverse(b);
    if (b_inv == -1)
    {
        fprintf(stderr, "Division not defined for these arguments (b has no inverse)\n");
        exit(EXIT_FAILURE);
    }

    int64_t result = PQC_LIB_multiply_mod(a, b_inv);
    return PQC_LIB_centered_reduce(result);
}
