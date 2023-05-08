#include "model.h"
#include <lcom/lcf.h>

// Variáveis externas importantes à construção e manipulação do modelo
extern uint8_t scancode;
extern uint8_t packet_counter;
SystemState systemState = RUNNING;
MenuState menuState = START;
extern vbe_mode_info_t mode_info;

Sprite* mouse;
Sprite* background;
Sprite* button_singleplayer;
Sprite* button_multiplayer;
Sprite* button_leaderboard;
Sprite* button_settings;

void setup_sprites() {
    mouse = create_sprite_xpm((xpm_map_t) mouse_xpm);
    background = create_sprite_xpm((xpm_map_t) menu_background_xpm);
    button_singleplayer = create_sprite_xpm((xpm_map_t) singleplayer_button_xpm);
    button_multiplayer = create_sprite_xpm((xpm_map_t) multiplayer_button_xpm);
    button_leaderboard = create_sprite_xpm((xpm_map_t) leaderboard_button_xpm);
    button_settings = create_sprite_xpm((xpm_map_t) settings_button_xpm);
}

void destroy_sprites() {
  destroy_sprite(mouse);
}

void update_keyboard_state() {
    (kbc_ih)();
    switch (scancode) {
        case ESC_BK_CODE:
            systemState = EXIT;
            break;
            }
}

void update_mouse_state() {
    mouse_ih();
    mouse_sync();
    if (packet_counter == 3) {
        sync_mouse_info();
    }
}

void update_timer_state() {
    vg_set_start();
    clear_screen();
    draw_new_frame();
}
