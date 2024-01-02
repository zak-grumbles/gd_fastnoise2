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

FNGenerator *FNGenerator::new_generator(int type) {
	return new FNGenerator(type);
}

PackedFloat32Array FNGenerator::gen_uniform_grid_2D(
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

Ref<Image> FNGenerator::gen_uniform_2D_image(
    int x_start, int y_start,
    int width, int height,
    float frequency, int seed
) const {

    auto gen_rgba8 = _FastNoise::New<_FastNoise::ConvertRGBA8>(_node->GetSIMDLevel());
    gen_rgba8->SetSource(_node);
    
    PackedFloat32Array data;
    data.resize_zeroed(width * height);
    gen_rgba8->GenUniformGrid2D(data.ptrw(),
        x_start, y_start,
        width, height,
        frequency, seed
    );

    Ref<Image> img = Image::create_from_data(width, height,
        false, Image::Format::FORMAT_RGBA8,
        data.to_byte_array());

    return img;
}

PackedFloat32Array FNGenerator::gen_uniform_grid_3D(
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
		D_METHOD("new_generator", "gen_type"),
		&FNGenerator::new_generator);

	ClassDB::bind_method(D_METHOD("gen_uniform_grid_2D",
		"x_start", "y_start", "width", "height",
		"frequency", "seed"), &FNGenerator::gen_uniform_grid_2D);
    ClassDB::bind_method(D_METHOD("gen_uniform_2D_image",
        "x_start", "y_start", "width", "height",
        "frequency", "seed"), &FNGenerator::gen_uniform_2D_image);

	ClassDB::bind_method(D_METHOD("gen_uniform_grid_3D",
		"x_start", "y_start", "z_start",
		"width", "height", "depth",
		"frequency", "seed"), &FNGenerator::gen_uniform_grid_3D);
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

FNModifier *FNModifier::new_modifier(int type) {
	return new FNModifier(type);
}

void FNModifier::set_source(FNGenerator *src) {
	switch(_mod_type) {
		case FRACTAL_FBM:
			_set_source_fractal(src);
			break;
		default:
			break;
	}
}

void FNModifier::_bind_methods() {
	_bind_mod_type_enum();

	ClassDB::bind_static_method("FNModifier", 
		D_METHOD("new_modifier", "mod_type"),
		&FNModifier::new_modifier);

	ClassDB::bind_method(D_METHOD("set_source", "src"), &FNModifier::set_source);
}

void FNModifier::_bind_mod_type_enum() {
	ClassDB::bind_integer_constant("FNModifier", "ModifierType", "FractalFBm", 0);
}

void FNModifier::_set_source_fractal(FNGenerator *src) {
	_FastNoise::SmartNode<_FastNoise::FractalFBm> frac;
	frac = _FastNoise::SmartNode<_FastNoise::FractalFBm>::DynamicCast(_node);

	frac->SetSource(src->_get_smart_node());
}
