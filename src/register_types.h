#ifndef REGISTER_TYPES_H
#define REGISTER_TYPES_H

// Core header that maps initialization tiers natively
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

// The exact pair of tier functions called by our entry point
void initialize_global_registry_module(ModuleInitializationLevel p_level);
void uninitialize_global_registry_module(ModuleInitializationLevel p_level);

#endif // REGISTER_TYPES_H

