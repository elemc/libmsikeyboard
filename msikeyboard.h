#ifndef MSIKEYBOARD_H__
#define MSIKEYBOARD_H__

#ifdef __cplusplus
extern "C" {
#endif

#include<unistd.h>
#include<stddef.h>

struct RGB {
    unsigned char r;
    unsigned char g;
    unsigned char b;
};

int init_msi_keyboard(void);
int free_msi_keyboard(void);

int set_color(unsigned char region, unsigned char color, unsigned char intensity);
int set_color_by_names(const char *region, const char *color, const char *intensity);
int set_rgb_color(
        unsigned char region,
        struct RGB rgb,
        float intensity_level
        );
int set_rgb_color_by_name(const char *region, struct RGB rgb, const char  *intensity);
int set_mode(unsigned char mode);
int set_mode_by_name(const char *mode);

unsigned char get_mode(const char *mode_name);
unsigned char get_region(const char *region_name);
unsigned char get_color(const char *color_name);
unsigned char get_intensity(const char *name);

char **get_intensities(size_t *size);
char **get_colors(size_t *size);
char **get_modes(size_t *size);
char **get_regions(size_t *size);

float get_intensity_level(const char *intensity);

struct RGB get_rgb_by_color_name(const char *name);

#ifdef __cplusplus
}
#endif


#endif
