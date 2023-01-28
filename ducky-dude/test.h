#include <stdio.h>
#include <libusb-1.0/libusb.h>

// #define VENDOR_ID 0x1d34 // replace with your device's vendor ID
// #define PRODUCT_ID 0x0013 // replace with your device's product ID

int inject_2(int VENDOR_ID, int PRODUCT_ID)
{
    libusb_device_handle* handle;
    int sent_bytes;

    libusb_init(NULL);

    handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);

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
