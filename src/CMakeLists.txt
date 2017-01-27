if (${CMAKE_SYSTEM_NAME} EQUAL "Linux")
 add_definitions(-D_GNU_SOURCE -DLINUX_BUILD)
endif (${CMAKE_SYSTEM_NAME} EQUAL "Linux")

if (WIN32)
	message(STATUS "Adding Windows specific files")
	set(
		OS_SPECIFIC_FILES
		common/windows/contrib/asprintf.c
		common/windows/contrib/vasprintf.c
		time/windows/contrib/getimeofday.c
	)
endif(WIN32)

add_library(
	gru-${GRU_VERSION_MAJOR} SHARED
	common/gru_base.c
	common/gru_status.c
	common/gru_alloc.c
	${OS_SPECIFIC_FILES}
	collection/gru_node.c
	collection/gru_list.c
	collection/gru_tree.c
	io/gru_path.c
	io/gru_ioutils.c
	log/gru_logger.c
	string/gru_util.c
	string/gru_alt.c
	config/gru_payload.c
	config/gru_config.c
	time/gru_time_utils.c
	time/other/gru_time_portable.c
	time/gru_duration.c
	network/gru_uri.c
	cli/gru_cli_opt.c
)

install(
	TARGETS gru-${GRU_VERSION_MAJOR}
	LIBRARY DESTINATION ${CPP_LIBRARY_DIR}
	ARCHIVE DESTINATION ${CPP_LIBRARY_DIR}
)

install(
	DIRECTORY common
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)

install(
	DIRECTORY log
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)


install(
	DIRECTORY io
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)


install(
	DIRECTORY string
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)

install(
	DIRECTORY collection
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)


install(
	DIRECTORY config
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)


install(
	DIRECTORY time
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)

install(
	DIRECTORY network
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)

install(
	DIRECTORY cli
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}-${GRU_VERSION_MAJOR}
	FILES_MATCHING PATTERN "*.h"
)
