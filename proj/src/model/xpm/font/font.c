#include "font.h"

void init_alphabet_sprites() {
    for (int i = 0; i < 26; i++) {
        alphabet_sprites[i] = create_sprite_xpm(alphabet[i]);
    }
    twoPoints = create_sprite_xpm((xpm_map_t) colon);
    slashSprite = create_sprite_xpm((xpm_map_t) slash);
}

void init_number_sprites() {
    for (int i = 0; i < 10; i++) {
        number_sprites[i] = create_sprite_xpm(digits[i]);
    }
}

void destroy_alphabet_sprites() {
    for (int i = 0; i < 26; i++) {
        destroy_sprite(alphabet_sprites[i]);
    }
    destroy_sprite(twoPoints);
    destroy_sprite(slashSprite);
}

void destroy_number_sprites() {
    for (int i = 0; i < 10; i++) {
        destroy_sprite(number_sprites[i]);
    }
}

Sprite* get_char(char c) {
    return alphabet_sprites[c - 'A'];
}

Sprite* get_number(char c) {
    return number_sprites[c - '0'];
}
