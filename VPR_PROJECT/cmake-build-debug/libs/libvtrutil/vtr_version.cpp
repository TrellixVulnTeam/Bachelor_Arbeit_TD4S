#include "vtr_version.h"

//This file is automatically processed by CMAKE and replaces
//the values between ampersand's with the releveant CMAKE variable
//before being compiled.
namespace vtr {
    const char* VERSION = "8.0.0-dev+0fe5bd411-dirty";
    const char* VERSION_SHORT = "8.0.0-dev";

    const size_t VERSION_MAJOR = 8;
    const size_t VERSION_MINOR = 0;
    const size_t VERSION_PATCH = 0;
    const char* VERSION_PRERELEASE = "dev";

    const char* VCS_REVISION = "0fe5bd411-dirty";
    const char* COMPILER = "GNU 9.3.0 on CYGWIN-3.1.4(0.340/5/3) x86_64";
    const char* BUILD_TIMESTAMP = "2020-03-30T00:24:10 (Debug build)";
}
