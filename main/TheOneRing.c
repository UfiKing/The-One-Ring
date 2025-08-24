#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "esp_log.h"
#include "esp_err.h"

//#define LED_COUNT 71
#define LED_STRIP_MEMORY_BLOCK_WORDS 0
#define LED_STRIP_USE_DMA 0 
#define LED_STRIP_GPIO_PIN 14

uint8_t LED_COUNT = 71;
// 10MHz resolution 1 tick = 0.1us 
#define LED_STRIP_RMT_RES_HZ (10 * 1000 * 1000)

static const char* TAG = "The One Ring";

led_strip_handle_t configure_led(void){

  led_strip_config_t strip_config = {
    .strip_gpio_num = LED_STRIP_GPIO_PIN, //the gpio pin that connects to the DIN
    .max_leds = LED_COUNT,
    .led_model = LED_MODEL_WS2812,
    .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
    .flags = {
      .invert_out = false,
    }
  };

  led_strip_rmt_config_t rmt_config = {
    .clk_src = RMT_CLK_SRC_DEFAULT, 
    .resolution_hz = LED_STRIP_RMT_RES_HZ,
    .mem_block_symbols = LED_STRIP_MEMORY_BLOCK_WORDS,
    .flags = {
      .with_dma = LED_STRIP_USE_DMA,
    }
  };

  led_strip_handle_t led_strip;
  ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
  ESP_LOGI(TAG, "Created LED strip object");
  return led_strip;


}

void breathe(uint16_t delay){
  
     for(uint8_t i = 1; i != 0; i ++){
       for(uint8_t j = 0; j < LED_COUNT; j++){
         led_strip_set_pixel(led_strip, j, i, i, i);
       }
       led_strip_refresh(led_strip);
       vTaskDelay(delay / portTICK_PERIOD_MS);
     }
     for(uint8_t i = 255; i != 0 ; i --){
       for(uint8_t j = 0; j < LED_COUNT; j++){
         led_strip_set_pixel(led_strip, j, i, i, i);
       }
       led_strip_refresh(led_strip);
       vTaskDelay(delay / portTICK_PERIOD_MS);
     }
    
  
}


void app_main(void){
  led_strip_handle_t led_strip = configure_led();
  led_strip_clear(led_strip);

  while(1){
     
  

  }

  
  

}

