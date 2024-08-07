#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <map>
#include <pcap.h>
#include <net/ethernet.h>    //For ether_header
#include <netinet/ip_icmp.h> //Provides declarations for icmp header
#include <netinet/udp.h>     //Provides declarations for udp header
#include <netinet/tcp.h>     //Provides declarations for tcp header
#include <netinet/ip.h>      //Provides declarations for ip header
#include <netinet/ip6.h>     //Provides declarations for ip header
#include <openssl/ssl.h>
#include <string>
#include <iostream>

class tcp
{
private:
    /* data */
    /// @brief todos los posibles tcp flags
    unsigned char *tcp_payload;
    int tcp_payload_size;
    struct TCPFlags
    {
        uint16_t is_fin;
        uint16_t is_syn;
        uint16_t is_rst;
        uint16_t is_psh;
        uint16_t is_ack;
        uint16_t is_urg;
        uint16_t is_ece;
        uint16_t is_cwr;
    };

    /// @brief caracteristicas simples de de tcp
    struct tcp_pkt
    {
        int dst_port;
        int src_port;
        char *ip_src;
        char *ip_dst;
        bool is_ipv4;
        int tcp_payload_len;
        unsigned char *tcp_payload;
        TCPFlags tcp_flags;
    }; // Structure variable

    // Structure variable
    struct Package_for_analysis
    {
        tcp_pkt tcp_info;
        bool fast_veredict;
        int tcp_resambled_conter;
        unsigned char *hash;
        int tcp_ack_conter;
    };
    std::map<std::string, int> tcp_session;
    void remove_Session();
    void make_session();
    void memory_cleaner();

public:
    tcp();
    ~tcp();
    tcp_pkt tcp_info;
    void Packet_inspect(unsigned char *tcp_payload, int size);
    void Packet_PayloadDebug(unsigned char *tcp_payload, int size, bool is_ipv4);
};
