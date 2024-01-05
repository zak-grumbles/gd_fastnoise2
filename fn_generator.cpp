#include "fn_generator.h"

FNGenerator::FNGenerator(int type) {
    _gen_type = static_cast<FNGenerator::GeneratorType>(type);
    switch(_gen_type) {
        case Simplex:
        default:
            _node = _FastNoise::New<_FastNoise::Simplex>();
            break;
        case Perlin:
            _node = _FastNoise::New<_FastNoise::Perlin>();
            break;
        case CellularValue:
            _node = _FastNoise::New<_FastNoise::CellularValue>();
            break;
        case CellularDistance:
            _node = _FastNoise::New<_FastNoise::CellularDistance>();
            break;
        case CellularLookup:
            _node = _FastNoise::New<_FastNoise::CellularLookup>();
            break;
        case Value:
            _node = _FastNoise::New<_FastNoise::Value>();
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
    ClassDB::bind_integer_constant(
        "FNGenerator", "GeneratorType",
        "Simplex",static_cast<int64_t>(GeneratorType::Simplex)
    );
    ClassDB::bind_integer_constant(
        "FNGenerator", "GeneratorType",
        "Perlin", static_cast<int64_t>(GeneratorType::Perlin)
    );
    ClassDB::bind_integer_constant(
        "FNGenerator", "GeneratorType",
        "CellularValue", static_cast<int64_t>(GeneratorType::CellularValue)
    );
    ClassDB::bind_integer_constant(
        "FNGenerator", "GeneratorType",
        "CellularDistance", static_cast<int64_t>(GeneratorType::CellularDistance)
    );
    ClassDB::bind_integer_constant(
        "FNGenerator", "GeneratorType",
        "CellularLookup", static_cast<int64_t>(GeneratorType::CellularLookup)
    );
    ClassDB::bind_integer_constant(
        "FNGenerator", "GeneratorType",
        "Value", static_cast<int64_t>(GeneratorType::Value)
    );
}