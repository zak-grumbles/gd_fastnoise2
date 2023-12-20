#include <core/object/ref_counted.h>

#include "./FastNoise2/include/FastNoise/FastNoise.h"

class FNSimplex : public RefCounted {
    GDCLASS(FNSimplex, RefCounted);

public:
    FNSimplex();

protected:
    // No public default constructor
    static void _bind_methods();

private:
    FastNoise::SmartNode<FastNoise::Simplex> _node;
}

