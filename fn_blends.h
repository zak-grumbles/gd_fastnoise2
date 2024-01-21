#ifndef gd_fastnoise2_FNBLENDS_H
#define gd_fastnoise2_FNBLENDS_H

#include "fn_generator.h"

#include "FastNoise2/include/FastNoise/Generators/Blends.h"

namespace _FastNoise = FastNoise;

class FNOpSourceLHS : public FNGenerator {
    GDCLASS(FNOpSourceLHS, FNGenerator)

public:
    FNOpSourceLHS();

    void set_lhs(FNGenerator* gen) { _node->SetLHS(gen->_get_smart_node()); }
    void set_rhs(FNGenerator* gen) { _node->SetRHS(gen->_get_smart_node()); }
    void set_rhs_val(float value) { _node->SetRHS(value); }

    virtual _FastNoise::SmartNode<_FastNoise::Generator> _get_smart_node() const override {
         return _node; 
    }

protected:
    static void _bind_methods();

    _FastNoise::SmartNode<_FastNoise::OperatorSourceLHS> _node;
};

class FNOpHybridLHS : public FNGenerator {
    GDCLASS(FNOpHybridLHS, FNGenerator)

public:
    FNOpHybridLHS();

    void set_lhs(FNGenerator* gen) { _node->SetLHS(gen->_get_smart_node()); }
    void set_lhs_val(float value) { _node->SetLHS(value); }
    void set_rhs(FNGenerator* gen) { _node->SetRHS(gen->_get_smart_node()); }
    void set_rhs_val(float value) { _node->SetRHS(value); }

protected:
    static void _bind_methods();

    _FastNoise::SmartNode<_FastNoise::OperatorHybridLHS> _node;
};

class FNAdd : public FNOpSourceLHS {
    GDCLASS(FNAdd, FNOpSourceLHS)

public:
    FNAdd();
};

class FNSubtract : public FNOpHybridLHS {
    GDCLASS(FNSubtract, FNOpHybridLHS)

public:
    FNSubtract();
};

class FNMultiply : public FNOpSourceLHS {
    GDCLASS(FNMultiply, FNOpSourceLHS)

public:
    FNMultiply();
};

class FNDivide : public FNOpHybridLHS {
    GDCLASS(FNDivide, FNOpHybridLHS)

public:
    FNDivide();
};

#endif