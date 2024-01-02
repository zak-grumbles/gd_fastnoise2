#ifndef GDFastNoise2_GDFASTNOISE2_H
#define GDFastNoise2_GDFASTNOISE2_H

#include <core/io/image.h>
#include <core/object/ref_counted.h>
#include <core/variant/typed_array.h>
#include <modules/GDFastNoise2/FastNoise2/include/FastNoise/FastNoise.h>

namespace _FastNoise = FastNoise;

class FNGenerator : public RefCounted {
	GDCLASS(FNGenerator, RefCounted)

public:
	enum GeneratorType {
		SIMPLEX = 0,
		PERLIN
	};

	FNGenerator(int type);

	static FNGenerator* NewGenerator(int type);

	PackedFloat32Array GenUniformGrid2D(
		int x_start, int y_start,
		int width, int height,
		float frequency = 0.2f, int seed = 1337
	) const;

    Ref<Image> GenUniform2DImage(
        int x_start, int y_start,
        int width, int height,
        float frequency = 0.2f, int seed = 1337
    ) const;

	PackedFloat32Array GenUniformGrid3D(
		int x_start, int y_start, int z_start,
		int width, int height, int depth,
		float frequency = 0.2f, int seed = 1337
	) const;

	_FastNoise::SmartNode<_FastNoise::Generator> GetSmartNode() const { return _node; }

protected:
	FNGenerator() = default;
    static void _bind_methods();
	static void _bind_generator_type_enum();

	GeneratorType _gen_type;
	_FastNoise::SmartNode<_FastNoise::Generator> _node;
};

class FNModifier : public FNGenerator {
	GDCLASS(FNModifier, FNGenerator)

public:
	enum ModifierType {
		FRACTAL_FBM = 0
	};

	FNModifier(int type);

	static FNModifier* NewModifier(int type);

	void SetSource(FNGenerator* src);

protected:
	FNModifier() = default;
	static void _bind_methods();
	static void _bind_mod_type_enum();

	void _SetSourceFractal(FNGenerator* src);

	ModifierType _mod_type;
};

#endif