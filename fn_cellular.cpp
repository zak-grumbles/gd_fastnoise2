#include "fn_cellular.h"

void FNCellular::set_distance_func(int value) {
    auto func = static_cast<_FastNoise::DistanceFunction>(value);
    _cell_node->SetDistanceFunction(func);
}

void FNCellular::_bind_methods() {
    _bind_cellular_type_enum();
    _bind_distance_func_enum();

    ClassDB::bind_method(
        D_METHOD("set_jitter_modifier", "value"),
        &FNCellular::set_jitter_modifier
    );
    ClassDB::bind_method(
        D_METHOD("set_distance_func", "value"),
        &FNCellular::set_distance_func
    );
}

void FNCellular::_bind_cellular_type_enum() {
    ClassDB::bind_integer_constant(
        "FNCellular", "CellularType",
        "CellularValue",
        static_cast<int64_t>(CellularType::CellularValue)
    );
    ClassDB::bind_integer_constant(
        "FNCellular", "CellularType",
        "CellularDistance",
        static_cast<int64_t>(CellularType::CellularDistance)
    );
    ClassDB::bind_integer_constant(
        "FNCellular", "CellularType",
        "CellularLookup",
        static_cast<int64_t>(CellularType::CellularLookup)
    );
}

void FNCellular::_bind_distance_func_enum() {
    ClassDB::bind_integer_constant(
        "FNCellular", "DistanceFunction",
        "Euclidean",
        static_cast<int64_t>(_FastNoise::DistanceFunction::Euclidean)
    );
    ClassDB::bind_integer_constant(
        "FNCellular", "DistanceFunction",
        "EuclideanSquared",
        static_cast<int64_t>(_FastNoise::DistanceFunction::EuclideanSquared)
    );
    ClassDB::bind_integer_constant(
        "FNCellular", "DistanceFunction",
        "Manhattan", 
        static_cast<int64_t>(_FastNoise::DistanceFunction::Manhattan)
    );
    ClassDB::bind_integer_constant(
        "FNCellular", "DistanceFunction",
        "Hybrid", 
        static_cast<int64_t>(_FastNoise::DistanceFunction::Hybrid)
    );
    ClassDB::bind_integer_constant(
        "FNCellular", "DistanceFunction",
        "MaxAxis", 
        static_cast<int64_t>(_FastNoise::DistanceFunction::MaxAxis)
    );
}

FNCellularValue::FNCellularValue() {
    _cell_type = CellularType::CellularValue;
    _cell_node = _FastNoise::New<_FastNoise::CellularValue>();
    _casted_node = _FastNoise::SmartNode<_FastNoise::CellularValue>::DynamicCast(_cell_node);
}

void FNCellularValue::set_value_index(int value) {
    _casted_node->SetValueIndex(value);
}

void FNCellularValue::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_value_index", "index"),
        &FNCellularValue::set_value_index
    );
}

FNCellularDistance::FNCellularDistance() {
    _cell_type = CellularType::CellularDistance;
    _cell_node = _FastNoise::New<_FastNoise::CellularDistance>();
    _casted_node = _FastNoise::SmartNode<_FastNoise::CellularDistance>::DynamicCast(_cell_node);
}

void FNCellularDistance::set_return_type(int type) {
    auto type = static_cast<_FastNoise::CellularDistance::ReturnType>(type);
    _casted_node->SetReturnType(type);
}

void FNCellularDistance::_bind_methods() {
    ClassDB::bind_method(
        D_METHOD("set_distance_index0", "value"),
        &FNCellularDistance::set_distance_index0
    );
    ClassDB::bind_method(
        D_METHOD("set_distance_index1", "value"),
        &FNCellularDistance::set_distance_index1
    );
    ClassDB::bind_method(
        D_METHOD("set_return_type", "value"),
        &FNCellularDistance::set_return_type
    );
}

void FNCellularDistance::_bind_return_type_enum() {
    ClassDB::bind_integer_constant(
        "FNCellularDistance", "ReturnType",
        "Index0",
        static_cast<int64_t>(_FastNoise::CellularDistance::ReturnType::Index0)
    );
    ClassDB::bind_integer_constant(
        "FNCellularDistance", "ReturnType",
        "Index0Add1",
        static_cast<int64_t>(_FastNoise::CellularDistance::ReturnType::Index0Add1)
    );
    ClassDB::bind_integer_constant(
        "FNCellularDistance", "ReturnType",
        "Index0Sub1",
        static_cast<int64_t>(_FastNoise::CellularDistance::ReturnType::Index0Sub1)
    );
    ClassDB::bind_integer_constant(
        "FNCellularDistance", "ReturnType",
        "Index0Mul1",
        static_cast<int64_t>(_FastNoise::CellularDistance::ReturnType::Index0Mul1)
    );
    ClassDB::bind_integer_constant(
        "FNCellularDistance", "ReturnType",
        "Index0Div1",
        static_cast<int64_t>(_FastNoise::CellularDistance::ReturnType::Index0Div1)
    );
}
