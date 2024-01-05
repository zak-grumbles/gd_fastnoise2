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

#endif