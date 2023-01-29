#include <stdio.h>
#include <libusb-1.0/libusb.h>

// #define VENDOR_ID 0x1d34 // replace with your device's vendor ID
// #define PRODUCT_ID 0x0013 // replace with your device's product ID

int inject_2(uint16_t VENDOR_ID, uint16_t PRODUCT_ID)
{
    printf("[INJECTOR]: Preparing to inject keys...\n");
    int sent_bytes;

    printf("[INJECTOR]: Initializing usb device...\n");
    libusb_device_handle* handle;
    libusb_context *ctx = NULL;
    int init = libusb_init(&ctx);
    if (init < 0) {
        errx(1,"\n\nERROR: Cannot Initialize libusb\n\n");
    }

    printf("[INJECTOR]: Preparing to open usb connection with a vendor id of '" "%"SCNd16", and product id of '" "%"SCNd16 "'\n", VENDOR_ID, PRODUCT_ID);
    handle = libusb_open_device_with_vid_pid(ctx, VENDOR_ID, PRODUCT_ID);
    printf("[INJECTOR]: Initialized the usb device!\n");

    if (handle == NULL) {
        printf("Failed to open device.\n");
        return 1;
    }

    if (libusb_kernel_driver_active(handle, 0)) {
        libusb_detach_kernel_driver(handle, 0);
    }

    libusb_claim_interface(handle, 0);

    // send key strokes here
    char key_strokes[] = {'h','e','l','l','o',' ','w','o','r','l','d','!'};
    libusb_interrupt_transfer(handle, 0x01, key_strokes, sizeof(key_strokes), &sent_bytes, 0);

    libusb_release_interface(handle, 0);
    libusb_attach_kernel_driver(handle, 0);
    libusb_close(handle);
    libusb_exit(NULL);
    return 0;
}
