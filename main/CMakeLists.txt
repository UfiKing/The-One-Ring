idf_component_register(SRCS "TheOneRing.c"
                    INCLUDE_DIRS "."
                    REQUIRES bootloader_support
                    REQUIRES esp_lcd
                    REQUIRES esp32-i2c-lcd1602 esp32-smbus
                    REQUIRES esp32-smbus)
