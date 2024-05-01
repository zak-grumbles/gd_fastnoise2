#include "fn_generator.h"

#include <FastNoise/Metadata.h>

FNGenerator::FNGenerator(int type) {
    _set_type(type);
}

PackedFloat32Array FNGenerator::gen_uniform_grid_2D(
        int x_start, int y_start,
        int width, int height,
        float frequency, int seed) const {
    PackedFloat32Array output;
    output.resize_zeroed(width * height);

    _get_smart_node()->GenUniformGrid2D(output.ptrw(),
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

    _get_smart_node()->GenUniformGrid2D(noise.ptrw(),
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

    _get_smart_node()->GenUniformGrid3D(noise_output.ptrw(),
        x_start, y_start, z_start,
        width, height, depth,
        frequency, seed);

    return noise_output;
}

int FNGenerator::get_type() const {
    return static_cast<int>(_gen_type);
}

String FNGenerator::encode_generator_tree() const {
    std::unique_ptr<_FastNoise::NodeData> data = std::make_unique<_FastNoise::NodeData>(
        &(_get_smart_node()->GetMetadata())
    );
    std::string serialised = _FastNoise::Metadata::SerialiseNodeData(data.get(), true);
	return String(serialised.c_str());
}

void FNGenerator::_set_type(int type) {
    _gen_type = static_cast<FNGenerator::GeneratorType>(type);
}

void FNGenerator::_bind_methods() {
    _bind_generator_type_enum();

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

    ClassDB::bind_method(
        D_METHOD("encode_generator_tree"),
        &FNGenerator::encode_generator_tree
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

FNSimplexGenerator::FNSimplexGenerator() : FNGenerator(GeneratorType::Simplex) {
    _node = _FastNoise::New<_FastNoise::Simplex>();
}

FNPerlinGenerator::FNPerlinGenerator() : FNGenerator(GeneratorType::Perlin) {
    _node = _FastNoise::New<_FastNoise::Perlin>();
}

FNValueGenerator::FNValueGenerator() : FNGenerator(GeneratorType::Value) {
    _node = _FastNoise::New<_FastNoise::Value>();
}
