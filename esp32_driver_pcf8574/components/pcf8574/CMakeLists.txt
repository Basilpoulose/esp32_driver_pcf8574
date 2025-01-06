# idf_component_register(SRCS "pcf8574.c"
#                        INCLUDE_DIRS driver)

idf_component_register(SRCS "pcf8574.c"
                       INCLUDE_DIRS "include"
                       REQUIRES driver)

# # idf_component_register(SRCS "pcf8574.c"
# #                     INCLUDE_DIRS "include")
