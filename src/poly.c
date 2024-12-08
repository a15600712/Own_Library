
/**
 * @file poly.c
 * @brief Implementation of polynomial operations
 */
#include "poly.h"

#include "arithmetic.h"  // Fixed spelling

poly PQC_LIB_create_poly(void)
{
    poly p;
    for (int i = 0; i < PQC_LIB_N; ++i)
    {
        p.coeffs[i] = 0;
    }
    p.NTT_Form    = false;
    p.Mont_Form   = false;
    p.Nega_Cyclic = true;
    return p;
}

matrix_poly PQC_LIB_init_matrix_poly(void)
{
    matrix_poly mat;
    mat.polynomial = NULL;
    mat.rows       = 0;
    mat.cols       = 0;
    return mat;
}

matrix_poly PQC_LIB_create_matrix(size_t rows, size_t cols)
{
    matrix_poly mat = PQC_LIB_init_matrix_poly();
    mat.rows        = rows;
    mat.cols        = cols;

    mat.polynomial = (poly **)malloc(rows * sizeof(poly *));
    if (mat.polynomial == NULL)
    {
        perror("Error: Memory allocation failed for matrix rows");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < rows; ++i)
    {
        mat.polynomial[i] = (poly *)malloc(cols * sizeof(poly));
        if (mat.polynomial[i] == NULL)
        {
            perror("Error: Memory allocation failed for matrix columns");
            for (size_t k = 0; k < i; ++k)
            {
                free(mat.polynomial[k]);
            }
            free(mat.polynomial);
            exit(EXIT_FAILURE);
        }

        for (size_t j = 0; j < cols; ++j)
        {
            mat.polynomial[i][j] = PQC_LIB_create_poly();
        }
    }

    return mat;
}

void PQC_LIB_print_NTTForm_poly(const poly *p)
{
    if (p == NULL)
    {
        printf("NULL polynomial\n");
        return;
    }
    if (p->NTT_Form == 0)
    {
        printf("Must in NTT Form\n");
        return;
    }
    printf("NTT Form Polynomial: ");
    printf("NTT_Form: %d, Mont_Form: %d, Nega_Cyclic: %d\n", p->NTT_Form, p->Mont_Form, p->Nega_Cyclic);

    printf(" ( ");
    for (size_t i = 0; i < PQC_LIB_N; ++i)
    {
        printf("%ld", p->coeffs[i]);
        if (i != PQC_LIB_N - 1)
        {
            printf(" , ");
        }
    }
    printf(" )");
    printf("\n");
}

void PQC_LIB_print_poly(const poly *p)
{
    if (p == NULL)
    {
        printf("NULL polynomial\n");
        return;
    }
    printf("Polynomial: ");
    printf("NTT_Form: %d, Mont_Form: %d, Nega_Cyclic: %d\n", p->NTT_Form, p->Mont_Form, p->Nega_Cyclic);
    printf(" ( ");
    for (size_t i = 0; i < PQC_LIB_N; ++i)
    {
        if (p->coeffs[i] != 0)
        {
            printf("%ld", p->coeffs[i]);
            if (i > 0)
                printf("*X^%zu", i);
            if (i != PQC_LIB_N - 1)
            {
                printf(" + ");
            }
        }
    }
    printf(" ) ");
    printf("\n");
}

void PQC_LIB_print_matrix(const matrix_poly *mat)
{
    if (mat == NULL || mat->polynomial == NULL)
    {
        printf("NULL matrix\n");
        return;
    }
    printf("Matrix (%zux%zu):\n", mat->rows, mat->cols);
    for (size_t i = 0; i < mat->rows; ++i)
    {
        for (size_t j = 0; j < mat->cols; ++j)
        {
            printf("Polynomial[%zu][%zu]:\n", i, j);
            PQC_LIB_print_poly(&mat->polynomial[i][j]);
        }
        printf("\n");
    }
}
void PQC_LIB_print_NTTForm_matrix(const matrix_poly *mat)
{
    if (mat == NULL || mat->polynomial == NULL)
    {
        printf("NULL matrix\n");
        return;
    }
    printf("Matrix (%zux%zu):\n", mat->rows, mat->cols);
    for (size_t i = 0; i < mat->rows; ++i)
    {
        for (size_t j = 0; j < mat->cols; ++j)
        {
            printf("Polynomial[%zu][%zu]:\n", i, j);
            PQC_LIB_print_NTTForm_poly(&mat->polynomial[i][j]);
        }
        printf("\n");
    }
}

void PQC_LIB_free_matrix(matrix_poly *mat)
{
    if (mat == NULL || mat->polynomial == NULL)
    {
        return;
    }

    for (size_t i = 0; i < mat->rows; ++i)
    {
        free(mat->polynomial[i]);
    }

    free(mat->polynomial);

    mat->polynomial = NULL;
    mat->rows = mat->cols = 0;
}

poly PQC_LIB_NTTForm_poly_add(const poly *a, const poly *b)
{
    poly result = PQC_LIB_create_poly();

    // Input validation
    if (!a || !b)
    {
        fprintf(stderr, "Error: Null polynomial pointer in NTTForm_poly_add\n");
        return result;
    }

    // Check if polynomials are in NTT form
    if (!a->NTT_Form || !b->NTT_Form)
    {
        fprintf(stderr, "Error: Polynomials must be in NTT form for NTTForm_poly_add\n");
        return result;
    }

    // Check if polynomials have compatible Montgomery form
    if (a->Mont_Form != b->Mont_Form)
    {
        fprintf(stderr, "Error: Polynomials must have compatible Montgomery form\n");
        return result;
    }

    // Perform coefficient-wise addition
    for (size_t i = 0; i < PQC_LIB_N; i++)
    {
        result.coeffs[i] = PQC_LIB_add_mod(a->coeffs[i], b->coeffs[i]);
    }

    // Set flags
    result.NTT_Form    = true;
    result.Mont_Form   = a->Mont_Form;
    result.Nega_Cyclic = a->Nega_Cyclic && b->Nega_Cyclic;

    return result;
}

poly PQC_LIB_NTTForm_poly_sub(const poly *a, const poly *b)
{
    poly result = PQC_LIB_create_poly();

    // Input validation
    if (!a || !b)
    {
        fprintf(stderr, "Error: Null polynomial pointer in NTTForm_poly_sub\n");
        return result;
    }

    // Check if polynomials are in NTT form
    if (!a->NTT_Form || !b->NTT_Form)
    {
        fprintf(stderr, "Error: Polynomials must be in NTT form for NTTForm_poly_sub\n");
        return result;
    }

    // Check if polynomials have compatible Montgomery form
    if (a->Mont_Form != b->Mont_Form)
    {
        fprintf(stderr, "Error: Polynomials must have compatible Montgomery form\n");
        return result;
    }

    // Perform coefficient-wise subtraction
    for (size_t i = 0; i < PQC_LIB_N; i++)
    {
        result.coeffs[i] = PQC_LIB_subtract_mod(a->coeffs[i], b->coeffs[i]);
    }

    // Set flags
    result.NTT_Form    = true;
    result.Mont_Form   = a->Mont_Form;
    result.Nega_Cyclic = a->Nega_Cyclic && b->Nega_Cyclic;

    return result;
}

poly PQC_LIB_NTTForm_poly_mul(const poly *a, const poly *b)
{
    poly result = PQC_LIB_create_poly();

    // Input validation
    if (!a || !b)
    {
        fprintf(stderr, "Error: Null polynomial pointer in NTTForm_poly_mul\n");
        return result;
    }

    // Check if polynomials are in NTT form
    if (!a->NTT_Form || !b->NTT_Form)
    {
        fprintf(stderr, "Error: Polynomials must be in NTT form for NTTForm_poly_mul\n");
        return result;
    }

    // Check if polynomials have compatible Montgomery form
    if (a->Mont_Form != b->Mont_Form)
    {
        fprintf(stderr, "Error: Polynomials must have compatible Montgomery form\n");
        return result;
    }

    // Perform coefficient-wise multiplication
    for (size_t i = 0; i < PQC_LIB_N; i++)
    {
        result.coeffs[i] = PQC_LIB_multiply_mod(a->coeffs[i], b->coeffs[i]);
    }

    // Set flags
    result.NTT_Form    = true;
    result.Mont_Form   = a->Mont_Form;
    result.Nega_Cyclic = a->Nega_Cyclic && b->Nega_Cyclic;

    return result;
}

/**
 * @brief Multiply a matrix of polynomials with a vector of polynomials in NTT form
 *
 * Both inputs must be:
 * - In NTT form
 * - Not in Montgomery form
 * - In negacyclic form
 * Matrix columns must match vector size
 *
 * @param mat The matrix of polynomials
 * @param vec Array of polynomials representing the vector
 * @return poly* Result vector of polynomials, or NULL if error
 */
poly *PQC_LIB_matrix_vector_mul(const matrix_poly *mat, const poly *vec)
{
    // Input validation
    if (!mat || !vec || !mat->polynomial)
    {
        fprintf(stderr, "Error: Null pointer in matrix_vector_mul\n");
        return NULL;
    }

    // Check matrix dimensions
    if (mat->rows == 0 || mat->cols == 0)
    {
        fprintf(stderr, "Error: Invalid matrix dimensions\n");
        return NULL;
    }

    // Verify all matrix polynomials are in correct form
    for (size_t i = 0; i < mat->rows; i++)
    {
        for (size_t j = 0; j < mat->cols; j++)
        {
            const poly *curr = &mat->polynomial[i][j];
            if (!curr->NTT_Form || curr->Mont_Form || !curr->Nega_Cyclic)
            {
                fprintf(stderr, "Error: Matrix polynomial at [%zu][%zu] in incorrect form\n", i, j);
                return NULL;
            }
        }
    }

    // Verify all vector polynomials are in correct form
    for (size_t i = 0; i < mat->cols; i++)
    {
        if (!vec[i].NTT_Form || vec[i].Mont_Form || !vec[i].Nega_Cyclic)
        {
            fprintf(stderr, "Error: Vector polynomial at [%zu] in incorrect form\n", i);
            return NULL;
        }
    }

    // Allocate result vector
    poly *result = (poly *)malloc(mat->rows * sizeof(poly));
    if (!result)
    {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return NULL;
    }

    // Initialize result polynomials
    for (size_t i = 0; i < mat->rows; i++)
    {
        result[i]             = PQC_LIB_create_poly();
        result[i].NTT_Form    = true;
        result[i].Mont_Form   = false;
        result[i].Nega_Cyclic = true;
    }

    // Perform matrix-vector multiplication
    for (size_t i = 0; i < mat->rows; i++)
    {
        // Start with first term
        poly term = PQC_LIB_NTTForm_poly_mul(&mat->polynomial[i][0], &vec[0]);
        result[i] = term;

        // Add remaining terms
        for (size_t j = 1; j < mat->cols; j++)
        {
            term      = PQC_LIB_NTTForm_poly_mul(&mat->polynomial[i][j], &vec[j]);
            poly temp = PQC_LIB_NTTForm_poly_add(&result[i], &term);
            result[i] = temp;
        }
    }

    return result;
}