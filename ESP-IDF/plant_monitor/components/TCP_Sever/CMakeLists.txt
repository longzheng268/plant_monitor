idf_component_register(SRCS "tcp_server.c"
                    INCLUDE_DIRS "." 
								 "./tcp_server"
					PRIV_REQUIRES esp_wifi
								  nvs_flash )
