#include "register_types.h"

#include <core/object/class_db.h>

#include "fn_cellular.h"
#include "fn_fractal.h"
#include "fn_generator.h"
#include "fn_basic_generators.h"
#include "fn_blends.h"
#include "fn_domain_warp.h"
#include "fn_modifiers.h"

void initialize_gd_fastnoise2_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	// Noise generators
	ClassDB::register_class<FNGenerator>();
	ClassDB::register_class<FNSimplexGenerator>();
	ClassDB::register_class<FNPerlinGenerator>();
	ClassDB::register_class<FNValueGenerator>();
	ClassDB::register_class<FNFractal>();
	ClassDB::register_class<FNCellular>();
	ClassDB::register_class<FNCellularValue>();
	ClassDB::register_class<FNCellularDistance>();
	ClassDB::register_class<FNCellularLookup>();

	// Basic generators
	ClassDB::register_class<FNConstant>();
	ClassDB::register_class<FNWhite>();
	ClassDB::register_class<FNCheckerboard>();
	ClassDB::register_class<FNSineWave>();
	ClassDB::register_class<FNPositionOutput>();
	ClassDB::register_class<FNDistanceToPoint>();

	// Domain Warp
	ClassDB::register_class<FNDomainWarp>();
	ClassDB::register_class<FNDomainWarpGradient>();

	// Modifiers
	ClassDB::register_class<FNDomainScale>();
	ClassDB::register_class<FNDomainOffset>();

	// Blends
	ClassDB::register_class<FNOpSourceLHS>();
	ClassDB::register_class<FNOpHybridLHS>();
	ClassDB::register_class<FNAdd>();
	ClassDB::register_class<FNSubtract>();
	ClassDB::register_class<FNMultiply>();
	ClassDB::register_class<FNDivide>();
}

void uninitialize_gd_fastnoise2_module(ModuleInitializationLevel p_level) {
}
