#include <core/object/ref_counted.h>

#include <modules/GDFastNoise2/FastNoise2/include/FastNoise/FastNoise.h>
#include <core/variant/typed_array.h>

namespace _FastNoise = FastNoise;

class FNGenerator : public RefCounted {
	GDCLASS(FNGenerator, RefCounted)

public:
	enum GeneratorType {
		SIMPLEX = 0,
		PERLIN,
		FRACTAL
	};

	FNGenerator() = default;

	static FNGenerator* New(int type);

	PackedFloat32Array GenUniformGrid2D(
		int x_start, int y_start,
		int width, int height,
		float frequency = 0.2f, int seed = 1337
	) const;

	PackedFloat32Array GenUniformGrid3D(
		int x_start, int y_start, int z_start,
		int width, int height, int depth,
		float frequency = 0.2f, int seed = 1337
	) const;

protected:
	FNGenerator(int type);
    static void _bind_methods();
	GeneratorType _gen_type;

private:
	_FastNoise::SmartNode<_FastNoise::Generator> _node;
};