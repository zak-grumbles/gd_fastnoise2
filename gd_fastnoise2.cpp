#include "gd_fastnoise2_simplex.h"

#include <FastNoise2/include/FastNoise/FastNoise.h>

FNSimplex::FNSimplex() {
    _node = _FastNoise::New<_FastNoise::Simplex>();
}

void FNSimplex::_bind_methods() {
}
