/**
 * @file poly.h
 * @brief Polynomial operations for the PQC library
 */
#ifndef PQC_LIB_POLY_H
#define PQC_LIB_POLY_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "params.h"

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

// Function declarations with full namespace
poly PQC_LIB_create_poly(void);
matrix_poly PQC_LIB_init_matrix_poly(void);
matrix_poly PQC_LIB_create_matrix(size_t rows, size_t cols);
void PQC_LIB_free_matrix(matrix_poly *mat);
void PQC_LIB_print_poly(const poly *p);
void PQC_LIB_print_matrix(const matrix_poly *mat);
void PQC_LIB_print_NTTForm_poly(const poly *p);
void PQC_LIB_print_NTTForm_matrix(const matrix_poly *mat);

// Matrix-vector operations
poly *PQC_LIB_matrix_vector_mul(const matrix_poly *mat, const poly *vec);

// NTT form polynomial arithmetic operations
poly PQC_LIB_NTTForm_poly_add(const poly *a, const poly *b);
poly PQC_LIB_NTTForm_poly_sub(const poly *a, const poly *b);
poly PQC_LIB_NTTForm_poly_mul(const poly *a, const poly *b);

// Namespace definitions for shorter names
#define create_poly          PQC_LIB_create_poly
#define init_matrix_poly     PQC_LIB_init_matrix_poly
#define create_matrix        PQC_LIB_create_matrix
#define free_matrix          PQC_LIB_free_matrix
#define print_poly           PQC_LIB_print_poly
#define print_matrix         PQC_LIB_print_matrix
#define print_NTTForm_poly   PQC_LIB_print_NTTForm_poly
#define print_NTTForm_matrix PQC_LIB_print_NTTForm_matrix
#define NTTForm_poly_add     PQC_LIB_NTTForm_poly_add
#define NTTForm_poly_sub     PQC_LIB_NTTForm_poly_sub
#define NTTForm_poly_mul     PQC_LIB_NTTForm_poly_mul
#define matrix_vector_mul    PQC_LIB_matrix_vector_mul

#endif /* PQC_LIB_POLY_H */