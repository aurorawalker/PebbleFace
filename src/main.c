#include <pebble.h>

Window *window;

void init(){ // APP INITIALIZATION
window = window_create(); // construct window - required for all apps
window_stack_push(window, true); // push the window to the stack
}

void deinit(){ // APP TEARDOWN
    
}

int main() {
  init();
  app_event_loop(); // this is a special loop to 'wait' for app events, prevents termination
  deinit();
  return 0;
}