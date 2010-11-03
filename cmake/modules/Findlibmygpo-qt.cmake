
# - Find libmygpo-qt
# Find the libmygpo-qt includes and the libmygpo-qt libraries
# This module defines
# LIBMYGPO_QT_INCLUDE_DIR, root mygpo-qt include dir
# LIBMYGPO_QT_LIBRARY, the path to libmygpo-qt
# LIBMYGPO_QT_FOUND, whether libmygpo-qt was found


find_path(LIBMYGPO_QT_INCLUDE_DIR NAMES mygpo.h
   HINTS
   ~/usr/include
   /opt/local/include
   /usr/include
   /usr/local/include
   /opt/kde4/include
  ~/kde/include
  PATH_SUFFIXES mygpo-qt
)

find_library( LIBMYGPO_QT_LIBRARY NAMES mygpo-qt
    PATHS
    ~/usr/lib
   /opt/local/lib
   /usr/lib
   /usr/lib64
   /usr/local/lib
   /opt/kde4/lib
    ~/kde/lib
)


if(LIBMYGPO_QT_INCLUDE_DIR AND LIBMYGPO_QT_LIBRARY)
   set(LIBMYGPO_QT_FOUND TRUE)
   message(STATUS "Found libmygpo-qt: ${LIBMYGPO_QT_INCLUDE_DIR}, ${LIBMYGPO_QT_LIBRARY}")
else(LIBMYGPO_QT_INCLUDE_DIR AND LIBMYGPO_QT_LIBRARY)
   set(LIBMYGPO_QT_FOUND FALSE)   
   if (LIBMYGPO_QT_FIND_REQUIRED)
      message(FATAL_ERROR "Could NOT find required package libmygpo-qt")
   endif(LIBMYGPO_QT_FIND_REQUIRED)
endif(LIBMYGPO_QT_INCLUDE_DIR AND LIBMYGPO_QT_LIBRARY)

mark_as_advanced(LIBMYGPO_QT_INCLUDE_DIR LIBMYGPO_QT_LIBRARY)
