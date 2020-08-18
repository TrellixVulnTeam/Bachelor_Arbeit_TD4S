#include "vtr_version.h"

//This file is automatically processed by CMAKE and replaces
//the values between ampersand's with the releveant CMAKE variable
//before being compiled.
namespace vtr {
    const char* VERSION = "8.0.0-dev+52f770dd8-dirty";
    const char* VERSION_SHORT = "8.0.0-dev";

    const size_t VERSION_MAJOR = 8;
    const size_t VERSION_MINOR = 0;
    const size_t VERSION_PATCH = 0;
    const char* VERSION_PRERELEASE = "dev";

    const char* VCS_REVISION = "52f770dd8-dirty";
    const char* COMPILER = "GNU 9.3.0 on CYGWIN-3.1.6(0.340/5/3) x86_64";
    const char* BUILD_TIMESTAMP = "2020-08-15T23:22:25 (Debug build)";
}
