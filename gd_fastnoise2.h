#include <core/object/ref_counted.h>

#include <modules/GDFastNoise2/FastNoise2/include/FastNoise/FastNoise.h>
#include <core/variant/typed_array.h>

namespace _FastNoise = FastNoise;

class FNSimplex : public RefCounted {
    GDCLASS(FNSimplex, RefCounted)

public:
    FNSimplex();

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
    // No public default constructor
    static void _bind_methods();

private:
	_FastNoise::SmartNode<_FastNoise::Simplex> _node;
};

