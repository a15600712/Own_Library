// exp_mod.h
#ifndef EXP_MOD_H
#define EXP_MOD_H

#include "params.h"

#define exp_mod PQC_LIB_NAMESPACE(exp_mod)
// Function declaration
int64_t exp_mod(int64_t base, int64_t exp);

#endif  // EXP_MOD_H