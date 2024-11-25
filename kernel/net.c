#include "net.h"
#include "mem.h"
#include "print.h"

int net_init(struct net_device *dev) {
    // Initialize the network device (for example, set MAC address)
    printf("Initializing network device %s\n", dev->name);
    // Example MAC address for eth0
    memcpy(dev->mac_addr, "\x00\x1a\x2b\x3c\x4d\x5e", 6);
    return 0;
}

int net_open(struct net_device *dev) {
    printf("Opening network device %s\n", dev->name);
    return 0;
}

int net_stop(struct net_device *dev) {
    printf("Stopping network device %s\n", dev->name);
    return 0;
}

int net_xmit(struct net_device *dev, void *buf, size_t len) {
    // For now, just print the transmitted data
    printf("Transmitting data: ");
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", ((uint8_t *)buf)[i]);
    }
    printf("\n");
    return 0;
}

void net_receive(struct net_device *dev, void *buf, size_t len) {
    // Simulate receiving data (just print the received data)
    printf("Receiving data: ");
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", ((uint8_t *)buf)[i]);
    }
    printf("\n");
}

void setup_network_device(struct net_device *dev) {
    // Set up the network dev
    dev->init = net_init;
    dev->open = net_open;
    dev->stop = net_stop;
    dev->xmit = net_xmit;
    dev->receive = net_receive;

    // Initialize the dev
    dev->init(dev);
    dev->open(dev);
}
