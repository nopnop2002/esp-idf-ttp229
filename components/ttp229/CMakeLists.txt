set(component_srcs "ttp229.c")

idf_component_register(
	SRCS "${component_srcs}"
	PRIV_REQUIRES driver esp_driver_gpio
	INCLUDE_DIRS "."
)
