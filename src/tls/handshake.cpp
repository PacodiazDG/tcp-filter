#include "handshake.h"
#include <iostream>

std::string handshake::extractSNI(const unsigned char *data, size_t data_length) {
    BIO *bio = BIO_new(BIO_s_mem());
    BIO_write(bio, data, data_length);
    SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());
    SSL *ssl = SSL_new(ssl_ctx);
    SSL_set_bio(ssl, bio, bio);
    if (SSL_accept(ssl) <= 0) {
        std::cerr << "failed hello client" << std::endl;
        return "";
    }
    const unsigned char *sni_data;
    unsigned int sni_length;
    SSL_get0_next_proto_negotiated(ssl, &sni_data, &sni_length);
    std::string sni(reinterpret_cast<const char*>(sni_data), sni_length);
    SSL_free(ssl);
    SSL_CTX_free(ssl_ctx);
    BIO_free(bio);
    return sni;
}