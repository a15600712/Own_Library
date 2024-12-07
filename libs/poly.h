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
    int64_t coeffs[PQC_LIB_N];  // Polynomial coefficients
    bool NTT_Form;              // Flag indicating if polynomial is in NTT form
    bool Mont_Form;             // Flag indicating if coefficients are in Montgomery form
    bool Nega_Cyclic;           // Flag indicating if polynomial is negacyclic
} poly;

typedef struct
{
    poly **polynomial;
    size_t rows;
    size_t cols;
} matrix_poly;

/**
 * @brief Create a polynomial with default values.
 * @return An initialized polynomial.
 */
poly create_poly();

/**
 * @brief Initialize an empty matrix_poly.
 * @return A matrix_poly with null pointers and zero dimensions.
 */
matrix_poly init_matrix_poly();

/**
 * @brief Create a matrix_poly with specified dimensions.
 *        Allocates memory for a matrix of polynomials.
 * @param rows Number of rows.
 * @param cols Number of columns.
 * @return An initialized matrix_poly.
 */
matrix_poly create_matrix(size_t rows, size_t cols);

/**
 * @brief Free the memory allocated for a matrix_poly.
 *        Ensures all dynamically allocated memory is released.
 * @param mat Pointer to the matrix_poly to be freed.
 */
void free_matrix(matrix_poly *mat);

/**
 * @brief Print a polynomial.
 * @param p Pointer to the polynomial to be printed.
 */
void print_poly(const poly *p);

/**
 * @brief Print a matrix of polynomials.
 * @param mat Pointer to the matrix_poly to be printed.
 */
void print_matrix(const matrix_poly *mat);

#endif /* POLY_H */
