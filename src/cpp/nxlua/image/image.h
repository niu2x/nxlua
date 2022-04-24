#ifndef NXLUA_IMAGE_H
#define NXLUA_IMAGE_H

#include <memory>

#include <boost/gil.hpp>
#include <boost/noncopyable.hpp>

#include "utils.h"

namespace nxlua {

class image_t : private boost::noncopyable {
public:
    image_t();
    ~image_t();

    bool load(const char*);
    bool save(const char*);

private:
    std::unique_ptr<boost::gil::rgba8_image_t> image_;
};

} // namespace nxlua

#endif