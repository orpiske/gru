if (${CMAKE_SYSTEM_NAME} EQUAL "Linux")
 add_definitions(-D_GNU_SOURCE -DLINUX_BUILD)
endif (${CMAKE_SYSTEM_NAME} EQUAL "Linux")

add_library(
	gru SHARED
        common/gru_base.c
        common/gru_status.c
        common/gru_alloc.c
        collection/gru_node.c
        collection/gru_list.c
        collection/gru_tree.c
        io/gru_path.c
        io/gru_ioutils.c
        log/gru_logger.c
        string/gru_util.c
        config/gru_payload.c
        config/gru_config.c
        time/gru_time_utils.c
        time/gru_duration.c
)


install(TARGETS gru
	LIBRARY DESTINATION ${CPP_LIBRARY_DIR}
)

install(DIRECTORY common
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY log
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)


install(DIRECTORY io
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)


install(DIRECTORY string
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)

install(DIRECTORY collection
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)


install(DIRECTORY config
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)


install(DIRECTORY time
        DESTINATION include/${PROJECT_NAME}
        FILES_MATCHING PATTERN "*.h"
)
