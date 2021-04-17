#include "random.h"

#include <stdlib.h>

double raytrc::random_double() { return rand() / (RAND_MAX + 1.0); }
