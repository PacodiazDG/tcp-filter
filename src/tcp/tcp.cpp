#include "tcp.h"



/// @brief imprime modo debug lo que es los bytes
/// @param tb
/// @return
void tcp::Packet_inspect(unsigned char *tcp_payload, int size)
{
    struct ether_header *eh = (struct ether_header *)tcp_payload;
    struct iphdr *ip_header = (struct iphdr *)tcp_payload;
    struct ip6_hdr *ip6_headers = (struct ip6_hdr *)tcp_payload;
    if (ip_header->protocol == IPPROTO_TCP)
    {
        tcp_info.is_ipv4 = true;
        struct sockaddr_in src_addr, dst_addr;
        src_addr.sin_addr.s_addr = ip_header->saddr;
        dst_addr.sin_addr.s_addr = ip_header->daddr;
        struct tcphdr *tcp_header = (struct tcphdr *)(tcp_payload + ip_header->ihl * 4);
        tcp_info.src_port = ntohs(tcp_header->source);
        tcp_info.dst_port = ntohs(tcp_header->dest);
        tcp_info.tcp_flags.is_fin = tcp_header->fin;
        tcp_info.tcp_flags.is_syn = tcp_header->syn;
        tcp_info.tcp_flags.is_rst = tcp_header->rst;
        tcp_info.tcp_flags.is_psh = tcp_header->psh;
        tcp_info.tcp_flags.is_ack = tcp_header->ack;
        tcp_info.tcp_flags.is_urg = tcp_header->urg;
        tcp_info.ip_dst = inet_ntoa(dst_addr.sin_addr);
        tcp_info.ip_src = inet_ntoa(src_addr.sin_addr);
        tcp_info.tcp_payload = tcp_payload + ip_header->ihl * 4 + tcp_header->doff * 4;
        tcp_info.tcp_payload_len = (size - (ip_header->ihl * 4 + tcp_header->doff * 4));
    }
    if (ip6_headers->ip6_nxt == IPPROTO_TCP)
    {
        tcp_info.is_ipv4 = false;
        struct tcphdr *tcp_header = (struct tcphdr *)(tcp_payload + sizeof(struct ip6_hdr));
        tcp_info.src_port = ntohs(tcp_header->th_sport);
        tcp_info.dst_port = ntohs(tcp_header->th_dport);
        char src_ip[INET6_ADDRSTRLEN];
        char dst_ip[INET6_ADDRSTRLEN];
        inet_ntop(AF_INET6, &(ip6_headers->ip6_src), src_ip, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &(ip6_headers->ip6_dst), dst_ip, INET6_ADDRSTRLEN);
        tcp_info.ip_dst = dst_ip;
        tcp_info.ip_src = src_ip;
        tcp_info.tcp_flags.is_ack = tcp_header->ack;
        tcp_info.tcp_flags.is_fin = tcp_header->fin;
        tcp_info.tcp_flags.is_psh = tcp_header->psh;
        tcp_info.tcp_flags.is_syn = tcp_header->syn;
        tcp_info.tcp_flags.is_rst = tcp_header->rst;
        tcp_info.tcp_flags.is_urg = tcp_header->urg;
        tcp_info.tcp_payload = tcp_payload + sizeof(struct ip6_hdr) + sizeof(struct tcphdr);
        tcp_info.tcp_payload_len = size - (sizeof(struct ip6_hdr) + sizeof(struct tcphdr));
    }

    return;
}

/// @brief Show Hex Packet Pyload
/// @param tcp_payload Tcp packet pyload
/// @param size Size of packet pyload
/// @param is_ipv4 is ivp4, default: true.
void tcp::Packet_PayloadDebug(unsigned char *tcp_payload, int size, bool is_ipv4 = true)
{
    printf("Payload TCP (hex): ");
    for (int i = 0; i < (size); ++i)
    {
        printf("%02x ", tcp_payload[i]);
    }
    printf("\n");
}
tcp::tcp()
{
}