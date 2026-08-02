#include <game/Paths.h>
#include <string>

std::string GetAssetsPath()
{
#if defined(ASSETS_DIR)
    return ASSETS_DIR;
#else
    return "assets";
#endif
}

std::string GetAssetsPath(const char* subdir)
{
    if (!subdir || !*subdir)
        return GetAssetsPath();
    return GetAssetsPath() + "/" + subdir;
}

