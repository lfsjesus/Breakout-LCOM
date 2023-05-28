#include <lcom/lcf.h>
#include "controller/video/graphics.h"
#include "controller/keyboard_mouse/keyboard.h"
#include "controller/keyboard_mouse/mouse.h"
#include "controller/rtc/rtc.h"
#include "controller/timer/i8254.h"
#include "controller/game/game.h"
#include "controller/serialPort/serialport.h"

extern SystemState systemState;

int (main)(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("");
  lcf_log_output("/home/lcom/labs/gitlab/g4/proj/src/debug/output.txt");
  if (lcf_start(argc, argv)) return 1;
  lcf_cleanup();
  return 0;
}

int init() {
  // Frequency set
  if (timer_set_frequency(0, 60) != OK) return 1;

  // video buffers init
  if (set_frame_buffer(0x115) != OK) return 1;
  if (set_graphics_mode(0x115) != 0) return 1;
  
  if (sp_setup() != 0)  return 1;

  setup_bricks(map1);
  setup_sprites();
  setup_paddle(4);
  setup_ball(2);
  setup_powerups();

  // Interrupts Enabling 
  uint8_t aux_bitno;
  if (timer_subscribe_int(&aux_bitno) != OK) return 1;
  if (keyboard_subscribe_int() != OK) return 1;
  if (mouse_subscribe_int() != OK) return 1;
  if (sp_subscribe_int(&aux_bitno) != 0) return 1;

  // Mouse config
  if (mouse_config(ENABLE_STREAM_MODE) != OK) return 1;
  if (mouse_config(ENABLE_DATA_REPORT) != OK) return 1;

  // RTC Setup (no need for interrupts)
  rtc_config();

  return OK;
}

int teardown() {
  // back to text mode
  if (vg_exit() != OK) return 1;

  destroy_sprites();

  // Disable interrupts
  if (timer_unsubscribe_int() != 0) return 1;
  if (keyboard_unsubscribe_int() != 0) return 1;
  if (mouse_unsubscribe_int() != 0) return 1;
  if (sp_unsubscribe_int() != 0) return 1;

  // Disable mouse report
  if (mouse_config(DISABLE_DATA_REPORT) != 0) return 1;

  return OK;
}

int (proj_main_loop)(int argc, char *argv[]) {
  init();
  int ipc_status;
  message msg;
  while (systemState == RUNNING) {
    
    if (driver_receive(ANY, &msg, &ipc_status) != 0) {
      printf("Error");
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch(_ENDPOINT_P(msg.m_source)) {
        case HARDWARE: 
          if (msg.m_notify.interrupts & BIT(TIMER0_IRQ)) {
            update_timer_state(); 
          }
          if (msg.m_notify.interrupts & BIT(KEYBOARD_IRQ)) {
            update_keyboard_state(); 
          }
          if (msg.m_notify.interrupts & BIT(MOUSE_IRQ)) {
            update_mouse_state();
          }
          if (msg.m_notify.interrupts & BIT(COM1_IRQ))  {
             update_sp_state();
          }

          break;
        }
    }
  }
  teardown();
  return OK;
}
