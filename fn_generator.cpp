#include "fn_generator.h"

FNGenerator::FNGenerator(int type) {
    _set_type(type);
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

Ref<ArrayMesh> FNGenerator::gen_mesh_2D(int x_start, int y_start, int width, int height, float frequency, int seed) const {

    PackedFloat32Array noise;
    noise.resize_zeroed(width * height);

    _node->GenUniformGrid2D(noise.ptrw(),
        x_start, y_start,
        width, height,
        frequency, seed
    );


    PackedVector3Array verts;
    PackedVector2Array uvs;
    PackedVector3Array normals;
    PackedInt32Array indices;

    Array mesh_array;
    mesh_array.resize(Mesh::ARRAY_MAX);
    mesh_array[Mesh::ARRAY_VERTEX] = verts;
    mesh_array[Mesh::ARRAY_TEX_UV] = uvs;
    mesh_array[Mesh::ARRAY_NORMAL] = normals;
    mesh_array[Mesh::ARRAY_INDEX] = indices;

    Ref<ArrayMesh> mesh;
    mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, mesh_array);
	return mesh;
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

int FNGenerator::get_type() const {
    return static_cast<int>(_gen_type);
}

void FNGenerator::_set_type(int type) {
    _gen_type = static_cast<FNGenerator::GeneratorType>(type);
    _init_node();
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

    ClassDB::bind_method(
        D_METHOD("get_type"),
        &FNGenerator::get_type
    );
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
        "Value", static_cast<int64_t>(GeneratorType::Value)
    );
}

void FNGenerator::_init_node() {
    if(_node) {
        _node.reset();
    }

    switch(_gen_type) {
        case Simplex:
        default:
            _node = _FastNoise::New<_FastNoise::Simplex>();
            break;
        case Perlin:
            _node = _FastNoise::New<_FastNoise::Perlin>();
            break;
        case Value:
            _node = _FastNoise::New<_FastNoise::Value>();
            break;
    }
}