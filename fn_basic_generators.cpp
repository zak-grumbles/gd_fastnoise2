#include "fn_basic_generators.h"

FNConstant::FNConstant() {
    _node = _FastNoise::New<_FastNoise::Constant>();
}

void FNConstant::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_value", "value"),
        &FNConstant::set_value
    );
}

FNWhite::FNWhite() {
    _node = _FastNoise::New<_FastNoise::White>();
}

void FNWhite::_bind_methods() {
    // No methods to bind
}

FNCheckerboard::FNCheckerboard() {
    _node = _FastNoise::New<_FastNoise::Checkerboard>();
}

void FNCheckerboard::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_size", "size"),
        &FNCheckerboard::set_size
    );
}

FNSineWave::FNSineWave() {
    _node = _FastNoise::New<_FastNoise::SineWave>();
}

void FNSineWave::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_scale", "value"),
        &FNSineWave::set_scale
    );
}
