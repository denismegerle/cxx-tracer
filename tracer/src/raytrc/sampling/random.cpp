#include "random.h"

#include <stdlib.h>

using namespace raytrc;

double raytrc::random_double() { return rand() / (RAND_MAX + 1.0); }
