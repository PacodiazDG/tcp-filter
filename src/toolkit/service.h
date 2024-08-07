#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include "toolkit.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <unistd.h>

class service
{

private:
    /* data */
public:
    service(/* args */);
    ~service();
    /// @brief 
    static std::vector<const char*>*  vectipaddrs;
    static void updateBadIpaddrs();
};
#endif // TOOLKIT_H
