#include "net.h"
// #include "pci.h"
#include "../kernel/mem.h"
#include "../kernel/print.h"


struct net_device device;

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

void setup_network_device() {
    // uint8_t mac[6];
    // get_mac_address(mac);
    unsigned char mac[6] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F};
    printf("Address MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    // Set up the network device
    device.name = "eth0";
    device.init = net_init;
    device.open = net_open;
    device.stop = net_stop;
    device.xmit = net_xmit;
    device.receive = net_receive;

    // Initialize the device
    device.init(&device);
    device.open(&device);
}
