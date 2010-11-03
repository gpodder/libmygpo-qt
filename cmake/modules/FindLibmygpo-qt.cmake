
# - Find LibLastFM
# Find the liblastfm includes and the liblastfm libraries
# This module defines
# LIBLASTFM_INCLUDE_DIR, root lastfm include dir
# LIBLASTFM_LIBRARY, the path to liblastfm
# LIBLASTFM_FOUND, whether liblastfm was found


find_path(LIBMYGPO_INCLUDE_DIR NAMES mygpo.h
   HINTS
   ~/usr/include
   /opt/local/include
   /usr/include
   /usr/local/include
   /opt/kde4/include
  ~/kde/include
  PATH_SUFFIXES mygpo-qt
)

find_library( LIBMYGPO_LIBRARY NAMES mygpo-qt
    PATHS
    ~/usr/lib
   /opt/local/lib
   /usr/lib
   /usr/lib64
   /usr/local/lib
   /opt/kde4/lib
    ~/kde/lib
)


if(LIBMYGPO_INCLUDE_DIR AND LIBMYGPO_LIBRARY)
   set(LIBMYGPO_FOUND TRUE)
   message(STATUS "Found liblastfm: ${LIBMYGPO_INCLUDE_DIR}, ${LIBMYGPO_LIBRARY}")
else(LIBMYGPO_INCLUDE_DIR AND LIBMYGPO_LIBRARY)
   set(LIBMYGPO_FOUND FALSE)   
   if (LIBMYGPO_FIND_REQUIRED)
      message(FATAL_ERROR "Could NOT find required package LibLastFm")
   endif(LIBMYGPO_FIND_REQUIRED)
endif(LIBMYGPO_INCLUDE_DIR AND LIBMYGPO_LIBRARY)

mark_as_advanced(LIBMYGPO_INCLUDE_DIR LIBMYGPO_LIBRARY)
