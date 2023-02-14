#include <string>

#include "../code/datas.h"

#ifdef _WIN32
#include "windows.h"
typedef void (*CropAddon)(CropProject);
#elif __linux__

#include <dlfcn.h>

typedef void (*CropAddon)(CropProject);

#endif

void doCompile(CropProject project, string addonPath) {
#ifdef _WIN32
    HINSTANCE hinstLib = LoadLibrary(addonPath + ".dll");
    if (!hinstLib) return;
    auto addon = (CropAddon) GetProcAddress(hinstLib, "compileCode");

    if (addon == nullptr) return;

    addon(project);
    ::FreeLibrary(hinstLib);
#elif __linux__
    void *handle;
    CropAddon func;
    handle = dlopen((addonPath + ".so").c_str(), RTLD_NOW | RTLD_GLOBAL);
    if (handle == nullptr) {
        fprintf(stderr, "Unable to open lib: %s\n", dlerror());
        return;
    }
    func = (CropAddon) dlsym(handle, "compileCode");

    if (func == nullptr) {
        fprintf(stderr, "Unable to get symbol\n");
        return;
    }

    func(project);
#endif
}