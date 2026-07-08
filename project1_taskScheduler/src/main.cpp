#include <Arduino.h>

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif

static const int led_pin = 2;

static int blink_delay = 500;

void readSerial(void *parameter){
  while(1){
    if(Serial.available()>0){
      int val = Serial.parseInt();
      if(val > 0){
        blink_delay = val;
        Serial.print("Updated Value to: ");
        Serial.println(blink_delay);
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

void toggleLED(void *parameter){
  while(1){
    digitalWrite(led_pin, HIGH);
    vTaskDelay(blink_delay / portTICK_PERIOD_MS);
    digitalWrite(led_pin, LOW);
    vTaskDelay(blink_delay / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(readSerial, "read serial", 1024, NULL, 1, NULL, app_cpu);
  xTaskCreatePinnedToCore(toggleLED, "toggleLED", 1024, NULL, 1, NULL, app_cpu);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}