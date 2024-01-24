#ifndef gd_fastnoise2_FNDOMAINWARP_H
#define gd_fastnoise2_FNDOMAINWARP_H

#include "fn_generator.h"

namespace _FastNoise = FastNoise;

class FNDomainWarp : public FNGenerator {
    GDCLASS(FNDomainWarp, FNGenerator)

public:
    FNDomainWarp() = default;

    void set_source(FNGenerator* gen) { _node->SetSource(gen->_get_smart_node()); }
    void set_warp_amplitude(FNGenerator* gen) {
        _node->SetWarpAmplitude(gen->_get_smart_node());
    }
    void set_warp_amplitude_val(float value) { _node->SetWarpAmplitude(value); }
    void set_warp_frequency(float value) { _node->SetWarpFrequency(value); }

protected:
    static void _bind_methods();

    _FastNoise::SmartNode<_FastNoise::DomainWarp> _node;
};

class FNDomainWarpGradient : public FNDomainWarp {
    GDCLASS(FNDomainWarpGradient, FNDomainWarp)

public:
    FNDomainWarpGradient();
};

#endif