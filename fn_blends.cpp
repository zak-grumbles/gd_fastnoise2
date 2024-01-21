#include "fn_blends.h"

#include <core/object/class_db.h>

FNOpSourceLHS::FNOpSourceLHS() {
}

void FNOpSourceLHS::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_lhs", "gen"),
        &FNOpSourceLHS::set_lhs);
    ClassDB::bind_method(D_METHOD("set_rhs", "gen"),
        &FNOpSourceLHS::set_rhs);
    ClassDB::bind_method(D_METHOD("set_rhs_val", "value"),
        &FNOpSourceLHS::set_rhs_val);
}

FNOpHybridLHS::FNOpHybridLHS() {
}

void FNOpHybridLHS::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_lhs", "gen"),
        &FNOpHybridLHS::set_lhs);
    ClassDB::bind_method(D_METHOD("set_lhs_val", "value"),
        &FNOpHybridLHS::set_lhs_val);
    ClassDB::bind_method(D_METHOD("set_rhs", "gen"),
        &FNOpHybridLHS::set_rhs);
    ClassDB::bind_method(D_METHOD("set_rhs_val", "value"),
        &FNOpHybridLHS::set_rhs_val);
}

FNAdd::FNAdd() {
    _node = _FastNoise::New<_FastNoise::Add>();
}

FNSubtract::FNSubtract() {
    _node = _FastNoise::New<_FastNoise::Subtract>();
}

FNMultiply::FNMultiply() {
    _node = _FastNoise::New<_FastNoise::Multiply>();
}

FNDivide::FNDivide() {
    _node = _FastNoise::New<_FastNoise::Divide>();
}
