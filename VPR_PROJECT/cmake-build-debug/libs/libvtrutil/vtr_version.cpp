#include "vtr_version.h"

//This file is automatically processed by CMAKE and replaces
//the values between ampersand's with the releveant CMAKE variable
//before being compiled.
namespace vtr {
    const char* VERSION = "8.0.0-dev+9d6a29f65-dirty";
    const char* VERSION_SHORT = "8.0.0-dev";

    const size_t VERSION_MAJOR = 8;
    const size_t VERSION_MINOR = 0;
    const size_t VERSION_PATCH = 0;
    const char* VERSION_PRERELEASE = "dev";

    const char* VCS_REVISION = "9d6a29f65-dirty";
    const char* COMPILER = "GNU 7.4.0 on CYGWIN-3.0.7(0.338/5/3) x86_64";
    const char* BUILD_TIMESTAMP = "2019-07-17T17:23:13 (Debug build)";
}
