#ifndef gd_fastnoise2_FNFRACTAL_H
#define gd_fastnoise2_FNFRACTAL_H

#include "fn_generator.h"

namespace _FastNoise = FastNoise;

class FNFractal : public FNGenerator {
	GDCLASS(FNFractal, FNGenerator)

public:
	enum FractalType {
		FBm = 0,
		Ridged,
		PingPong
	};

	FNFractal(FractalType type);

	static FNFractal* new_fractal(int type);

	void set_source(FNGenerator* src);
	void set_gain(float value) const { _frac_node->SetGain(value); }
	void set_weighted_strength(float value) const { _frac_node->SetWeightedStrength(value); }
	void set_octave_count(int value) const { _frac_node->SetOctaveCount(value); }
	void set_lacunarity(float value) const { _frac_node->SetLacunarity(value); }

	_FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
		 return _frac_node; 
	}

protected:
	FNFractal() = default;

	static void _bind_methods();
	static void _bind_frac_type_enum();

	FractalType _frac_type = FractalType::FBm;

private:
	_FastNoise::SmartNode<_FastNoise::Fractal<>> _frac_node;
};

class FNFBmFractal : public FNFractal {
	GDCLASS(FNFBmFractal, FNFractal)

public:
	FNFBmFractal() : FNFractal(FractalType::FBm) {}
};

class FNRidgedFractal : public FNFractal {
	GDCLASS(FNRidgedFractal, FNFractal)

public:
	FNRidgedFractal() : FNFractal(FractalType::Ridged) {}
};

class FNPingPongFractal : public FNFractal {
	GDCLASS(FNPingPongFractal, FNFractal)

public:
	FNPingPongFractal() : FNFractal(FractalType::PingPong) {}
};

#endif