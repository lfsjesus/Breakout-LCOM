#ifndef _LCOM_MODEL_H_
#define _LCOM_MODEL_H_

#include <minix/sysutil.h>
#include <lcom/lcf.h>
#include "../controller/keyboard_mouse/keyboard.h"
#include "../controller/keyboard_mouse/mouse.h"
#include "../controller/video/graphics.h"
#include "xpm/mouse.xpm"
#include "../view/view.h"
#include "../model/sprite.h"

void setup_sprites();
void destroy_sprites();
void update_keyboard_state();
void update_mouse_state();
void update_timer_state();


typedef enum {
    RUNNING,
    EXIT,
} SystemState;

typedef enum {
    START,
    GAME,
    END
} MenuState;


#endif
