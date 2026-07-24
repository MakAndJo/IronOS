#include "OperatingModes.h"
#include "ui_drawing.hpp"

OperatingMode showDebugMenu(const ButtonState buttons, guiContext *cxt) {

  if (cxt->scratch_state.state3 == 0) {
    cxt->scratch_state.state3 = 1;
    if (buttons != BUTTON_NONE) {
      ui_draw_debug_menu(cxt->scratch_state.state1);
      return OperatingMode::DebugMenuReadout;
    }
  }

  ui_draw_debug_menu(cxt->scratch_state.state1);

  switch (buttons) {
  case BUTTON_B_SHORT:
    cxt->scratch_state.state1++;
#ifdef HALL_SENSOR
    cxt->scratch_state.state1 = cxt->scratch_state.state1 % 17;
#else
    cxt->scratch_state.state1 = cxt->scratch_state.state1 % 16;
#endif
    break;
  case BUTTON_F_SHORT:
    if (cxt->scratch_state.state1 == 0) {
#ifdef HALL_SENSOR
      cxt->scratch_state.state1 = 16;
#else
      cxt->scratch_state.state1 = 15;
#endif
    } else {
      cxt->scratch_state.state1--;
    }
    break;
  case BUTTON_BOTH:
  case BUTTON_BOTH_LONG:
    cxt->transitionMode = TransitionAnimation::Up;
    return OperatingMode::HomeScreen;
    break;
  default:
    break;
  }
  return OperatingMode::DebugMenuReadout;
}
