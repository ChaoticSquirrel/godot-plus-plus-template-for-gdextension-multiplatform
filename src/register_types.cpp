#include "register_types.h"
#include "global_registry_plugin.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>


using namespace godot;
// ... rest of entry code stays exactly the same



void initialize_global_registry_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
        return;
    }
    // Formally bind our custom class registry loop to the engine
    ClassDB::register_class<GlobalRegistryPlugin>();
}

void uninitialize_global_registry_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
        return;
    }
}

extern "C" {
// REMOVED 'GDEXTENSION_API_CC' -> This is now fully compatible with modern Godot 4.x+ bindings!
GDExtensionBool global_registry_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
    godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

    init_obj.register_initializer(initialize_global_registry_module);
    init_obj.register_terminator(uninitialize_global_registry_module);
    init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_EDITOR);

    return init_obj.init();
}
}
