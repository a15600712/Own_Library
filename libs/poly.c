#include <poly.h>

poly create_poly()
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

matrix_poly init_matrix_poly()
{
    matrix_poly mat;
    mat.polynomial = NULL;
    mat.rows       = 0;
    mat.cols       = 0;
    return mat;
}

matrix_poly create_matrix(size_t rows, size_t cols)
{
    matrix_poly mat = init_matrix_poly();
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

        // Initialize each polynomial using create_poly
        for (size_t j = 0; j < cols; ++j)
        {
            mat.polynomial[i][j] = create_poly();
        }
    }

    return mat;
}

void print_poly(const poly *p)
{
    if (p == NULL)
    {
        printf("NULL polynomial\n");
        return;
    }
    printf("Polynomial: ");
    printf("NTT_Form: %d, Mont_Form: %d, Nega_Cyclic: %d\n", p->NTT_Form, p->Mont_Form, p->Nega_Cyclic);
    for (size_t i = 0; i < PQC_LIB_N; ++i)
    {
        if (p->coeffs[i] != 0)
        {
            printf("%ld", p->coeffs[i]);
            if (i > 0)
                printf("*X^%zu", i);
            if (i < PQC_LIB_N - 1 && (p->coeffs[i + 1] != 0))
                printf(" + ");
        }
    }
    printf("\n");
}

void print_matrix(const matrix_poly *mat)
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
            print_poly(&mat->polynomial[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(matrix_poly *mat)
{
    if (mat == NULL || mat->polynomial == NULL)
    {
        return;
    }

    // Free each row
    for (size_t i = 0; i < mat->rows; ++i)
    {
        free(mat->polynomial[i]);
    }

    // Free the row pointers
    free(mat->polynomial);

    // Reset the structure
    mat->polynomial = NULL;
    mat->rows = mat->cols = 0;
}
