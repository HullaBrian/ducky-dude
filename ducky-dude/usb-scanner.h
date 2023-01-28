
int scan() {
    struct libusb_device_descriptor desc;
    libusb_context *ctx = NULL;
    libusb_device **list;

    int init = libusb_init(&ctx);
    if (init < 0) {
        errx(1,"\n\nERROR: Cannot Initialize libusb\n\n");
    }

    ssize_t count = libusb_get_device_list(ctx, &list);
    for (int i = 0; i < count; i++) {
        libusb_device *device = list[i];
        libusb_get_device_descriptor(device, &desc);
        printf("[DEVICE LOGGER]: Vendor ID: %04x, Product ID: %04x\n", desc.idVendor, desc.idProduct);
    }
    libusb_free_device_list(list, 1);
    libusb_exit(ctx);

    return 0;
}
