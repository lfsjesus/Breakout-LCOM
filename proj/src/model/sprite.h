#ifndef _LCOM_SPRITE_H_
#define _LCOM_SPRITE_H_

#include "../controller/video/graphics.h"

/**
 * @brief Struct for Sprite objects
 */
typedef struct {
    uint16_t height;        /**< Height of the sprite. */
    uint16_t width;         /**< Width of the sprite. */
    uint32_t *colors;       /**< Pointer to the color map of the sprite. */
} Sprite; 

/**
 * @brief Builds a sprite with a XPM with colors in direct mode
 * @param sprite 
 * @return pointer to the sprite created
 */
Sprite *create_sprite_xpm(xpm_map_t sprite);

/**
 * @brief Destroys a sprite
 * @param sprite a pointer to the sprite that will be destroyed
 */
void destroy_sprite(Sprite *sprite);

#endif
