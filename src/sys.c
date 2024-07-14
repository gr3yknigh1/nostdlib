#include "nostdlib/platform.h"
#include "nostdlib/sys.h"

#if defined(NOC_PLATFORM_LINUX)
#include <unistd.h>
#endif

#if defined(NOC_PLATFORM_WINDOWS)
#include <Windows.h>
#endif

NOC_DEF usize
NOC_GetPageSize(void) {
    usize pageSize;

#if defined(NOC_PLATFORM_LINUX)
    pageSize = getpagesize();
#elif defined(NOC_PLATFORM_WINDOWS)
    SYSTEM_INFO systemInfo = {0};
    GetSystemInfo(&systemInfo);
    pageSize = systemInfo.dwPageSize;
#endif

    return pageSize;
}
