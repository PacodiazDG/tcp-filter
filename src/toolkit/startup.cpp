#include "startup.h"

startup::startup(/* args */)
{
}

startup::~startup()
{
}



void startup::iniT()
{
    service::updateBadIpaddrs();
}
