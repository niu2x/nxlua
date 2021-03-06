#include "image.h"

#include <filesystem>

#include <boost/gil/algorithm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include "nxlua/nx_assert.h"

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
    if (!image_) {
        return false;
    }

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

    std::filesystem::path target = filename;
    auto ext = target.extension();
    int err = -1;
    if (ext == ".png")
        err = stbi_write_png(filename, image_->width(), image_->height(), COMPS,
            buffer, image_->width() * COMPS);
    else if (ext == ".jpg")
        err = stbi_write_jpg(
            filename, image_->width(), image_->height(), COMPS, buffer, 100);
    else if (ext == ".bmp")
        err = stbi_write_bmp(
            filename, image_->width(), image_->height(), COMPS, buffer);
    else if (ext == ".tga")
        err = stbi_write_tga(
            filename, image_->width(), image_->height(), COMPS, buffer);
    else
        NX_ASSERT(false, "unsupport image format %s", ext.c_str());

    delete[] buffer;
    return err == 1;
}

void image_t::fill(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (!image_) {
        return;
    }

    auto v = bg::view(backend());
    auto iter = v.begin();
    while (iter != v.end()) {
        (*iter)[0] = r;
        (*iter)[1] = g;
        (*iter)[2] = b;
        (*iter)[3] = a;
        ++iter;
    }
}

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

void image_t::draw(const image_t* src, int x, int y, int blend)
{

    using Pix = bg::rgba8_pixel_t::value_type;

    bg::transform_pixels(bg::subimage_view(bg::const_view(src->backend()), 0, 0,
                             src->width(), src->height()),

        bg::subimage_view(
            bg::view(this->backend()), x, y, src->width(), src->height()),

        bg::subimage_view(
            bg::view(this->backend()), x, y, src->width(), src->height()),

        [](auto& A, auto& B) {
            return Pix {
                (uint8_t)(((A[0] * A[0]) >> 8) + ((B[0] * (255 - A[0])) >> 8)),
                (uint8_t)(((A[1] * A[0]) >> 8) + ((B[1] * (255 - A[0])) >> 8)),
                (uint8_t)(((A[2] * A[0]) >> 8) + ((B[2] * (255 - A[0])) >> 8)),
                (uint8_t)(((A[3] * A[0]) >> 8) + ((B[3] * (255 - A[0])) >> 8)),
            };
        });
}

} // namespace nxlua