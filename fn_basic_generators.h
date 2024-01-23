#ifndef gd_fastnoise2_BASICGENERATORS_H
#define gd_fastnoise2_BASICGENERATORS_H

#include <FastNoise/Generators/BasicGenerators.h>

#include "fn_generator.h"

namespace _FastNoise = FastNoise;

class FNConstant : public FNGenerator {
    GDCLASS(FNConstant, FNGenerator)

public:
    FNConstant();

    void set_value(float value) { _node->SetValue(value); }

    virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
        return _node;
    }

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::Constant> _node;
};

class FNWhite : public FNGenerator {
    GDCLASS(FNWhite, FNGenerator)

public:
    FNWhite();

	virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
		return _node;
	}

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::White> _node;
};

class FNCheckerboard : public FNGenerator {
    GDCLASS(FNCheckerboard, FNGenerator)

public:
    FNCheckerboard();

    void set_size(float value) { _node->SetSize(value); }

	virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
		return _node;
	}

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::Checkerboard> _node;
};

class FNSineWave : public FNGenerator {
    GDCLASS(FNSineWave, FNGenerator)

public:
    FNSineWave();

    void set_scale(float value) { _node->SetScale(value); }

	virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
		return _node;
	}

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::SineWave> _node;
};

class FNPositionOutput : public FNGenerator {
    GDCLASS(FNPositionOutput, FNGenerator)

public:
    FNPositionOutput();

    void set_x(float multiplier, float offset = 0.0f) { 
        _node->Set<_FastNoise::Dim::X>(multiplier, offset); 
    }

    void set_y(float multiplier, float offset = 0.0f) {
        _node->Set<_FastNoise::Dim::Y>(multiplier, offset);
    }

    void set_z(float multiplier, float offset = 0.0f) {
        _node->Set<_FastNoise::Dim::Z>(multiplier, offset);
    }

    void set_w(float multiplier, float offset = 0.0f) {
        _node->Set<_FastNoise::Dim::W>(multiplier, offset);
    }

	virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
		return _node;
	}

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::PositionOutput> _node;
};

class FNDistanceToPoint : public FNGenerator {
    GDCLASS(FNDistanceToPoint, FNGenerator)

public:
    FNDistanceToPoint();

    void set_source(FNGenerator *gen) { _node->SetSource(gen->_get_smart_node()); }
    void set_distance_function(int64_t func);

    void set_x_scale(float value) { _node->SetScale<_FastNoise::Dim::X>(value); }
    void set_y_scale(float value) { _node->SetScale<_FastNoise::Dim::Y>(value); }
    void set_z_scale(float value) { _node->SetScale<_FastNoise::Dim::Z>(value); }
    void set_w_scale(float value) { _node->SetScale<_FastNoise::Dim::W>(value); }

	virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
		return _node;
	}

protected:
    static void _bind_methods();

private:
    _FastNoise::SmartNode<_FastNoise::DistanceToPoint> _node;
};

#endif