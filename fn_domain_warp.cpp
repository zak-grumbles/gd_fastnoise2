#include "fn_domain_warp.h"

void FNDomainWarp::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_source", "gen"),
        &FNDomainWarp::set_source
    );
    ClassDB::bind_method(
        D_METHOD("set_warp_amplitude", "gen"),
        &FNDomainWarp::set_warp_amplitude
    );
    ClassDB::bind_method(
        D_METHOD("set_warp_amplitude_val", "value"),
        &FNDomainWarp::set_warp_amplitude_val
    );
    ClassDB::bind_method(
        D_METHOD("set_warp_frequency", "value"),
        &FNDomainWarp::set_warp_frequency
    );
}

FNDomainWarpGradient::FNDomainWarpGradient() {
    _node = _FastNoise::New<_FastNoise::DomainWarpGradient>();
}
