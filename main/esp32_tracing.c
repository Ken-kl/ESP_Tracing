#include "driver/gpio.h"
#include "esp_log.h"
#include "soc/soc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_attr.h"

#define BLINK_GPIO GPIO_NUM_8
#define DR_REG_PCR_BASE 0x60096000
#define TRACE_BASE_ADDRESS 0x600C0000

#define PCR_TRACE_CONF_REG (DR_REG_PCR_BASE + 0x00FC)
#define TRACE_MEM_START_ADDR_REG (TRACE_BASE_ADDRESS + 0x0000)
#define TRACE_MEM_END_ADDR_REG (TRACE_BASE_ADDRESS + 0x0004)
#define TRACE_MEM_CURRENT_ADDR_REG (TRACE_BASE_ADDRESS + 0x0008)
#define TRACE_MEM_ADDR_UPDATE_REG (TRACE_BASE_ADDRESS + 0x000C)
#define TRACE_RESYNC_PROLONGED (TRACE_BASE_ADDRESS + 0x0024)
#define TRACE_TRIGGER_REG (TRACE_BASE_ADDRESS + 0x0020)
#define TRACE_RESYNC_PROLONGED_REG (TRACE_BASE_ADDRESS + 0x0024)

// Memory
#define TRACE_BUFFER_SIZE 0x8000
uint8_t trace_buffer[TRACE_BUFFER_SIZE] WORD_ALIGNED_ATTR DMA_ATTR __attribute__((aligned(16)));

void app_main(void)
{
    // Clear memory address
    memset(trace_buffer, 0, TRACE_BUFFER_SIZE);
    ESP_LOGI("BUFFER", "Resetting trace buffer");
    uint32_t start_address = (uint32_t)&trace_buffer[0];
    uint32_t end_address = start_address + TRACE_BUFFER_SIZE - 4;
    ESP_LOGI("TRACE", "Buffer allocated at: 0x%08X - 0x%08X", start_address, end_address);

    // Enable Trace Clock
    REG_WRITE(PCR_TRACE_CONF_REG, 1);

    // Define Start and End Address for Trace
    REG_WRITE(TRACE_MEM_START_ADDR_REG, start_address);
    REG_WRITE(TRACE_MEM_END_ADDR_REG, end_address);

    // Update value of current trace memory address
    REG_WRITE(TRACE_MEM_ADDR_UPDATE_REG, 1);

    // Configure Threshold for Synchronization counter to resync after X cycles
    REG_WRITE(TRACE_RESYNC_PROLONGED, 50);

    // Enable Trace Encoder
    REG_WRITE(TRACE_TRIGGER_REG, 0x5);
    asm volatile("nop; nop; nop; nop;");
    ESP_LOGI("TRACE", "Hardware should be streaming now.");

    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    while (1)
    {
        ESP_LOGI("LED", "Turning LED ON");
        gpio_set_level(BLINK_GPIO, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));

        ESP_LOGI("LED", "Turning LED OFF");
        gpio_set_level(BLINK_GPIO, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));

        /*REG_WRITE(TRACE_TRIGGER_REG, 0x6);
        __asm__ __volatile__("nop");
        uint32_t current = *(volatile uint32_t *)TRACE_MEM_CURRENT_ADDR_REG;
        ESP_LOGI("TRACE", "Buffer address: 0x%08x", (unsigned int)current);

        if (current >= start_address + TRACE_BUFFER_SIZE - 0x100)
        {
            ESP_LOGW("TRACE", "Buffer is almost full!");
        }
        REG_WRITE(TRACE_TRIGGER_REG, 0x5);*/
    }
}
