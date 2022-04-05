#include <iostream>
#include <fstream>

#include "common.h"
#include "material.h"
#include "scene.h"
#include "sphere.h"

using std::shared_ptr;
using std::make_shared;

void write_color(std::ostream &out, vec3 pixel_color) {
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

int main() {

    // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = vec3(0, 0, 0);
    auto horizontal = vec3(viewport_width, 0, 0);
    auto vertical = vec3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focal_length);

    // Scene

    scene world;
    auto s1 = make_shared<sphere>(vec3(0,0,-1), 0.5, make_shared<flat>());
    auto s2 = make_shared<sphere>(vec3(-1,0,-1), 0.5, make_shared<flat>());
    auto s3 = make_shared<sphere>(vec3(1,0,-1), 0.5, make_shared<flat>());
    world.add(s1);
    world.add(s2);
    world.add(s3);

    // Render

    std::ofstream ofs("image.ppm");
    ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            vec3 pixel_color = world.ray_color(r);
            write_color(ofs, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";

    ofs.close();

#if defined(_WIN32)
    system("image.ppm");
#elif defined(__APPLE__)
    system("open image.ppm");
#endif
}
