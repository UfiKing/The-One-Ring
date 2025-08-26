#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "led_strip.h"
#include "esp_log.h"
#include "esp_err.h"
#include "esp_random.h"
#include "bootloader_random.h"

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

void breathe(led_strip_handle_t led_strip, uint16_t delay){
  
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

void spin(led_strip_handle_t led_strip, uint16_t delay){
  for(uint8_t i = 0; i < LED_COUNT; i ++){

    led_strip_set_pixel(led_strip, i, 255, 255, 255);

      //led_strip_clear(led_strip);
    if(i - 1 == - 1){
      led_strip_set_pixel(led_strip, LED_COUNT - 1, 200, 200, 150);
      led_strip_set_pixel(led_strip, LED_COUNT - 2, 150, 150, 100);
      led_strip_set_pixel(led_strip, LED_COUNT - 3, 100, 100, 050);
      led_strip_set_pixel(led_strip, LED_COUNT - 4, 050, 050, 000);
      led_strip_set_pixel(led_strip, LED_COUNT - 5, 0,0,0);
    }else if(i - 2 == - 1){
      led_strip_set_pixel(led_strip, LED_COUNT - 1, 150, 150, 100);
      led_strip_set_pixel(led_strip, LED_COUNT - 2, 100, 100, 050);
      led_strip_set_pixel(led_strip, LED_COUNT - 3, 050, 050, 000);
      led_strip_set_pixel(led_strip, LED_COUNT - 4, 0,0,0);
    }else if(i - 3 == -1){
      led_strip_set_pixel(led_strip, LED_COUNT - 1, 100, 100, 050);
      led_strip_set_pixel(led_strip, LED_COUNT - 2, 050, 050, 000);
      led_strip_set_pixel(led_strip, LED_COUNT - 3, 0,0,0);
    }else if(i - 4 == - 1){
      led_strip_set_pixel(led_strip, LED_COUNT - 1, 50, 50, 00);
      led_strip_set_pixel(led_strip, LED_COUNT - 2, 0,0,0);
    }else if(i - 5 == 0){
      led_strip_set_pixel(led_strip, LED_COUNT - 1, 0,0,0);
    }else if(i + 1 == LED_COUNT){
      led_strip_set_pixel(led_strip, 0, 200, 200, 150);
      led_strip_set_pixel(led_strip, 1 , 150, 150, 100);
      led_strip_set_pixel(led_strip, 2, 100, 100, 050);
      led_strip_set_pixel(led_strip, 3, 050, 050, 000);
      led_strip_set_pixel(led_strip, 4, 0,0,0);
    }else if(i + 2 == LED_COUNT){
      led_strip_set_pixel(led_strip,0, 150, 150, 100);
      led_strip_set_pixel(led_strip,1, 100, 100, 050);
      led_strip_set_pixel(led_strip,2, 050, 050, 000);
      led_strip_set_pixel(led_strip,3,0,0,0);
    }else if(i + 3 == LED_COUNT){
      led_strip_set_pixel(led_strip, 0, 100, 100, 050);
      led_strip_set_pixel(led_strip, 1, 050, 050, 000);
      led_strip_set_pixel(led_strip, 2, 0,0,0);
    }else if(i + 4 == LED_COUNT){
      led_strip_set_pixel(led_strip, 0, 50, 50, 00);
      led_strip_set_pixel(led_strip, 1, 0,0,0);
    }
    led_strip_set_pixel(led_strip, i - 4, 050, 050, 000);
    led_strip_set_pixel(led_strip, i - 3, 100, 100, 050);
    led_strip_set_pixel(led_strip, i - 2, 150, 150, 100);
    led_strip_set_pixel(led_strip, i - 1, 200, 200, 150);     
      
    led_strip_set_pixel(led_strip, i + 1, 200, 200, 150);
    led_strip_set_pixel(led_strip, i + 2, 150, 150, 100);
    led_strip_set_pixel(led_strip, i + 3, 100, 100, 050);
    led_strip_set_pixel(led_strip, i + 4, 050, 050, 000);
      
    led_strip_set_pixel(led_strip, i - 5, 0,0,0);
    led_strip_set_pixel(led_strip, i + 5, 0,0,0);
    
    led_strip_refresh(led_strip);
    vTaskDelay(50  / portTICK_PERIOD_MS);

  }
}

void lavaV1(led_strip_handle_t led_strip, uint16_t delay){
  for(int i = 0; i < LED_COUNT; i++){
    uint32_t rand = esp_random();
    led_strip_set_pixel(led_strip, i, rand & 0b11111111,(rand >> 8) & 0b11111111, (rand >> 16 ) & 0b11111111);
  }
  //led_strip_refresh(led_strip);
  vTaskDelay(delay / portTICK_PERIOD_MS);  

}

void app_main(void){
  led_strip_handle_t led_strip = configure_led();
  led_strip_clear(led_strip);
  bootloader_random_enable();

  uint8_t targets[LED_COUNT][3];
  uint16_t steps = 25;
  for(uint8_t i = 0; i < LED_COUNT; i++){
    targets[i][0] = esp_random() & 0b11111111;
    targets[i][1] = targets[i][0];
    targets[i][2] = esp_random() & 0b11111111;
    led_strip_set_pixel(led_strip, i, targets[i][1], targets[i][1], targets[i][1]);
  }
  while(1){
    for(uint8_t i = 0; i < LED_COUNT; i++){
      targets[i][0] = targets[i][1];
      targets[i][2] = esp_random() & 0b11111111;
      led_strip_set_pixel(led_strip, i, targets[i][1], targets[i][1], targets[i][1]);
    }   
    led_strip_refresh(led_strip);
    for(uint8_t j = 0; j < steps; j++){
      for(uint8_t i = 0; i < LED_COUNT; i++){
        int16_t change = targets[i][2] - targets[i][0];
        change = change / 10;
        targets[i][1] = targets[i][1] + change;
        led_strip_set_pixel(led_strip, i, targets[i][1], targets[i][1], targets[i][1]);
      }
      led_strip_refresh(led_strip);
      vTaskDelay(50 / portTICK_PERIOD_MS);
    }
  }

}

  
  


