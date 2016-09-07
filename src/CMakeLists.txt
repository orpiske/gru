add_definitions(-D_GNU_SOURCE -D_POSIX_C_SOURCE)

if (${CMAKE_SYSTEM_NAME} EQUAL "Linux") 
 add_definitions(-DLINUX_BUILD) 
endif (${CMAKE_SYSTEM_NAME} EQUAL "Linux")

add_library(
	gru SHARED
        log/logger.c
        options/options.c
)


install(TARGETS gru
	LIBRARY DESTINATION ${CPP_LIBRARY_DIR}
)

install(DIRECTORY log
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)


install(DIRECTORY options
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)




