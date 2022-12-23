#ifndef __EFFECTIVE_H__

#define __EFFECTIVE_H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../inc/errors.h"
#include "../inc/matrix.h"
#include "../inc/sparse_matrix.h"

#define N_REPS 1

char t_matrix_sparse_mupltiplication(sparse_matrix_t *sparse_matrix_vector, sparse_matrix_t *t_sparse_matrix, sparse_matrix_t *sparse_matrix_result);
char get_effective(void);

#endif //#ifndef __EFFECTIVE_H__
