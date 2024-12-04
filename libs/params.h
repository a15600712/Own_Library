// params.h
#ifndef PARAMS_H
#define PARAMS_H

#include "math.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

// Ring dimension
#define N 256

// Modulus
#define Q 8380417

// Useful derived constants
#define LOG2_N log2(N) // log2(256)

// Helper macros
// #define REDUCE(x) ((x) < Q ? (x) : (x) - Q) // Reduction modulo Q
// #define CADDQ(x) ((x) < 0 ? (x) + Q : (x))  // Centered reduction

#endif // PARAMS_H