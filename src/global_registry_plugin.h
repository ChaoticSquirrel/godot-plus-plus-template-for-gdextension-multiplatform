#ifndef GLOBAL_REGISTRY_PLUGIN_H
#define GLOBAL_REGISTRY_PLUGIN_H

#include <godot-cpp/include/godot_cpp/classes/editor_plugin.hpp>

namespace godot {

class GlobalRegistryPlugin : public EditorPlugin {
    GDCLASS(GlobalRegistryPlugin, EditorPlugin);

protected:
    static void _bind_methods() {} // Required by Godot's system structure

public:
    // Declare the functions that live inside your .cpp file
    void _enter_tree() override;
    void _exit_tree() override;
    void _register_custom_user_nodes(String folder_path);
};

} // namespace godot

#endif // GLOBAL_REGISTRY_PLUGIN_H
