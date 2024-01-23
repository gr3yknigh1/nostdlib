#ifndef NOSTDLIB_PLATFORM_H_
#define NOSTDLIB_PLATFORM_H_

#ifdef _WIN32
#define NOC_PLATFORM_WINDOWS
#ifdef _WIN64
#define NOC_PLATFORM_WINDOWS_X64
#else
#define NOC_PLATFORM_WINDOWS_X32
#endif // _WIN64
#elif defined(__APPLE__) || defined(__MACH__)
#error "Premium devices isn't supported"
#elif defined(__ANDROID__)
#error "Android is not supported"
#elif defined(__linux__)
#define NOC_PLATFORM_LINUX
#else
#error "Unknown platform"
#endif // _WIN32

#ifndef NOC_PLATFORM_LINUX
#error "We currently can't support any platform except linux. sorry :c"
#endif

#endif // NOSTDLIB_PLATFORM_H_
