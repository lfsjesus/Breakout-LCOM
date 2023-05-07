#include <lcom/lcf.h>
#include "controller/video/graphics.h"
#include "controller/keyboard_mouse/keyboard.h"
#include "controller/keyboard_mouse/mouse.h"
#include "model/model.h"
#include "model/sprite.h"
#include "view/view.h"
#include "controller/timer/i8254.h"

extern SystemState systemState;

int (main)(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/g4-main/proj/src/debug/trace.txt");
  lcf_log_output("/home/lcom/labs/g4-main/proj/src/debug/output.txt");
  if (lcf_start(argc, argv)) return 1;
  lcf_cleanup();
  return 0;
}

int setup() {
  // Atualização da frequência
  if (timer_set_frequency(0, 60) != 0) return 1;


  // Inicialização dos buffers de vídeo (double buffering)
  if (set_frame_buffer(0x115) != 0) return 1;

  // Inicialização do modo gráfico
  if ( set_graphics_mode(0x115) != 0) return 1;

  // Inicialização dos sprites
  setup_sprites();
  uint8_t hook_id_helper;
  // Ativação das interrupções dos dispositivos
  if (timer_subscribe_int(&hook_id_helper) != 0) return 1;
  if (keyboard_subscribe_int(&hook_id_helper) != 0) return 1;
  if (mouse_subscribe_int(&hook_id_helper) != 0) return 1;
  //if (rtc_subscribe_interrupts() != 0) return 1;

  // Ativar stream-mode e report de dados do rato
  if (mouse_config(ENABLE_STREAM_MODE) != 0) return 1;
  if (mouse_config(ENABLE_DATA_REPORT) != 0) return 1;

  // Setup do Real Time Clock
  //rtc_setup();

  return OK;
}

int teardown() {
  // Volta ao modo de texto
  if (vg_exit() != 0) return 1;

  // Destruição dos sprites
  destroy_sprites();

  // Desativa todas as interrupções
  if (timer_unsubscribe_int() != 0) return 1;
  if (keyboard_unsubscribe_int() != 0) return 1;
  if (mouse_unsubscribe_int() != 0) return 1;
  //if (rtc_unsubscribe_interrupts() != 0) return 1;

  // Desativar o report de dados do rato
  if (mouse_config(DISABLE_DATA_REPORT) != 0) return 1;

  return OK;
}

int (proj_main_loop)(int argc, char *argv[]) {
  setup();

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
          //printf("Interrupt: %d\n", msg.m_notify.interrupts);
          if (msg.m_notify.interrupts & BIT(TIMER0_IRQ))   update_timer_state();    //troca buffers
          if (msg.m_notify.interrupts & BIT(KEYBOARD_IRQ)) update_keyboard_state(); 
          if (msg.m_notify.interrupts & BIT(MOUSE_IRQ))    update_mouse_state();
          break;
          //if (msg.m_notify.interrupts & RTC_IRQ)      update_rtc_state(); 
        }
    }
  }
  teardown();
  return OK;
}
