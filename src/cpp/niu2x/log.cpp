#include "log.h"

#include <stdarg.h>
#include <stdio.h>

namespace nx {

void log::write(int lvl, const char* filename, int line, const char* msg, ...)
{
    static const char* level_colors[] = {
        "",
        "\x1b[31m",
        "\x1b[31m",
        "\x1b[33m",
        "\x1b[36m",
        "\x1b[94m",
    };

    static const char* level_names[] = {
        "",
        "fatal",
        "error",
        "warning",
        "debug",
        "trace",
    };

    fprintf(stderr, "\x1b[0m\x1b[90m%s[%s] %s %d ", level_colors[lvl],
        level_names[lvl], filename, line);
    va_list args;
    va_start(args, msg);
    vfprintf(stderr, msg, args);
    fprintf(stderr, "\x1b[0m\n");
    va_end(args);
}

} // namespace nx
