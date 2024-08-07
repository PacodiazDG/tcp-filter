#include <pcap.h>
#include <net/ethernet.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>
#include <libnetfilter_queue/libnetfilter_queue.h>
#include "../tls/handshake.h"
#include <iostream>
#include "../tcp/tcp.h"
#include "../toolkit/service.h"
#include <iomanip>
#include <chrono>
#include <ctime>
namespace nfqueue_control
{
    class nfqueue_manager
    {
    private:
        int queue, verbose;
        static int cb(nfq_q_handle *qh, nfgenmsg *nfmsg, nfq_data *nfa, void *data);
        static bool nfqueue_control(unsigned char *buffer, int size);
        static u_int32_t handle_pkt(nfq_data *tb);
        static bool Process_package(nfq_data *tb);
        

    public:
        nfqueue_manager(int q, bool verbose);
        void run();
        static void dafault_nfq();
        static const int default_nfq = 3;

    };
    struct
    {
        int default_nfq;
        bool verbose;
    } options;
}