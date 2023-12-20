#include "gd_fastnoise2.h"

FNSimplex::FNSimplex() {
	_node = FastNoise::New<FastNoise::Simplex>();
}

void FNSimplex::_bind_methods() {
}
