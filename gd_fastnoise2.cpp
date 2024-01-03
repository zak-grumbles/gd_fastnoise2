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

	auto src_node = _get_smart_node();

	_FastNoise::SmartNode<_FastNoise::ConvertRGBA8> gen_rgba8;
    gen_rgba8 = _FastNoise::New<_FastNoise::ConvertRGBA8>(src_node->GetSIMDLevel());
	gen_rgba8->SetSource(src_node);
    
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

FNFractal::FNFractal(FractalType type) {
	_frac_type = type;

	switch(_frac_type) {
		case FractalType::FBm:
		default:
			_frac_node = _FastNoise::New<_FastNoise::FractalFBm>();
			break;
	}
}

FNFractal *FNFractal::new_fractal(int type) {
	FractalType frac_type = static_cast<FractalType>(type);
	return new FNFractal(frac_type);
}

void FNFractal::set_source(FNGenerator *src) {
	_frac_node->SetSource(src->_get_smart_node());
}

void FNFractal::_bind_methods() {
	_bind_frac_type_enum();

	ClassDB::bind_static_method("FNFractal", 
		D_METHOD("new_fractal", "type"),
		&FNFractal::new_fractal);

	ClassDB::bind_method(D_METHOD("set_source", "src"),
		&FNFractal::set_source);
}

void FNFractal::_bind_frac_type_enum() {
	ClassDB::bind_integer_constant("FNFractal", "FractalType", "FBm", 0);
	ClassDB::bind_integer_constant("FNFractal", "FractalType", "Ridged", 1);
	ClassDB::bind_integer_constant("FNFractal", "FractalType", "PingPong", 2);
}
