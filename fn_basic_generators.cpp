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

FNPositionOutput::FNPositionOutput() {
    _node = _FastNoise::New<_FastNoise::PositionOutput>();
}

void FNPositionOutput::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_x", "multiplier", "offset"),
        &FNPositionOutput::set_x
    );
    ClassDB::bind_method(
        D_METHOD("set_y", "multiplier", "offset"),
        &FNPositionOutput::set_y
    );
    ClassDB::bind_method(
        D_METHOD("set_z", "multiplier", "offset"),
        &FNPositionOutput::set_z
    );
    ClassDB::bind_method(
        D_METHOD("set_w", "multiplier", "offset"),
        &FNPositionOutput::set_w
    );
}

FNDistanceToPoint::FNDistanceToPoint() {
    _node = _FastNoise::New<_FastNoise::DistanceToPoint>();
}

void FNDistanceToPoint::set_distance_function(int64_t func) {
    _FastNoise::DistanceFunction fn_func = static_cast<_FastNoise::DistanceFunction>(func);
    _node->SetDistanceFunction(fn_func);
}

void FNDistanceToPoint::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_source", "gen"),
        &FNDistanceToPoint::set_source
    );
    ClassDB::bind_method(
        D_METHOD("set_distance_function", "func"),
        &FNDistanceToPoint::set_distance_function
    );
    ClassDB::bind_method(
        D_METHOD("set_x_scale", "value"),
        &FNDistanceToPoint::set_x_scale
    );
    ClassDB::bind_method(
        D_METHOD("set_y_scale", "value"),
        &FNDistanceToPoint::set_y_scale
    );
    ClassDB::bind_method(
        D_METHOD("set_z_scale", "value"),
        &FNDistanceToPoint::set_z_scale
    );
    ClassDB::bind_method(
        D_METHOD("set_w_scale", "value"),
        &FNDistanceToPoint::set_w_scale
    );
}
