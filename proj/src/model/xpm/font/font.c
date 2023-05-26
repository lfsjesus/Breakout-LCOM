#include "font.h"

void init_alphabet_sprites() {
    for (int i = 0; i < 26; i++) {
        alphabet_sprites[i] = create_sprite_xpm(alphabet[i]);
    }
}

void destroy_alphabet_sprites() {
    for (int i = 0; i < 26; i++) {
        destroy_sprite(alphabet_sprites[i]);
    }
}
Sprite* get_char(char c) {
    return alphabet_sprites[c - 'A'];
}
