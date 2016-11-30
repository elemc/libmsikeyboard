#include <hidapi/hidapi.h>
#include <stdlib.h>
#include <string.h>
#include "msikeyboard.h"

#define MSI_KEYBOARD_VENDOR_ID 0x1770
#define MSI_KEYBOARD_PRODUCT_ID 0xff00

#define DATA_BUFFER_SIZE 8

hid_device *open_device() {
    return hid_open(MSI_KEYBOARD_VENDOR_ID, MSI_KEYBOARD_PRODUCT_ID, 0);
}

void close_device(hid_device *device) {
    hid_close(device);
}

int init_msi_keyboard() {
    return hid_init();
}

int free_msi_keyboard() {
    return hid_exit();
}

unsigned char *init_data() {
    unsigned char *data = calloc(sizeof(unsigned char), DATA_BUFFER_SIZE);
    data[0] = 1;
    data[1] = 2;
    data[7] = 236;
    return data;
}

int set_color(unsigned char region, unsigned char color, unsigned char intensity) {
    hid_device *device = open_device();
    if ( device == NULL ) {
        return -1;
    }

    unsigned char *data = init_data();
    data[2] = 66;
    data[3] = region;
    data[4] = color;
    data[5] = intensity;

    int result = hid_send_feature_report(device, data, DATA_BUFFER_SIZE);
    close_device(device);
    if ( result < 0 ) {
        return result;
    }

    return 0;
}

int set_color_by_names(const char *region, const char *color, const char *intensity) {
    unsigned char num_region = get_region(region);
    if ( num_region < 0 ) {
        return -1;
    }
    unsigned char num_color = get_color(color);
    unsigned char num_instensity = get_intensity(intensity);

    return set_color(num_region, num_color, num_instensity);
}

int set_rgb_color(unsigned char region, unsigned char r, unsigned char g, unsigned char b) {
    hid_device *device = open_device();
    if ( device == NULL ) {
        return -1;
    }

    unsigned char *data = init_data();
    data[2] = 64;
    data[3] = region;
    data[4] = r;
    data[5] = g;
    data[6] = b;

    int result = hid_send_feature_report(device, data, DATA_BUFFER_SIZE);
    close_device(device);
    if ( result < 0 ) {
        return result;
    }

    return 0;
}

int set_rgb_color_by_name(const char *region, unsigned char r, unsigned char g, unsigned char b) {
    unsigned char num_region = get_region(region);
    if ( num_region < 0 ) {
        return -1;
    }
    return set_rgb_color(num_region, r,  g, b);
}

int set_mode(unsigned char mode) {
    hid_device *device = open_device();
    if ( device == NULL ) {
        return -1;
    }

    unsigned char *data = init_data();
    data[2] = 65;
    data[3] = mode;

    int result = hid_send_feature_report(device, data, DATA_BUFFER_SIZE);
    close_device(device);
    if ( result < 0 ) {
        return result;
    }

    return 0;
}

int set_mode_by_name(const char *mode) {
    unsigned char num_mode = get_mode(mode);
    return set_mode(num_mode);
}

unsigned char get_mode(const char *mode_name) {
    if (mode_name == NULL) {
        return -1;
    }

    if ( strcmp(mode_name, "gaming") == 0 )
        return 2;
    else if ( strcmp(mode_name, "breathe") == 0 )
        return 3;
    else if ( strcmp(mode_name, "demo") == 0 )
        return 4;
    else if ( strcmp(mode_name, "wave") == 0 )
        return 5;

    return 1;
}

unsigned char get_region(const char *region_name) {
    if (region_name == NULL) {
        return -1;
    }

    if ( strcmp(region_name, "left") == 0 )
        return 1;
    else if ( strcmp(region_name, "middle") == 0 )
        return 2;
    else if ( strcmp(region_name, "right") == 0 )
        return 3;
    else if ( strcmp(region_name, "logo") == 0 )
        return 4;
    else if ( strcmp(region_name, "front_left") == 0 )
        return 5;
    else if ( strcmp(region_name, "front_right") == 0 )
        return 6;
    else if ( strcmp(region_name, "touchpad") == 0 )
        return 7;

    return -1;
}

unsigned char get_color(const char *color_name) {
    if (color_name == NULL) {
        return -1;
    }

    if ( strcmp(color_name, "off") == 0 )
        return 0;
    else if ( strcmp(color_name, "red") == 0 )
        return 1;
    else if ( strcmp(color_name, "orange") == 0 )
        return 2;
    else if ( strcmp(color_name, "yellow") == 0 )
        return 3;
    else if ( strcmp(color_name, "green") == 0 )
        return 4;
    else if ( strcmp(color_name, "sky") == 0 )
        return 5;
    else if ( strcmp(color_name, "blue") == 0 )
        return 6;
    else if ( strcmp(color_name, "purple") == 0 )
        return 7;
    else if ( strcmp(color_name, "white") == 0 )
        return 8;

    return 0;
}

unsigned char get_intensity(const char *name) {
    if (name == NULL) {
        return -1;
    }

    if ( strcmp(name, "high") == 0 )
        return 0;
    else if ( strcmp(name, "medium") == 0 )
        return 1;
    else if ( strcmp(name, "low") == 0 )
        return 2;
    else if ( strcmp(name, "light") == 0 )
        return 3;

    return 0;
}
