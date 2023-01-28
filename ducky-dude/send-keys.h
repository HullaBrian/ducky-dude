
int inject(char *vendor_id, char *product_id) {
    // Find the USB device
    libusb_context *ctx = NULL;
    libusb_device **list;
    struct libusb_device *dev = NULL;
    struct libusb_bus *bus;
    libusb_device_handle *dev_handle = NULL;

    libusb_init(&ctx);
    libusb_get_device(&dev_handle);
    for (bus = libusb_get_pollfds(&&ctx); bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {
            if (dev->descriptor.idVendor == 0x1234 && dev->descriptor.idProduct == 0x5678) {
                break;
            }
        }
    }
    if (!dev) {
        printf("Device not found\n");
        return 1;
    }

    // Open the device
    libusb_device_handle *handle = libusb_open(dev, &dev_handle);
    if (!handle) {
        printf("Cannot open device\n");
        return 1;
    }

    // Send a key press
    int result = libusb_control_transfer(handle, LIBUSB_TYPE_CLASS + LIBUSB_RECIPIENT_INTERFACE, 0x09, 0x200, 0, "a", 1, 1000);
    if (result < 0) {
        printf("Error sending key press: %s\n", libusb_strerror(1));
    }

    // Close the device
    libusb_close(handle);

    return 0;
}