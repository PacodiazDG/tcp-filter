#include "nfqueue_manager.h"
tcp *c = new tcp();

namespace nfqueue_control
{

    /// @brief
    /// @param buffer
    /// @param size
    bool nfqueue_manager::nfqueue_control(unsigned char *buffer, int size)
    {
        c->Packet_inspect(buffer, size);
        if (service::vectipaddrs)
        {
            for (const auto &ip : *service::vectipaddrs)
            {
                if (strcmp(c->tcp_info.ip_src, ip) == 0)
                {
                    return true;
                }
            }
        }
        else
        {
            std::cerr << "El vector vectipaddrs no está inicializado." << std::endl;
        }
        return false;
    }
    /// @brief
    /// @param tb
    /// @return
    u_int32_t nfqueue_manager::handle_pkt(nfq_data *tb)
    {

        int id = 0;
        struct nfqnl_msg_packet_hdr *ph;
        struct nfqnl_msg_packet_hw *q;
        u_int32_t mark, ifi;
        int ret;
        unsigned char *data;
        ph = nfq_get_msg_packet_hdr(tb);
        if (ph)
        {
            id = ntohl(ph->packet_id);
        }
        q = nfq_get_packet_hw(tb);
        if (q)
        {
            int i, hlen = ntohs(q->hw_addrlen);
        }
        mark = nfq_get_nfmark(tb);
        fputc('\n', stdout);
        return id;
    }
    /// @brief controls and processes the package
    /// @param tb
    /// @return returns true in case the packet has to be blocked
    bool nfqueue_manager::Process_package(nfq_data *tb)
    {
        int ret;
        unsigned char *data;
        bool veredict = false;
        ret = nfq_get_payload(tb, &data);
        if (ret >= 0)
        {
            veredict = nfqueue_control(data, ret);
        }
        fputc('\n', stdout);
        return veredict;
    }

    int nfqueue_manager::cb(struct nfq_q_handle *qh, struct nfgenmsg *nfmsg, struct nfq_data *nfa, void *data)
    {
        u_int32_t id = handle_pkt(nfa);
        if (Process_package(nfa))
        {
            return nfq_set_verdict(qh, id, NF_DROP, 0, NULL);
        }
        struct nfqnl_msg_packet_hdr *ph;
        ph = nfq_get_msg_packet_hdr(nfa);
        id = ntohl(ph->packet_id);
        return nfq_set_verdict(qh, id, NF_ACCEPT, 0, NULL);
    }

    nfqueue_manager::nfqueue_manager(int q = 0, bool verbose = true)
    {
        this->queue = q;
        this->verbose = verbose;
    }
    void nfqueue_manager::run()
    {
        if (this->verbose == false)
        {
            fclose(stdout);
        }
        struct nfq_handle *h;
        struct nfq_q_handle *qh;
        int fd;
        int rv;
        char buf[4096] __attribute__((aligned));
        printf("opening library handle\n");
        h = nfq_open();
        if (!h)
        {
            fprintf(stderr, "error during nfq_open()\n");
            exit(1);
        }
        if (nfq_unbind_pf(h, AF_INET) < 0)
        {
            fprintf(stderr, "error during nfq_unbind_pf()\n");
            exit(1);
        }
        if (nfq_bind_pf(h, AF_INET) < 0)
        {
            fprintf(stderr, "error during nfq_bind_pf()\n");
            exit(1);
        }
        qh = nfq_create_queue(h, (this->queue), &cb, NULL);
        if (!qh)
        {
            fprintf(stderr, "error during nfq_create_queue()\n");
            exit(1);
        }
        printf("setting copy_packet mode\n");
        if (nfq_set_mode(qh, NFQNL_COPY_PACKET, 0xffff) < 0)
        {
            fprintf(stderr, "can't set packet_copy mode\n");
            exit(1);
        }

        fd = nfq_fd(h);
        while ((rv = recv(fd, buf, sizeof(buf), 0)))
        {
            std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::cout << "\033[2K\rpkt received: \x1B[92m" << std::put_time(std::localtime(&t), "%Y-%m-%d %H:%M:%S") << "\033[0m" << std::flush;
            nfq_handle_packet(h, buf, rv);
        }
        nfq_destroy_queue(qh);
#ifdef INSANE
        nfq_unbind_pf(h, AF_INET);
#endif
        nfq_close(h);
        exit(0);
    }

}