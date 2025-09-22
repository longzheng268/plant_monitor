idf_component_register(SRCS "Wifi_STA_init.c"
                    INCLUDE_DIRS "."
								 "./Wifi_STA_init"
					PRIV_REQUIRES esp_wifi
								  nvs_flash )
