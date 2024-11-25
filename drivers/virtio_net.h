#include <stddef.h>
#include "virtio.h"

static virtio_net_device_t *virtio_dev = NULL;

virtio_net_device_t* init_virtio_net();
