#include <pebble.h>

static Window *s_main_window;
static TextLayer *s_time_layer;


static void update_time() {
    /*  This only cares about the hour, giving an approximate string value
    *   to describe what time it is. This is best used by people who don't
    *   actually want to know the real time.
    */
    time_t temp = time(NULL); 
    struct tm *tick_time = localtime(&temp);
    
    int hour = tick_time->tm_hour;
    char *s_buffer = malloc(24);

    if(hour < 9) {
        strcpy(s_buffer, "Too Early");
    } else if(hour >= 9 && hour < 11){
        strcpy(s_buffer, "Do Stuff!");
    } else if(hour >= 11 && hour < 12 ){
        strcpy(s_buffer, "Elevensies");
    } else if(hour >= 12 && hour < 13){
        strcpy(s_buffer, "Burrito-O'clock");
    } else if(hour >= 13 && hour < 17){
        strcpy(s_buffer, "2nd Wind");
    } else if(hour >= 17 && hour < 19){
        strcpy(s_buffer, "Supperish");
    } else {
        strcpy(s_buffer, "Party Time, Excellent");
    }
    
    // Display this time on the TextLayer
    text_layer_set_text(s_time_layer, s_buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void main_window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  // Create the TextLayer with specific bounds
  s_time_layer = text_layer_create(GRect(0, PBL_IF_ROUND_ELSE(58, 52), bounds.size.w, 50));

  // Improve the layout to be more like a watchface
  text_layer_set_background_color(s_time_layer, GColorClear);
  text_layer_set_text_color(s_time_layer, GColorBlack);
  text_layer_set_font(s_time_layer, fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21));
  text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

  // Add it as a child layer to the Window's root layer
  layer_add_child(window_layer, text_layer_get_layer(s_time_layer));
}

static void main_window_unload(Window *window) {
    text_layer_destroy(s_time_layer);
}

static void init() {
    s_main_window = window_create();

    // Set handlers to manage the elements inside the Window
    window_set_window_handlers(s_main_window, (WindowHandlers) {
      .load = main_window_load,
      .unload = main_window_unload
    });

    // Show the Window on the watch, with animated=true
    window_stack_push(s_main_window, true);
    // Make sure the time is displayed from the start
    update_time();
    
    // Register with TickTimerService
    tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
}

static void deinit() {
    window_destroy(s_main_window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}