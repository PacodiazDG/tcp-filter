#include <string>
#include <openssl/ssl.h>
#include <openssl/err.h>


class handshake
{
private:
    /* data */
public:
    handshake(/* args */);
    ~handshake();
   static std::string extractSNI(const unsigned char *data, size_t data_length);
};
