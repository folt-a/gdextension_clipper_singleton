#pragma once

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

class ClipperSingleton : public Object
{
	GDCLASS(ClipperSingleton, Object);

	static ClipperSingleton *singleton;

protected:
	static void _bind_methods();

public:
	static ClipperSingleton *get_singleton();

	ClipperSingleton();
	~ClipperSingleton();

    void hello_singleton();
    Array clip_polygons(Array p_polygons_a, Array p_polygons_b);
    bool subject_open;
};
