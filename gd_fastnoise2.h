#ifndef gd_fastnoise2_GDFASTNOISE2_H
#define gd_fastnoise2_GDFASTNOISE2_H

#include <core/io/image.h>
#include <core/object/ref_counted.h>
#include <core/variant/typed_array.h>
#include "FastNoise2/include/FastNoise/FastNoise.h"
#include "FastNoise2/include/FastNoise/Generators/Fractal.h"

namespace _FastNoise = FastNoise;

class FNGenerator : public RefCounted {
	GDCLASS(FNGenerator, RefCounted)

public:
	enum GeneratorType {
		SIMPLEX = 0,
		PERLIN
	};

	FNGenerator(int type);

	static FNGenerator* new_generator(int type);

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

	PackedFloat32Array gen_uniform_grid_3D(
		int x_start, int y_start, int z_start,
		int width, int height, int depth,
		float frequency = 0.2f, int seed = 1337
	) const;

	virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const {
		 return _node; 
	}

protected:
	FNGenerator() = default;
    static void _bind_methods();
	static void _bind_generator_type_enum();

	GeneratorType _gen_type;

private:
	_FastNoise::SmartNode<_FastNoise::Generator> _node;
};

class FNFractal : public FNGenerator {
	GDCLASS(FNFractal, FNGenerator)

public:
	enum FractalType {
		FBm = 0,
		Ridged,
		PingPong
	};

	FNFractal(FractalType type);

	static FNFractal* new_fractal(int type);

	void set_source(FNGenerator* src);

	_FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
		 return _frac_node; 
	}

protected:
	FNFractal() = default;

	static void _bind_methods();
	static void _bind_frac_type_enum();

	FractalType _frac_type = FractalType::FBm;

private:
	_FastNoise::SmartNode<_FastNoise::Fractal<>> _frac_node;
};

#endif
