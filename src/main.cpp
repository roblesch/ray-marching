#include <iostream>
#include <fstream>

#include "camera.h"
#include "common.h"
#include "diffuse.h"
#include "scene.h"
#include "sphere.h"

void write_color(std::ostream &out, vec3 pixel_color) {
    // Clamp color to (0.0, 1.0)
    vclamp(pixel_color);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

scene diffuse_scene() {
    // 3 spheres with flat, normals, and diffuse shading
    scene world;

    world.add_light(light(
            vec3(1,1,1),
            vec3(0.3,0.3,0.3)));
    world.add_light(light(
            vec3(-1,1,1),
            vec3(0.4,0.4,0.4)));

    auto d1 = make_shared<diffuse>(
            vec3(0.3,0.1,0.1),
            vec3(0.9,0.2,0.2),
            vec3(0.4, 0.4, 0.4),
            vec3(0.2,0.2,0.2),
            16);

    auto s1 = make_shared<sphere>(
            vec3(-1.1,0,-2), 0.5,
            make_shared<flat>(vec3(0.2, 0.5, 0.1)));
    auto s2 = make_shared<sphere>(
            vec3(0, 0, -2), 0.5,
            make_shared<normals>());
    auto s3 = make_shared<sphere>(
            vec3(1.1, 0, -2), 0.5, d1);

    world.add_surface(s1);
    world.add_surface(s2);
    world.add_surface(s3);

    return world;
}

void render_scene(camera cam, scene world) {
    // Render the scene and write to image.ppm
    std::ofstream ofs("image.ppm");
    ofs << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            vec3 pixel_color;
            for (int s = 0; s < rays_per_pixel; s++) {
                auto u = (i + random_double()) / (image_width - 1);
                auto v = (j + random_double()) / (image_height - 1);
                ray r = cam.get_ray(u, v);
                pixel_color += world.ray_color(r);
            }
            pixel_color /= rays_per_pixel;
            write_color(ofs, pixel_color);
        }
    }
    std::cerr << "\nDone.\n";
    ofs.close();
}

void render_scene_parallel(camera cam, scene world) {
    render_scene(cam, std::move(world));
}

int main() {
    // Camera
    camera cam(aspect_ratio);

    // Scene
    scene world = diffuse_scene();

    // Render
    RENDER_PARALLEL ? render_scene_parallel(cam, world)
                    : render_scene(cam, world);

#if defined(_WIN32)
    system("image.ppm");
#elif defined(__APPLE__)
    system("open image.ppm");
#endif

}
