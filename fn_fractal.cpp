#include "fn_fractal.h"

FNFractal::FNFractal(FractalType type) {
    _frac_type = type;

    switch(_frac_type) {
        case FractalType::FBm:
        default:
            _frac_node = _FastNoise::New<_FastNoise::FractalFBm>();
            break;
    }
}

FNFractal *FNFractal::new_fractal(int type) {
    FractalType frac_type = static_cast<FractalType>(type);
    return new FNFractal(frac_type);
}

void FNFractal::set_source(FNGenerator *src) {
    _frac_node->SetSource(src->_get_smart_node());
}

void FNFractal::_bind_methods() {
    _bind_frac_type_enum();

    ClassDB::bind_static_method("FNFractal", 
        D_METHOD("new_fractal", "type"),
        &FNFractal::new_fractal);

    ClassDB::bind_method(D_METHOD("set_source", "src"),
        &FNFractal::set_source);
    ClassDB::bind_method(D_METHOD("set_gain", "value"),
        &FNFractal::set_gain);
    ClassDB::bind_method(D_METHOD("set_weighted_strength", "value"),
        &FNFractal::set_weighted_strength);
    ClassDB::bind_method(D_METHOD("set_octave_count", "value"),
        &FNFractal::set_octave_count);
    ClassDB::bind_method(D_METHOD("set_lacunarity", "value"),
        &FNFractal::set_lacunarity);
}

void FNFractal::_bind_frac_type_enum() {
    ClassDB::bind_integer_constant("FNFractal", "FractalType", "FBm", 0);
    ClassDB::bind_integer_constant("FNFractal", "FractalType", "Ridged", 1);
    ClassDB::bind_integer_constant("FNFractal", "FractalType", "PingPong", 2);
}