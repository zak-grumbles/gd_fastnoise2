#include "fn_modifiers.h"

FNDomainScale::FNDomainScale() {
    _node = _FastNoise::New<_FastNoise::DomainScale>();
}

void FNDomainScale::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_source", "gen"),
        &FNDomainScale::set_source
    );
    ClassDB::bind_method(
        D_METHOD("set_scale", "value"),
        &FNDomainScale::set_scale
    );
}

FNDomainOffset::FNDomainOffset() {
    _node = _FastNoise::New<_FastNoise::DomainOffset>();
}

void FNDomainOffset::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_source", "gen"),
        &FNDomainOffset::set_source
    );

    ClassDB::bind_method(
        D_METHOD("set_x_offset_val", "value"),
        &FNDomainOffset::set_x_offset_val
    );
    ClassDB::bind_method(
        D_METHOD("set_y_offset_val", "value"),
        &FNDomainOffset::set_y_offset_val
    );
    ClassDB::bind_method(
        D_METHOD("set_z_offset_val", "value"),
        &FNDomainOffset::set_z_offset_val
    );
    ClassDB::bind_method(
        D_METHOD("set_w_offset_val", "value"),
        &FNDomainOffset::set_w_offset_val
    );

    ClassDB::bind_method(
        D_METHOD("set_x_offset", "gen"),
        &FNDomainOffset::set_x_offset
    );
    ClassDB::bind_method(
        D_METHOD("set_y_offset", "gen"),
        &FNDomainOffset::set_y_offset
    );
    ClassDB::bind_method(
        D_METHOD("set_z_offset", "gen"),
        &FNDomainOffset::set_z_offset
    );
    ClassDB::bind_method(
        D_METHOD("set_w_offset", "gen"),
        &FNDomainOffset::set_w_offset
    );
}
