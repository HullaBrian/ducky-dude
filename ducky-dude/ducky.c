#include <stdio.h>
#include <libusb-1.0/libusb.h>
#include <err.h>
#include <inttypes.h>
#include <string.h>
#include <stdbool.h>
#include "usb-scanner.h"
#include "test.h"
//#include "send-keys.h"

bool val_in_list(char *list, char val[]){
    for(int i = 0; i < sizeof(&list); i++){
        if (strcmp(list[i], val) == 0){
            return true;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    if (argc < 2){
        printf("No parameters were given!\n");
        return 1;
    }

    // Searching for verbose flag
    bool is_verbose = false;
    if (val_in_list(argv, "--verbose")){
        is_verbose = true;
    }

    if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0){
        printf("HELP!\n");
    }
    else if (strcmp(argv[1], "--scan") == 0 || strcmp(argv[1], "-s") == 0){
        scan(is_verbose);
    }
    else{
        inject_2(*argv[1], *argv[2]);
    }

    uint16_t vendor_id;
    uint16_t product_id;
    for(int i = 0; argv[i]; i++){
        if(strcmp(argv[i], "--vid") == 0 || strcmp(argv[i], "-v") == 0) {
            sscanf(argv[i], "%" SCNd16, &vendor_id);
        }
        else if (strcmp(argv[i], "--pid") == 0 || strcmp(argv[i], "-p") == 0) {
            sscanf(argv[i], "%" SCNd16, &product_id);
        }
    }

    return 0;
}
