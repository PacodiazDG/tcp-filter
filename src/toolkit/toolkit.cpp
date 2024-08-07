#include "toolkit.h"
#include <stdexcept>

/// @brief
/// @param fileurl
/// @param name
namespace toolkit
{
    void downloadfile(const char *fileurl,
                      const char *name)
    {

        if (sizeof(name) >= FILENAME_MAX - 1)
            throw std::invalid_argument("File name too long");
        CURL *curl;
        FILE *f;
        CURLcode r;
        curl = curl_easy_init();
        if (curl)
        {
            f = fopen(name, "wb");
            curl_easy_setopt(curl, CURLOPT_URL, fileurl);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, f);
            r = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(f);
        }
    }
  
}