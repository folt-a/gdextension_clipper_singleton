#include "clipper_singleton.hpp"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
//#include <godot_cpp/variant/vector2.hpp>
#include "clipper.h"

using namespace godot;

ClipperSingleton *ClipperSingleton::singleton = nullptr;

void ClipperSingleton::_bind_methods() {
    ClassDB::bind_method(D_METHOD("hello_singleton"), &ClipperSingleton::hello_singleton);
    ClassDB::bind_method(D_METHOD("clip_polygons"), &ClipperSingleton::clip_polygons);
//    ClassDB::bind_method(D_METHOD("set_parameters"), &ClipperSingleton::set_parameters);
}

ClipperSingleton *ClipperSingleton::get_singleton() {
    return singleton;
}

ClipperSingleton::ClipperSingleton() {
    ERR_FAIL_COND(singleton != nullptr);
    singleton = this;
}

ClipperSingleton::~ClipperSingleton() {
    ERR_FAIL_COND(singleton != this);
    singleton = nullptr;
}

void ClipperSingleton::hello_singleton() {
    UtilityFunctions::print("Hello GDExtension Singleton!");
}

Array ClipperSingleton::clip_polygons(Array p_polygons_a, Array p_polygons_b) {
    clipperlib::Clipper clp = clipperlib::Clipper();
    
    clipperlib::Paths subjectPaths;
    subjectPaths.clear();
    subjectPaths.resize(p_polygons_a.size());
    for (int i = 0; i < p_polygons_a.size(); ++i) {
        PackedVector2Array array_vec2 = ((const PackedVector2Array) p_polygons_a[i]);
        clipperlib::Path &polypath_out = subjectPaths[i];
        for (int j = 0; j < array_vec2.size(); ++j) {
            polypath_out << clipperlib::Point64(
                    ((const Vector2) array_vec2[j]).x * 1e3,
                    ((const Vector2) array_vec2[j]).y * 1e3);
//            UtilityFunctions::print(((const Vector2) array_vec2[j]).x);
//            UtilityFunctions::print(((const Vector2) array_vec2[j]).y);
        }
//        UtilityFunctions::print("----------");
    }
    clp.AddPaths(subjectPaths, clipperlib::ptSubject, false);
    if (p_polygons_b.size() != 0) { // Optional for merge operation.
        clipperlib::Paths clipPaths;
        clipPaths.clear();
        clipPaths.resize(p_polygons_b.size());
        for (int i = 0; i < p_polygons_b.size(); ++i) {
            PackedVector2Array array_vec2 = ((const PackedVector2Array) p_polygons_b[i]);
            clipperlib::Path &polypath_out = clipPaths[i];
            for (int j = 0; j < array_vec2.size(); ++j) {
                polypath_out << clipperlib::Point64(
                        ((const Vector2) array_vec2[j]).x * 1e3,
                        ((const Vector2) array_vec2[j]).y * 1e3);
//                UtilityFunctions::print(((const Vector2) array_vec2[j]).x);
//                UtilityFunctions::print(((const Vector2) array_vec2[j]).y);
            }
        }
//        UtilityFunctions::print("71!");
        clp.AddPaths(clipPaths, clipperlib::ptClip, false);
    }

    clipperlib::Paths solutionClosed, solutionOpen;
    
    clp.Execute(clipperlib::ctDifference, solutionClosed, clipperlib::frNonZero);

//    Vector<Vector<Point2>> ret;
//    GodotClipperUtils::scale_down_polypaths(solutionClosed, ret);
//    UtilityFunctions::print("80!");
    Array ret;

    for (clipperlib::Paths::size_type i = 0; i < solutionClosed.size(); ++i) {
        const clipperlib::Path &polypath_in = solutionClosed[i];
//        Vector<Vector2> polypath_out;
        Array ret_nest;
        for (clipperlib::Paths::size_type j = 0; j < polypath_in.size(); ++j) {
//            polypath_out.push_back(Point2(
//                    static_cast<real_t>(polypath_in[j].X) / 1e3,
//                    static_cast<real_t>(polypath_in[j].Y) / 1e3));
            ret_nest.push_back(Vector2(
                    static_cast<real_t>(polypath_in[j].x) / 1e3,
                    static_cast<real_t>(polypath_in[j].y) / 1e3));
        }
//        UtilityFunctions::print("95!");
        ret.push_back(ret_nest);
//        ret.append(push_back)
//        p_polypaths_out.push_back(polypath_out);
    }
    
//    for (int i = 0; i < solutionClosed.size(); ++i) {
//        ret.push_back(solutionClosed[i]);
//    }
    return ret;
}
//
//clipperlib::Clipper PolyBoolean2DClipper6::configure() {
//    using namespace clipperlib;
//
//    clip_type = ctDifference;
//    int init_options = 0;
//
//    subject_fill_type = PolyFillType(p_parameters->subject_fill_rule);
//    clip_fill_type = PolyFillType(p_parameters->clip_fill_rule);
//    init_options |= p_parameters->0;
//    init_options |= p_parameters->0;
//    init_options |= p_parameters->0;
//    subject_open = p_parameters->subject_open;
//
//    return Clipper(init_options);
//}