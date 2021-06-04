// myadd.h

#if defined(_WIN32)
#define DLL_EXPORT __declspec(dllexport) ///< define DLL_EXPORT windows
#else
#define DLL_EXPORT __attribute__((visibility("default"))) ///< define DLL_EXPORT unix 
#endif

int DLL_EXPORT myAdd(int x, int y);