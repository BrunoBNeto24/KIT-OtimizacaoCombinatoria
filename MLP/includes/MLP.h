#ifndef MLP_H
#define MLP_H

#include "Data.h"
#include "construction.h"
#include "buscaLocal.h"
#include "perturbacao.h"

Solution MLP(int maxIter, int maxIterIls, Data data);

#endif