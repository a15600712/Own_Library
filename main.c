#include "libs/poly.h"
#include "libs/zetas.h"

int main()
{
    matrix_poly mat                = create_matrix(PQC_LIB_MATRIX_K, PQC_LIB_MATRIX_K);
    mat.polynomial[0][0].coeffs[0] = 42;
    mat.polynomial[0][0].coeffs[1] = 2;
    mat.polynomial[1][0].coeffs[3] = 5;
    print_matrix(&mat);
    free_matrix(&mat);
    return 0;
}
