#include <godot-cpp/include/godot_cpp/classes/dir_access.hpp>
#include <godot-cpp/include/godot_cpp/classes/file_access.hpp>
#include <godot-cpp/include/godot_cpp/classes/editor_interface.hpp>

using namespace godot;

void GlobalRegistryPlugin::_enter_tree() {
    String global_repo_path = "user://../GodotGlobalRegistry/"; 
    Ref<DirAccess> dir = DirAccess::open(global_repo_path);
    
    if (dir.is_null()) {
        DirAccess::make_dir_absolute(global_repo_path);
        return;
    }

    dir->list_dir_begin();
    String subfolder = dir->get_next();
    
    while (subfolder != "") {
        if (dir->current_is_dir() && !subfolder.begins_with(".")) {
            _register_custom_user_nodes(global_repo_path + subfolder + "/");
        }
        subfolder = dir->get_next();
    }
}

void GlobalRegistryPlugin::_register_custom_user_nodes(String folder_path) {
    String node_name = folder_path.get_basename().get_file(); 
    String script_path = folder_path + node_name + ".gd";
    String icon_path = folder_path + "icon.svg";
    
    // Shortened filenames
    String b_path = folder_path + "base.txt";
    String c_path = folder_path + "cat.txt";

    // Standard engine defaults
    String base_type = "Node"; 
    String category = "UserNodes";

    // 1. Read Base Node Type
    if (FileAccess::file_exists(b_path)) {
        Ref<FileAccess> file = FileAccess::open(b_path, FileAccess::READ);
        if (file.is_valid()) {
            String read_line = file->get_line().strip_edges();
            if (!read_line.is_empty()) {
                base_type = read_line;
            }
        }
    }

    // 2. Read Custom Category with strict validation and failure fallback
    if (FileAccess::file_exists(c_path)) {
        Ref<FileAccess> file = FileAccess::open(c_path, FileAccess::READ);
        if (file.is_valid()) {
            String read_line = file->get_line().strip_edges();
            // If the file exists but it's accidentally empty, drop back to fallback
            if (!read_line.is_empty()) {
                category = read_line;
            } else {
                UtilityFunctions::print("Warning: ", node_name, "/c.txt is empty. Falling back to 'UserNodes'.");
            }
        }
    } else {
        // If the file is missing entirely, log a clean warning and keep moving gracefully
        UtilityFunctions::print("Notice: Missing c.txt for ", node_name, ". Using fallback category 'UserNodes'.");
    }

    // 3. Verify files and load script safely into memory
    if (!FileAccess::file_exists(script_path)) {
        UtilityFunctions::print("Error: Missing script file for ", node_name, ". Skipping registration.");
        return;
    }

    Ref<Script> loaded_script = ResourceLoader::get_singleton()->load(script_path);
    if (loaded_script.is_valid()) {
        // Load custom icon if it exists, otherwise pass a null reference to let Godot fall back to the base icon
        Ref<Texture2D> icon_tex;
        if (FileAccess::file_exists(icon_path)) {
            icon_tex = ResourceLoader::get_singleton()->load(icon_path);
        }

        EditorInterface::get_singleton()->get_editor_plugin_base()->add_custom_type(
            node_name, base_type, loaded_script, icon_tex
        );
        UtilityFunctions::print("Registered: ", node_name, " (", base_type, ") -> [", category, "]");
    }
}
