#ifndef gd_fastnoise2_FNMODIFIERS_H
#define gd_fastnoise2_FNMODIFIERS_H

#include "fn_generator.h"

class FNDomainScale : public FNGenerator {
    GDCLASS(FNDomainScale, FNGenerator)

public:
    FNDomainScale();

    void set_source(FNGenerator* gen) { _node->SetSource(gen->_get_smart_node()); }
    void set_scale(float value) { _node->SetScale(value); }

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::DomainScale> _node;
};

class FNDomainOffset : public FNGenerator {
    GDCLASS(FNDomainOffset, FNGenerator)

public:
    FNDomainOffset();

    void set_source(FNGenerator* gen) { _node->SetSource(gen->_get_smart_node()); }

    void set_x_offset_val(float value) { _node->SetOffset<_FastNoise::Dim::X>(value); }
    void set_y_offset_val(float value) { _node->SetOffset<_FastNoise::Dim::Y>(value); }
    void set_z_offset_val(float value) { _node->SetOffset<_FastNoise::Dim::Z>(value); }
    void set_w_offset_val(float value) { _node->SetOffset<_FastNoise::Dim::W>(value); }

    void set_x_offset(FNGenerator* gen) { _node->SetOffset<_FastNoise::Dim::X>(gen->_get_smart_node()); }
    void set_y_offset(FNGenerator* gen) { _node->SetOffset<_FastNoise::Dim::Y>(gen->_get_smart_node()); }
    void set_z_offset(FNGenerator* gen) { _node->SetOffset<_FastNoise::Dim::Z>(gen->_get_smart_node()); }
    void set_w_offset(FNGenerator* gen) { _node->SetOffset<_FastNoise::Dim::W>(gen->_get_smart_node()); }

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::DomainOffset> _node;
};

#endif