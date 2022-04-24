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

    image_ = std::make_unique<bg::rgba8_image_t>(width, height);

    auto* buffer_pixel = buffer;

    auto v = bg::view(*image_.get());
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

    auto v = bg::view(*image_.get());
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

} // namespace nxlua