#include "register_types.h"

#include <core/object/class_db.h>

#include "gd_fastnoise2.h"

void initialize_GDFastNoise2_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<FNGenerator>();
	ClassDB::register_class<FNModifier>();
}

void uninitialize_GDFastNoise2_module(ModuleInitializationLevel p_level) {
}
