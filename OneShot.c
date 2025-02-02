#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

int64_t alarm_callback(alarm_id_t id, void *user_data) {
    return 0;
}



int main() {
    stdio_init_all();

    add_alarm_in_ms(2000, alarm_callback, NULL, false);

    while (true) {
    }
}