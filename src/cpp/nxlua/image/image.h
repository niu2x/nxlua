#ifndef NXLUA_IMAGE_H
#define NXLUA_IMAGE_H

#include <memory>

#include <boost/gil/image.hpp>
#include <boost/gil/typedefs.hpp>
#include <boost/gil/extension/numeric/sampler.hpp>
#include <boost/gil/extension/numeric/resample.hpp>
#include <boost/noncopyable.hpp>

#include "utils.h"

namespace nxlua {

class image_transform_t {
public:
    static image_transform_t translate(double, double);
    static image_transform_t scale(double, double);
    static image_transform_t rotate(double);

    image_transform_t();
    ~image_transform_t();

    boost::gil::matrix3x2<double>& backend() { return mat_; }
    const boost::gil::matrix3x2<double>& backend() const { return mat_; }

    image_transform_t mul(const image_transform_t& right) const;

private:
    boost::gil::matrix3x2<double> mat_;
};

class image_t {
public:
    typedef struct {
        uint8_t r, g, b, a;
    } color_t;

    image_t();
    ~image_t();
    bool load(const char*);
    bool save(const char*);

    void resize(int width, int height);

    image_t(image_t&& other) = default;
    image_t& operator=(image_t&& other) = default;

    image_t(const image_t& other) = delete;
    image_t& operator=(const image_t& other) = delete;

    static void resample(image_t* src, int src_min_x, int src_min_y,
        int src_width, int src_height,

        image_t* dst, int dst_min_x, int dst_min_y, int dst_width,
        int dst_height,

        const image_transform_t*);

    int width() const { return image_ ? image_->width() : 0; }

    int height() const { return image_ ? image_->height() : 0; }

    color_t pixel(int x, int y) const;

private:
    std::unique_ptr<boost::gil::rgba8_image_t> image_;

    // void _resize(int width, int height);
    boost::gil::rgba8_image_t& backend() { return *image_.get(); }
    const boost::gil::rgba8_image_t& backend() const { return *image_.get(); }
};

} // namespace nxlua

#endif