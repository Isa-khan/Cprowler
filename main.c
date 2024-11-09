#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pcap.h>

void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr, const u_char *packet) {

    struct ether_header *eth_header = (struct ether_header *)packet;
    char src_mac[18];
    char dst_mac[18];
    
    snprintf(src_mac, sizeof(src_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
             eth_header->ether_shost[0], eth_header->ether_shost[1],
             eth_header->ether_shost[2], eth_header->ether_shost[3],
             eth_header->ether_shost[4], eth_header->ether_shost[5]);
    
    snprintf(dst_mac, sizeof(dst_mac), "%02x:%02x:%02x:%02x:%02x:%02x",
             eth_header->ether_dhost[0], eth_header->ether_dhost[1],
             eth_header->ether_dhost[2], eth_header->ether_dhost[3],
             eth_header->ether_dhost[4], eth_header->ether_dhost[5]);
    
    printf("\nEthernet Frame:");
    printf("\nDestination: %s", dst_mac);
    printf("\nSource: %s", src_mac);
    printf("\nType: 0x%04x\n", ntohs(eth_header->ether_type));
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t *handle;
    
    char *dev = pcap_lookupdev(errbuf);
    if (dev == NULL) {
        fprintf(stderr, "Couldn't find default device: %s\n", errbuf);
        return 1;
    }
    
    printf("Device: %s\n", dev);
    
    handle = pcap_open_live(dev, BUFSIZ, 1, 1000, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return 1;
    }
    
    printf("Starting packet capture. Press Ctrl+C to stop.\n");
    pcap_loop(handle, 0, packet_handler, NULL);
    
    pcap_close(handle);
    return 0;
}