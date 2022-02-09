set(INNODB_SOURCES
        os_thread.cc os_thread.hh os_sync.cc os_sync.hh
        )

add_library(innodb2 SHARED ${INNODB_SOURCES})