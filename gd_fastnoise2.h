#include <core/object/ref_counted.h>

#include <modules/GDFastNoise2/FastNoise2/include/FastNoise/FastNoise.h>

namespace _FastNoise = FastNoise;

class FNSimplex : public RefCounted {
    GDCLASS(FNSimplex, RefCounted)

public:
    FNSimplex();

protected:
    // No public default constructor
    static void _bind_methods();

private:
	_FastNoise::SmartNode<_FastNoise::Simplex> _node;
};

