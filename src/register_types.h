#ifndef REGISTER_TYPES_H
#define REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>


using namespace godot;

// Declare the boot-up and shut-down sequence functions
void initialize_global_registry_module(ModuleInitializationLevel p_level);
void uninitialize_global_registry_module(ModuleInitializationLevel p_level);

#endif // REGISTER_TYPES_H
