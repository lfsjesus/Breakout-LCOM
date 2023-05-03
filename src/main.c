#include <lcom/lcf.h>

int (main)(int argc, char *argv[]) {
  lcf_set_language("EN-US");
  lcf_trace_calls("/home/lcom/labs/Template/debug/trace.txt");
  lcf_log_output("/home/lcom/labs/Template/debug/output.txt");
  if (lcf_start(argc, argv)) return 1;
  lcf_cleanup();
  return 0;
}

int setup() {
  /* TODO 
  // Atualização da frequência
  if (timer_set_frequency(TIMER, GAME_FREQUENCY) != 0) return 1;

  // Inicialização dos buffers de vídeo (double buffering)
  if (set_frame_buffers(VIDEO_MODE) != 0) return 1;

  // Inicialização do modo gráfico
  if (set_graphic_mode(VIDEO_MODE) != 0) return 1;

  // Inicialização dos sprites
  setup_sprites();

  // Ativação das interrupções dos dispositivos
  if (timer_subscribe_interrupts() != 0) return 1;
  if (keyboard_subscribe_interrupts() != 0) return 1;
  if (mouse_subscribe_interrupts() != 0) return 1;
  if (rtc_subscribe_interrupts() != 0) return 1;

  // Ativar stream-mode e report de dados do rato
  if (mouse_write(ENABLE_STREAM_MODE) != 0) return 1;
  if (mouse_write(ENABLE_DATA_REPORT) != 0) return 1;

  // Setup do Real Time Clock
  rtc_setup();
  */

  return OK;
}

int teardown() {
  /* TO DO
  // Volta ao modo de texto
  if (vg_exit() != 0) return 1;

  // Destruição dos sprites
  destroy_sprites();

  // Desativa todas as interrupções
  if (timer_unsubscribe_interrupts() != 0) return 1;
  if (keyboard_unsubscribe_interrupts() != 0) return 1;
  if (mouse_unsubscribe_interrupts() != 0) return 1;
  if (rtc_unsubscribe_interrupts() != 0) return 1;

  // Desativar o report de dados do rato
  if (mouse_write(DISABLE_DATA_REPORT) != 0) return 1;
  */ 
  return OK;
}

int (proj_main_loop)(int argc, char *argv[]) {

  return OK;
}
