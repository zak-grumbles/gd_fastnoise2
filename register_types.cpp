#include "register_types.h"

#include <core/object/class_db.h>

#include "fn_generator.h"
#include "fn_fractal.h"

void initialize_gd_fastnoise2_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<FNGenerator>();
	ClassDB::register_class<FNFractal>();
}

void uninitialize_gd_fastnoise2_module(ModuleInitializationLevel p_level) {
}
