#include <pebble.h>

#define NB_OF_POEPLE 100

static Window *window;
static TextLayer *firstname_text_layer;
static TextLayer *surname_text_layer;

typedef struct {
  char firstName[15];
  char surname[15];
} Person;

static Person person;
static int id;

static void getPerson(int id_, Person* person_){
  ResHandle rh = resource_get_handle(RESOURCE_ID_PEOPLE_BIN);
  resource_load_byte_range(rh, id_ * sizeof(Person), (uint8_t*)person_, sizeof(Person));
}

static void update_text(int inc_) {
  id += inc_;
  if(id < 0){
    id = NB_OF_POEPLE - 1;
  }
  if(id == NB_OF_POEPLE){
    id = 0;
  }

  getPerson(id, &person);
  
  text_layer_set_text(firstname_text_layer, person.firstName);
  text_layer_set_text(surname_text_layer, person.surname);
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  update_text(1);
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  update_text(-1);
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  firstname_text_layer = text_layer_create((GRect) { .origin = { 0, 32 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text_alignment(firstname_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(firstname_text_layer));

  surname_text_layer = text_layer_create((GRect) { .origin = { 0, 72 }, .size = { bounds.size.w, 20 } });
  text_layer_set_text_alignment(surname_text_layer, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(surname_text_layer));

  update_text(0);
}

static void window_unload(Window *window) {
  text_layer_destroy(firstname_text_layer);
  text_layer_destroy(surname_text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
