#include <pebble.h>

Window *window;
TextLayer *text_layer;

void init(){ // APP INITIALIZATION
    window = window_create(); // construct window - required for all apps
    window_stack_push(window, true); // push the window to the stack
    text_layer = text_layer_create(GRect(0, 0, 144, 40));  // GRect(x, y, width, height)
    text_layer_set_text(text_layer, "Hello, Pebble!");
    
    layer_add_child(window_get_root_layer(window), // have to set layer as a child 
                    text_layer_get_layer(text_layer));
}

void deinit(){ // APP TEARDOWN
    text_layer_destroy(text_layer);
    window_destroy(window); // This is C, gotta clean up your shit 
}

int main() {
  init();
  app_event_loop(); // this is a special loop to 'wait' for app events, prevents termination
  deinit();
  return 0;
}