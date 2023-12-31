#include "gd_fastnoise2.h"

FNSimplex::FNSimplex() {
	_node = FastNoise::New<FastNoise::Simplex>();
}

PackedFloat32Array FNSimplex::GenUniformGrid2D(
	int x_start, int y_start,
	int width, int height,
	float frequency /*= 0.2f*/,
	int seed /*= 1337*/) const {


	PackedFloat32Array noise_output;
	noise_output.resize_zeroed(width * height);

	_node->GenUniformGrid2D(noise_output.ptrw(),
		x_start, y_start,
		width, height,
		frequency, seed);

	return noise_output;
}

PackedFloat32Array FNSimplex::GenUniformGrid3D(
	int x_start, int y_start, int z_start,
	int width, int height, int depth,
	float frequency, int seed) const {

	PackedFloat32Array noise_output;
	noise_output.resize_zeroed(width * height * depth);

	_node->GenUniformGrid3D(noise_output.ptrw(),
		x_start, y_start, z_start,
		width, height, depth,
		frequency, seed);

	return noise_output;
}


void FNSimplex::_bind_methods() {
	ClassDB::bind_method(D_METHOD("GenUniformGrid2D",
		"x_start", "y_start", "width", "height",
		"frequency", "seed"), &FNSimplex::GenUniformGrid2D);
	ClassDB::bind_method(D_METHOD("GenUniformGrid3D",
		"x_start", "y_start", "z_start",
		"width", "height", "depth",
		"frequency", "seed"), &FNSimplex::GenUniformGrid3D);
}
