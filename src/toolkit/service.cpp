#include "service.h"

service::service(/* args */)
{
}

service::~service()
{
}
std::vector<const char*> *service::vectipaddrs = nullptr;

void service::updateBadIpaddrs()
{
    const char *f = "ips.txt";
    vectipaddrs = new std::vector<const char*>;
    try
    {
        if (!access(f, F_OK) == 0)
        {
            try
            {
                toolkit::downloadfile(
                    "https://example.com/",
                    "ips.txt");
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        std::ifstream input(f);
        printf("\n");
        for (std::string line; getline(input, line);)
        {
            printf("\033[2K\rLoading: \x1B[92m%s\033[0m", line.c_str()); // dbg line
            vectipaddrs->push_back(line.c_str());
        }
        printf("\033c");
        if (!vectipaddrs)
        {
            throw std::invalid_argument("Failed to load the IP addresses, uninitialized pointer");
            exit(-0x87141);
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return;
}
