#include <hidapi.h>
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

int init_msi_keyboard(void) {
    return hid_init();
}

int free_msi_keyboard(void) {
    return hid_exit();
}

unsigned char *init_data() {
    unsigned char *data = calloc(sizeof(unsigned char), DATA_BUFFER_SIZE);
    data[0] = 1;
    data[1] = 2;
    data[7] = 236;
    return data;
}

int set_color_by_names(const char *region, const char *color, const char *intensity) {
    unsigned char num_region = get_region(region);
    if ( num_region < 0 ) {
        return -1;
    }

    return set_rgb_color(num_region, get_rgb_by_color_name(color), get_intensity_level(intensity));
}

int set_rgb_color(
        unsigned char region,
        struct RGB rgb,
        float intensity_level
        ) {
    hid_device *device = open_device();
    if ( device == NULL ) {
        return -1;
    }

    unsigned char *data = init_data();
    data[2] = 64;
    data[3] = region;
    data[4] = (char)((float)rgb.r * intensity_level);
    data[5] = (char)((float)rgb.g * intensity_level);
    data[6] = (char)((float)rgb.b * intensity_level);
    data[7] = 0;

    int result = hid_send_feature_report(device, data, DATA_BUFFER_SIZE);
    close_device(device);
    if ( result < 0 ) {
        return result;
    }
    free(data);

    return 0;
}

int set_rgb_color_by_name(const char *region, struct RGB rgb, const char *intensity) {
    unsigned char num_region = get_region(region);
    if ( num_region < 0 ) {
        return -1;
    }
    return set_rgb_color(num_region, rgb, get_intensity_level(intensity));
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
    free(data);

    return 0;
}

int set_mode_by_name(const char *mode) {
    unsigned char num_mode = get_mode(mode);
    return set_mode(num_mode);
}

unsigned char get_code_from_list(const char *name, char **list, size_t list_size) {
    if ( list == NULL ) {
        return -2;
    }

    unsigned char result = -1;
    int i;
    for (i=0; i < list_size; i++) {
        if ( strcmp(list[i], name) == 0 ) {
            result = i;
            break;
        }
    }
    free(list);

    return result;
}

unsigned char get_mode(const char *mode_name) {
    if (mode_name == NULL) {
        return -1;
    }

    size_t size;
    char **modes = get_modes(&size);
    unsigned char result = get_code_from_list(mode_name, modes, size);
    result = result < 0 ? 1 : result;
    return result;
}

unsigned char get_region(const char *region_name) {
    if (region_name == NULL) {
        return -1;
    }

    size_t size;
    char **regions = get_regions(&size);
    unsigned char result = get_code_from_list(region_name, regions, size);

    return result;
}

unsigned char get_color(const char *color_name) {
    if (color_name == NULL) {
        return -1;
    }

    size_t size;
    char **colors = get_colors(&size);
    unsigned char result = get_code_from_list(color_name, colors, size);
    result = result < 0 ? 1 : result;
    return result;
}

char **get_intensities(size_t *size) {
    *size = 4;
    char **result;
    result = calloc(sizeof(char*), *size);
    result[0] = "high";
    result[1] = "medium";
    result[2] = "low";
    result[3] = "light";

    return result;
}

float get_intensity_level(const char *intensity) {
    size_t size;
    char **intensities = get_intensities(&size);
    unsigned char result = get_code_from_list(intensity, intensities, size);

    float level;

    switch (result) {
        case 0:
            level = (float)1.0;
            break;
        case 1:
            level = (float)0.75;
            break;
        case 2:
            level = (float)0.50;
            break;
        case 3:
            level = (float)0.25;
            break;
        default:
            level = (float)1.0;
            break;
    }
    return level;
}

char **get_colors(size_t *size) {
    *size = 9;
    char **result;
    result = calloc(sizeof(char*), *size);
    result[0] = "off";
    result[1] = "red";
    result[2] = "orange";
    result[3] = "yellow";
    result[4] = "green";
    result[5] = "sky";
    result[6] = "blue";
    result[7] = "purple";
    result[8] = "white";

    return result;
}

char **get_modes(size_t *size) {
    *size = 6;
    char **result;
    result = calloc(sizeof(char*), *size);
    result[0] = "off";
    result[1] = "normal";
    result[2] = "gaming";
    result[3] = "breathe";
    result[4] = "demo";
    result[5] = "wave";
    return result;
}

char **get_regions(size_t *size) {
    *size = 8;
    char **result;
    result = calloc(sizeof(char*), *size);
    result[0] = "none";
    result[1] = "left";
    result[2] = "middle";
    result[3] = "right";
    result[4] = "logo";
    result[5] = "front_left";
    result[6] = "front_right";
    result[7] = "touchpad";
    return result;

}

struct RGB get_rgb_by_color_name(const char *name) {
    size_t size;
    char **colors = get_colors(&size);
    unsigned char result = get_code_from_list(name, colors, size);

    struct RGB rgb;
    rgb.r = 0;
    rgb.g = 0;
    rgb.b = 0;

    switch (result) {
        case 0:
            break;
        case 1:
            rgb.r = 255;
            break;
        case 2:
            rgb.r = 255;
            rgb.g = 165;
            break;
        case 3:
            rgb.r = 255;
            rgb.g = 255;
            break;
        case 4:
            rgb.g = 128;
            break;
        case 5:
            rgb.g = 255;
            rgb.b = 255;
            break;
        case 6:
            rgb.b = 255;
            break;
        case 7:
            rgb.r = 128;
            rgb.b = 128;
            break;
        case 8:
            rgb.r = 255;
            rgb.g = 255;
            rgb.b = 255;
            break;
        default:
            break;
    }
    return rgb;
}
