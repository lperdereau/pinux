#pragma once
#include <stdint.h>
#include <stddef.h>

struct net_device {
    char *name;             // Network device name, e.g., eth0
    uint8_t mac_addr[6];    // MAC address
    int (*init)(struct net_device *dev);   // Device initialization function
    int (*open)(struct net_device *dev);   // Open device for use
    int (*stop)(struct net_device *dev);   // Stop device
    int (*xmit)(struct net_device *dev, void *buf, size_t len); // Transmit data
    void (*receive)(struct net_device *dev, void *buf, size_t len); // Receive data
    void *priv;  // Private data for the device (e.g., driver-specific)
};

struct arp_entry {
    uint32_t ip_addr;        // Adresse IP (en big-endian)
    uint8_t mac_addr[6];     // Adresse MAC correspondante
};

#define ARP_TABLE_SIZE 16
// struct arp_entry arp_table[ARP_TABLE_SIZE];

struct arp_packet {
    uint16_t hw_type;     // Type matériel (1 = Ethernet)
    uint16_t proto_type;  // Type de protocole (0x0800 = IPv4)
    uint8_t hw_size;      // Taille de l'adresse matérielle (6 pour MAC)
    uint8_t proto_size;   // Taille de l'adresse protocole (4 pour IPv4)
    uint16_t opcode;      // 1 = requête, 2 = réponse
    uint8_t sender_mac[6]; // Adresse MAC de l'émetteur
    uint32_t sender_ip;    // Adresse IP de l'émetteur
    uint8_t target_mac[6]; // Adresse MAC du destinataire
    uint32_t target_ip;    // Adresse IP du destinataire
};

void setup_network_device();
