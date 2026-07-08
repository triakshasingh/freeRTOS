Task Scheduling

Challenge Question:


Using FreeRTOS, create two separate tasks. One listens for an integer over UART (from the Serial Monitor) and sets a variable when it sees an integer. The other task blinks the onboard LED (or other connected LED) at a rate specified by that integer. In effect, you want to create a multi-threaded system that allows for the user interface to run concurrently with the control task (the blinking LED).


What's covered


Creating tasks with xTaskCreatePinnedToCore()
delay() vs vTaskDelay() — blocking the CPU vs. freeing it for other tasks
Running multiple independent tasks concurrently (blinking two LEDs at different rates)
Task handles, vTaskSuspend(), vTaskResume(), and vTaskDelete()
Reading input over Serial (Serial.parseInt()) in one task while another task
keeps running independently (UART-controlled LED blink rate challenge)


Key takeaways


Concurrency comes from xTaskCreate() / xTaskCreatePinnedToCore() calls —
not from how code is organized into functions. Splitting code into helper
functions doesn't make it run in parallel unless each one is registered as
its own task.
vTaskDelay() only frees the CPU for other tasks — it doesn't make code
within the same task skip ahead or run out of order.
Shared global variables (like a shared LED pin or a shared delay value)
work for now, but come with risks — the "correct" fix is queues/mutexes,
covered in later parts.


Setup


Board: ESP32 DevKit (simulated in Wokwi)
Framework: Arduino (via PlatformIO)
Run locally: build with PlatformIO, then F1 → "Wokwi: Start Simulator"