#include <stdio.h>
#include <libusb.h>

int main()
{
    // Find the USB device
    struct usb_device *dev = NULL;
    struct usb_bus *bus;
    usb_init();
    usb_find_busses();
    usb_find_devices();
    for (bus = usb_get_busses(); bus; bus = bus->next) {
        for (dev = bus->devices; dev; dev = dev->next) {
            if (dev->descriptor.idVendor == 0x05ac && dev->descriptor.idProduct == 0x12a8) {
                break;
            }
        }
    }
    if (!dev) {
        printf("Device not found\n");
        return 1;
    }

    // Open the device
    usb_dev_handle *handle = usb_open(dev);
    if (!handle) {
        printf("Cannot open device\n");
        return 1;
    }

    // Send a key press
    int result = usb_control_msg(handle, USB_TYPE_CLASS + USB_RECIP_INTERFACE, 0x09, 0x200, 0, "a", 1, 1000);
    if (result < 0) {
        printf("Error sending key press: %s\n", usb_strerror());
    }

    // Close the device
    usb_close(handle);

    return 0;
}
