#ifndef NXLUA_IMAGE_H
#define NXLUA_IMAGE_H

#include <memory>

#include <boost/gil.hpp>
#include <boost/noncopyable.hpp>

#include "utils.h"

namespace nxlua {

class image_t {
public:
    image_t();
    ~image_t();
    bool load(const char*);
    bool save(const char*);

    void resize(int width, int height);

    image_t(image_t&& other) = default;
    image_t& operator=(image_t&& other) = default;

    image_t(const image_t& other) = delete;
    image_t& operator=(const image_t& other) = delete;

    static void resample_subimage(image_t* src, image_t* dst, int src_min_x,
        int src_min_y, int src_max_x, int src_max_y, double angle);

    int width() const { return image_ ? image_->width() : 0; }

    int height() const { return image_ ? image_->height() : 0; }

private:
    std::unique_ptr<boost::gil::rgba8_image_t> image_;

    // void _resize(int width, int height);
    boost::gil::rgba8_image_t& backend() { return *image_.get(); }
};

} // namespace nxlua

#endif