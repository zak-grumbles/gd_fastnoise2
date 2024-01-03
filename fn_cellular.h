#ifndef gd_fastnoise2_FNCELLULAR_H
#define gd_fastnoise2_FNCELLULAR_H

#include "fn_generator.h"

namespace _FastNoise = FastNoise;

class FNCellular : public FNGenerator {
	GDCLASS(FNCellular, FNGenerator)

public:
    enum CellularType {
        Cellular = 0,
        CellularValue,
        CellularDistance,
        CellularLookup,
    };

    FNCellular() = default;

    void set_jitter_modifier(float value) { _cell_node->SetJitterModifier(value); }
    void set_distance_func(int value);

	_FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
		 return _cell_node; 
	}

protected:

    static void _bind_methods();
    static void _bind_cellular_type_enum();
    static void _bind_distance_func_enum();

    CellularType _cell_type = CellularType::Cellular;
    _FastNoise::SmartNode<_FastNoise::Cellular> _cell_node;
};

class FNCellularValue : public FNCellular {
    GDCLASS(FNCellularValue, FNCellular)

public:
    FNCellularValue();

    void set_value_index(int value);

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::CellularValue> _casted_node;
};

class FNCellularDistance : public FNCellular {
    GDCLASS(FNCellularDistance, FNCellular)

public:
    FNCellularDistance();

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::CellularDistance> _casted_node;
};

#endif