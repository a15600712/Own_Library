# Own_Library

## Overview
The **Own_Library** is a specialized library for cryptographic applications, focusing on efficient polynomial arithmetic, modular operations, and Number Theoretic Transform (NTT) computations. It provides foundational tools for implementing cryptographic protocols, particularly in post-quantum cryptography.

## Features
- **Polynomial Operations**: Efficient operations including addition, subtraction, multiplication, and conversions between standard and NTT forms.
- **Modular Arithmetic**: Optimized modular addition, subtraction, multiplication, and inversion, with centered reductions.
- **Matrix Support**: Tools for creating, printing, and performing matrix-vector multiplications with polynomials.
- **NTT Operations**: Forward and inverse NTT implementations for polynomial transformations.
- **Zeta Computations**: Automatic generation of zeta tables and related operations for NTT.

## Key Components
- **Modular Arithmetic**:
  - Functions for modular addition, subtraction, multiplication, division, and inversion.
  - Centered reduction to ensure values remain in a symmetric range.
- **Polynomial Arithmetic**:
  - Creation and manipulation of polynomials, including support for NTT and Montgomery forms.
  - Operations on matrices of polynomials.
- **NTT Support**:
  - Transform polynomials to/from NTT form for efficient convolution.
- **Zeta Value Utilities**:
  - Computation of zeta values for NTT and generation of bit-reversed zeta tables.

## File Structure
- `arithmetic.c` / `arithmetic.h`: Modular arithmetic operations.
- `poly.c` / `poly.h`: Polynomial creation, manipulation, and matrix operations.
- `ntt.c` / `ntt.h`: Forward and inverse NTT transformations.
- `zetas.c` / `zetas.h`: Zeta value computation for NTT operations.
- `params.h`: Library-wide parameters (e.g., modulus `PQC_LIB_Q` and dimension `PQC_LIB_N`).
- `main.c`: Demonstrates matrix-vector multiplication and NTT transformations.

## Dependencies
- Standard libraries: `<stdio.h>`, `<stdlib.h>`, `<stdint.h>`, `<stdbool.h>`, `<math.h>`.

## Usage Example
The library provides utilities for cryptographic operations, demonstrated in `main.c`. Example steps:
1. Create a matrix of polynomials and a polynomial vector.
2. Transform both into NTT form using the generated zeta values.
3. Perform matrix-vector multiplication in NTT form.
4. Transform the result back to standard form.

## Build Instructions
```bash
mkdir build
cd build
cmake ..
make
