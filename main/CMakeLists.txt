idf_component_register(SRCS "esp32_tracing.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp_driver_gpio esp_trace)

idf_component_get_property(app_trace_lib app_trace COMPONENT_LIB)

target_sources(${COMPONENT_LIB} PRIVATE 
    "/opt/esp/idf/components/esp_trace/adapters/transport/adapter_transport_apptrace.c"
    "/opt/esp/idf/components/app_trace/app_trace.c"
)   

target_include_directories(${COMPONENT_LIB} PRIVATE 
"/opt/esp/idf/components/esp_trace/include"
    "/opt/esp/idf/components/esp_trace/adapters/include"
    "/opt/esp/idf/components/app_trace/include"
    "/opt/esp/idf/components/app_trace/port/include"
)