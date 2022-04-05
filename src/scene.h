#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <limits>

#include "common.h"
#include "hit_record.h"
#include "surface.h"

class scene {
public:
    scene() = default;
    explicit scene(const shared_ptr<surface>& s) { add(s); }
    void add(const shared_ptr<surface>& s) { surface_list.push_back(s); }

    double DE(vec3 p);
    bool march(const ray& r, hit_record& rec);
    vec3 ray_color(const ray& r);

public:
    std::vector<shared_ptr<surface>> surface_list{};
    shared_ptr<surface> nearest;
};

#endif //SCENE_H
