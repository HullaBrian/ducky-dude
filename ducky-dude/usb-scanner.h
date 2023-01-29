int get_usb_devices(libusb_device ***list, bool is_verbose) {
    libusb_device **device_list;
    int device_count;
    int rc;

    if (is_verbose){ printf("[DEBUG]: Initializing libusb...\n"); }
    rc = libusb_init(NULL);
    if (rc < 0) {
        if (is_verbose){ printf("[DEBUG]: Error initializing libusb!\n"); }
        return rc;
    }
    if (is_verbose){ printf("[DEBUG]: Initialized libusb!\n"); }

    if (is_verbose){ printf("[DEBUG]: Retrieving list of usb devices..."); }
    device_count = libusb_get_device_list(NULL, &device_list);
    if (device_count < 0) {
        if (is_verbose){ printf("\n[ERROR]: Could not retrieve list of usb devices!"); }
        libusb_exit(NULL);
        return device_count;
    }
    if (is_verbose){ printf("Done!\n"); }

    *list = device_list;
    return device_count;
}

int scan(bool is_verbose) {
    libusb_device **device_list;
    int device_count;

    device_count = get_usb_devices(&device_list, is_verbose);
    if (device_count < 0) {
        printf("Error: %s\n", libusb_strerror(device_count));
        return 1;
    }

    for (int i = 0; i < device_count; i++) {
        struct libusb_device *device = device_list[i];
        struct libusb_device_descriptor descriptor;
        int rc;

        rc = libusb_get_device_descriptor(device, &descriptor);
        if (rc < 0) {
            printf("Error: %s\n", libusb_strerror(rc));
            continue;
        }

        printf("[DEVICE LOGGER]: Vendor ID: %04x, Product ID: %04x\n", descriptor.idVendor, descriptor.idProduct);
    }
    printf("[DEVICE LOGGER]: Found %d USB devices!\n", device_count);

    libusb_free_device_list(device_list, 1);
    libusb_exit(NULL);
    return 0;
}