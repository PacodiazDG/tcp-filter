#ifndef TOOLKIT_H
#define TOOLKIT_H
#include <curl/curl.h>

/// @brief dfvdf
namespace toolkit
{
    void downloadfile(const char *fileurl, const char *name);

};
#endif // TOOLKIT_H
