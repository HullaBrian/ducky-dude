#include <stdio.h>
#include <libusb-1.0/libusb.h>

int main() {
    libusb_context *ctx = NULL;
    libusb_device **list;
    libusb_init(&ctx);
    ssize_t count = libusb_get_device_list(ctx, &list);
    for (int i = 0; i < count; i++) {
        libusb_device *device = list[i];
        struct libusb_device_descriptor desc;
        libusb_get_device_descriptor(device, &desc);
        printf("Vendor ID: %04x, Product ID: %04x\n", desc.idVendor, desc.idProduct);
    }
    libusb_free_device_list(list, 1);
    libusb_exit(ctx);
    return 0;
}
