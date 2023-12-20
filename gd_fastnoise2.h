#ifndef GODOT_FASTNOISE2_H
#define GODOT_FASTNOISE2_H

#include "core/object/ref_counted.h"

#include "FastNoise2/include/FastNoise/FastNoise.h"

namespace _FastNoise = FastNoise;

class FNSimplex : public RefCounted {
    GDCLASS(FNSimplex, RefCounted);
    OBJ_SAVE_TYPE(FNSimplex);

public:
    FNSimplex();

protected:
    // No public default constructor
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::Simplex> _node;
}

#endif