#ifndef gd_fastnoise2_FNGENERATOR_H
#define gd_fastnoise2_FNGENERATOR_H

#include <core/io/image.h>
#include <core/object/ref_counted.h>
#include <core/variant/typed_array.h>
#include <scene/resources/mesh.h>

#include "FastNoise2/include/FastNoise/FastNoise.h"

namespace _FastNoise = FastNoise;

class FNGenerator : public RefCounted {
    GDCLASS(FNGenerator, RefCounted)

public:
    enum GeneratorType {
        Simplex = 0,
        Perlin,
        Value
    };

    FNGenerator(int type);

    PackedFloat32Array gen_uniform_grid_2D(
        int x_start, int y_start,
        int width, int height,
        float frequency = 0.2f, int seed = 1337
    ) const;

    Ref<Image> gen_uniform_2D_image(
        int x_start, int y_start,
        int width, int height,
        float frequency = 0.2f, int seed = 1337
    ) const;

    Ref<ArrayMesh> gen_mesh_2D(
        int x_start, int y_start,
        int width, int height,
        float frequency = 0.2f, int seed = 1337
    ) const;

    PackedFloat32Array gen_uniform_grid_3D(
        int x_start, int y_start, int z_start,
        int width, int height, int depth,
        float frequency = 0.2f, int seed = 1337
    ) const;

    int get_type() const;

    virtual String encode_generator_tree() const;
    virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const { return _node; }

protected:
    FNGenerator() = default;
    static void _bind_methods();
    static void _bind_generator_type_enum();


    void _set_type(int type);

    GeneratorType _gen_type;
    _FastNoise::SmartNode<_FastNoise::Generator> _node;
};

class FNSimplexGenerator : public FNGenerator {
    GDCLASS(FNSimplexGenerator, FNGenerator)

public:
    FNSimplexGenerator();
};

class FNPerlinGenerator : public FNGenerator {
    GDCLASS(FNPerlinGenerator, FNGenerator)

public:
    FNPerlinGenerator();
};

class FNValueGenerator : public FNGenerator {
    GDCLASS(FNValueGenerator, FNGenerator)

public:
    FNValueGenerator();
};

#endif