#include "gd_fastnoise2.h"

FNSimplex::FNSimplex() {
	_node = FastNoise::New<FastNoise::Simplex>();
}

PackedFloat32Array FNSimplex::GenUniformGrid2D(
	int x_start, int y_start,
	int width, int height,
	float frequency /*= 0.2f*/,
	int seed /*= 1337*/) {

	PackedFloat32Array noise_output;
	noise_output.resize_zeroed(width * height);

	_node->GenUniformGrid2D(noise_output.ptrw(),
		x_start, y_start,
		width, height,
		frequency, seed);

	return noise_output;
}

void FNSimplex::_bind_methods() {
	ClassDB::bind_method(D_METHOD("GenUniformGrid2D",
		"x_start", "y_start", "width", "height",
		"frequency", "seed"), &FNSimplex::GenUniformGrid2D);
}
