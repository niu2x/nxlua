#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

static constexpr int COMPS = 4;

namespace bg = boost::gil;

namespace nxlua {

image_t::image_t() { }

image_t::~image_t() { }

bool image_t::load(const char* filename)
{
    int width, height;
    int comp;
    auto* buffer = stbi_load(filename, &width, &height, &comp, COMPS);
    if (!buffer)
        return false;

    resize(width, height);

    auto* buffer_pixel = buffer;

    auto v = bg::view(backend());
    auto b = v.begin();
    while (b != v.end()) {
        *b = bg::rgba8_pixel_t { buffer_pixel[0], buffer_pixel[1],
            buffer_pixel[2], buffer_pixel[3] };
        buffer_pixel += COMPS;
        b++;
    }
    stbi_image_free(buffer);
    return true;
}

bool image_t::save(const char* filename)
{
    if (!image_)
        return false;

    auto buffer = new uint8_t[image_->width() * image_->height() * COMPS];
    auto buffer_writer = buffer;

    auto v = bg::view(backend());
    auto b = v.begin();
    while (b != v.end()) {
        *(buffer_writer++) = (*b)[0];
        *(buffer_writer++) = (*b)[1];
        *(buffer_writer++) = (*b)[2];
        *(buffer_writer++) = (*b)[3];
        ++b;
    }

    auto success = 1
        == stbi_write_png(filename, image_->width(), image_->height(), COMPS,
            buffer, image_->width() * COMPS);
    delete[] buffer;
    return success;
}

// image_t image_t::resize(int width, int height) {
//     image_t result;
//     result._resize(width,height);
//     bg::resize_view(bg::const_view(backend()), bg::view( result.backend() ),
//     bg::bilinear_sampler()); return result;
// }

void image_t::resize(int width, int height)
{
    image_ = std::make_unique<bg::rgba8_image_t>(width, height);
}

void image_t::resample(image_t* src, int src_min_x, int src_min_y,
    int src_width, int src_height,

    image_t* dst, int dst_min_x, int dst_min_y, int dst_width, int dst_height,

    const image_transform_t* dst_to_src)
{

    bg::resample_pixels(bg::subimage_view(bg::const_view(src->backend()),
                            src_min_x, src_min_y, src_width, src_height),
        bg::subimage_view(bg::view(dst->backend()), dst_min_x, dst_min_y,
            dst_width, dst_height),
        dst_to_src->backend(), bg::bilinear_sampler());
}

image_t::color_t image_t::pixel(int x, int y) const
{
    auto view = bg::const_view(backend());
    auto ref = view(x, y);
    return {
        (ref)[0],
        (ref)[1],
        (ref)[2],
        (ref)[3],
    };
}

image_transform_t image_transform_t::translate(double x, double y)
{
    image_transform_t t;
    t.mat_ = bg::matrix3x2<double>::get_translate(x, y);
    return t;
}
image_transform_t image_transform_t::scale(double x, double y)
{
    image_transform_t t;
    t.mat_ = bg::matrix3x2<double>::get_scale(x, y);
    return t;
}
image_transform_t image_transform_t::rotate(double angle)
{
    image_transform_t t;
    t.mat_ = bg::matrix3x2<double>::get_rotate(angle);
    return t;
}

image_transform_t::image_transform_t() { }
image_transform_t::~image_transform_t() { }

image_transform_t image_transform_t::mul(const image_transform_t& right) const
{
    image_transform_t t;
    t.mat_ = this->mat_ * right.mat_;
    return t;
}

} // namespace nxlua