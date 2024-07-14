#if !defined(NOSTDLIB_PLATFORM_H_)
#define NOSTDLIB_PLATFORM_H_

#if defined(_WIN32)
#define NOC_PLATFORM_WINDOWS
#elif defined(__APPLE__) || defined(__MACH__)
#error "Premium devices isn't supported"
#elif defined(__ANDROID__)
#error "Android is not supported"
#elif defined(__linux__)

#if !defined(NOC_PLATFORM_LINUX)
#define NOC_PLATFORM_LINUX
#endif

#else
#error "Unknown platform"
#endif // _WIN32

#if !defined(NOC_PLATFORM_LINUX)
#error "We currently can't support any platform except linux. sorry :c"
#endif

#endif // NOSTDLIB_PLATFORM_H_
