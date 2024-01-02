#include "gd_fastnoise2.h"

FNGenerator::FNGenerator(int type) {
	_gen_type = static_cast<FNGenerator::GeneratorType>(type);
	switch(_gen_type) {
		case SIMPLEX:
		default:
			_node = _FastNoise::New<_FastNoise::Simplex>();
			break;
		case PERLIN:
			_node = _FastNoise::New<_FastNoise::Perlin>();
			break;
	}
}

FNGenerator *FNGenerator::NewGenerator(int type) {
	return new FNGenerator(type);
}

PackedFloat32Array FNGenerator::GenUniformGrid2D(
		int x_start, int y_start,
		int width, int height,
		float frequency, int seed) const {
	PackedFloat32Array output;
	output.resize_zeroed(width * height);

	_node->GenUniformGrid2D(output.ptrw(),
		x_start, y_start,
		width, height,
		frequency, seed);

	return output;
}

PackedFloat32Array FNGenerator::GenUniformGrid3D(
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

void FNGenerator::_bind_methods() {
	_bind_generator_type_enum();

	ClassDB::bind_static_method("FNGenerator", 
		D_METHOD("NewGenerator", "gen_type"),
		&FNGenerator::NewGenerator);

	ClassDB::bind_method(D_METHOD("GenUniformGrid2D",
		"x_start", "y_start", "width", "height",
		"frequency", "seed"), &FNGenerator::GenUniformGrid2D);
	ClassDB::bind_method(D_METHOD("GenUniformGrid3D",
		"x_start", "y_start", "z_start",
		"width", "height", "depth",
		"frequency", "seed"), &FNGenerator::GenUniformGrid3D);
}

void FNGenerator::_bind_generator_type_enum() {
	ClassDB::bind_integer_constant("FNGenerator", "GeneratorType", "Simplex", 0);
	ClassDB::bind_integer_constant("FNGenerator", "GeneratorType", "Perlin", 1);
}

FNModifier::FNModifier(int type) {
	_mod_type = static_cast<FNModifier::ModifierType>(type);

	switch(_mod_type) {
		case FRACTAL_FBM:
		default:
			_node = _FastNoise::New<_FastNoise::FractalFBm>();
			break;
	}
}

FNModifier *FNModifier::NewModifier(int type) {
	return new FNModifier(type);
}

void FNModifier::SetSource(FNGenerator *src) {
	switch(_mod_type) {
		case FRACTAL_FBM:
			_SetSourceFractal(src);
			break;
		default:
			break;
	}
}

void FNModifier::_bind_methods() {
	_bind_mod_type_enum();

	ClassDB::bind_static_method("FNModifier", 
		D_METHOD("NewModifier", "mod_type"),
		&FNModifier::NewModifier);

	ClassDB::bind_method(D_METHOD("SetSource", "src"), &FNModifier::SetSource);
}

void FNModifier::_bind_mod_type_enum() {
	ClassDB::bind_integer_constant("FNModifier", "ModifierType", "FractalFBm", 0);
}

void FNModifier::_SetSourceFractal(FNGenerator *src) {
	_FastNoise::SmartNode<_FastNoise::FractalFBm> frac;
	frac = _FastNoise::SmartNode<_FastNoise::FractalFBm>::DynamicCast(_node);

	frac->SetSource(src->GetSmartNode());
}
