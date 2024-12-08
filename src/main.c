/**
 * @file main.c
 * @brief Main program demonstrating matrix-vector multiplication with polynomials
 */
#include <stdio.h>
#include <stdlib.h>

#include "ntt.h"
#include "poly.h"
#include "zetas.h"

int main()
{
    printf("=== Matrix-Vector Multiplication Demo ===\n\n");

    // Create a 2x2 matrix of polynomials
    matrix_poly mat = PQC_LIB_create_matrix(2, 2);

    // Initialize matrix with simple values
    // First row
    mat.polynomial[0][0].coeffs[0] = 1;  // X^0
    mat.polynomial[0][0].coeffs[1] = 2;  // X^1
    mat.polynomial[0][0].coeffs[2] = 3;  // X^2
    mat.polynomial[0][0].coeffs[3] = 4;  // X^3

    mat.polynomial[0][1].coeffs[0] = 2;
    mat.polynomial[0][1].coeffs[1] = 3;
    mat.polynomial[0][1].coeffs[2] = 4;
    mat.polynomial[0][1].coeffs[3] = 1;

    // Second row
    mat.polynomial[1][0].coeffs[0] = 5;
    mat.polynomial[1][0].coeffs[1] = 6;
    mat.polynomial[1][0].coeffs[2] = 7;
    mat.polynomial[1][0].coeffs[3] = 8;

    mat.polynomial[1][1].coeffs[0] = 6;
    mat.polynomial[1][1].coeffs[1] = 7;
    mat.polynomial[1][1].coeffs[2] = 8;
    mat.polynomial[1][1].coeffs[3] = 5;

    // Create vector (size must match matrix columns)
    poly* vec = (poly*)malloc(2 * sizeof(poly));
    if (!vec)
    {
        printf("Memory allocation failed for vector\n");
        PQC_LIB_free_matrix(&mat);
        return 1;
    }

    // Initialize vector elements
    vec[0]           = PQC_LIB_create_poly();
    vec[0].coeffs[0] = 1;
    vec[0].coeffs[1] = 2;
    vec[0].coeffs[2] = 3;
    vec[0].coeffs[3] = 4;

    vec[1]           = PQC_LIB_create_poly();
    vec[1].coeffs[0] = 4;
    vec[1].coeffs[1] = 3;
    vec[1].coeffs[2] = 2;
    vec[1].coeffs[3] = 1;

    // Print original matrix and vector
    printf("Original Matrix:\n");
    PQC_LIB_print_matrix(&mat);

    printf("\nOriginal Vector:\n");
    for (size_t i = 0; i < 2; i++)
    {
        printf("Vec[%zu]:\n", i);
        PQC_LIB_print_poly(&vec[i]);
    }

    // Generate zetas for NTT
    int64_t zeta = PQC_LIB_zetafinder(true);  // true for negacyclic
    if (zeta == 0)
    {
        printf("Error: No valid zeta found\n");
        free(vec);
        PQC_LIB_free_matrix(&mat);
        return 1;
    }

    int64_t* zetas = PQC_LIB_gen_zetas_table(zeta);
    if (!zetas)
    {
        printf("Error: Failed to generate zetas table\n");
        free(vec);
        PQC_LIB_free_matrix(&mat);
        return 1;
    }

    // Convert matrix to NTT form
    for (size_t i = 0; i < mat.rows; i++)
    {
        for (size_t j = 0; j < mat.cols; j++)
        {
            PQC_LIB_ForwardNTT(&mat.polynomial[i][j], zetas);
        }
    }

    // Convert vector to NTT form
    for (size_t i = 0; i < mat.cols; i++)
    {
        PQC_LIB_ForwardNTT(&vec[i], zetas);
    }

    printf("\nAfter NTT transformation:\n");
    printf("\nMatrix in NTT form:\n");
    PQC_LIB_print_NTTForm_matrix(&mat);

    printf("\nVector in NTT form:\n");
    for (size_t i = 0; i < mat.cols; i++)
    {
        printf("Vec[%zu]:\n", i);
        PQC_LIB_print_NTTForm_poly(&vec[i]);
    }

    // Perform matrix-vector multiplication
    poly* result = PQC_LIB_matrix_vector_mul(&mat, vec);
    if (!result)
    {
        printf("Matrix-vector multiplication failed\n");
        free(zetas);
        free(vec);
        PQC_LIB_free_matrix(&mat);
        return 1;
    }

    printf("\nResult in NTT form:\n");
    for (size_t i = 0; i < mat.rows; i++)
    {
        printf("Result[%zu]:\n", i);
        PQC_LIB_print_NTTForm_poly(&result[i]);
    }

    // Convert result back from NTT form
    for (size_t i = 0; i < mat.rows; i++)
    {
        PQC_LIB_InverseNTT(&result[i], zetas);
    }

    printf("\nFinal result after inverse NTT:\n");
    for (size_t i = 0; i < mat.rows; i++)
    {
        printf("Result[%zu]:\n", i);
        PQC_LIB_print_poly(&result[i]);
    }

    // Cleanup
    free(zetas);
    free(result);
    free(vec);
    PQC_LIB_free_matrix(&mat);

    return 0;
}