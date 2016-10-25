ACLOCAL_AMFLAGS=-I m4

bin_SCRIPTS = scripts/bin/*

pyutilsdir=$(libdir)/sonic
pyutils_SCRIPTS = scripts/lib/python/*.py

nobase_include_HEADERS=sonic/nas_l2_init.h

lib_LTLIBRARIES=libsonic_nas_l2.la

libsonic_nas_l2_la_SOURCES=src/stg/nas_stg_cps.cpp \
         src/stg/nas_stg_api.cpp src/nas_l2.cpp \
         src/sflow/nas_sflow_cps.cpp src/sflow/nas_sflow_api.cpp \
         src/mirror/nas_mirror_api.cpp src/mirror/nas_mirror_cps.cpp \
         src/mac/nas_mac_api.cpp src/mac/nas_mac_cps.cpp \
         src/mac/nas_mac_request_handler.cpp src/mac/nas_mac_events.cpp \
         src/switch/nas_switch_cps.cpp src/switch/nas_switch_mac.cpp \
         src/switch/nas_switch_log.cpp

libsonic_nas_l2_la_CPPFLAGS= -D_FILE_OFFSET_BITS=64 -I$(top_srcdir)/sonic -I$(includedir)/sonic

libsonic_nas_l2_la_CXXFLAGS=-std=c++11

libsonic_nas_l2_la_LDFLAGS=-shared -version-info 1:1:0

libsonic_nas_l2_la_LIBADD=-lsonic_nas_linux -lsonic_common -lsonic_nas_common -lsonic_nas_ndi -lsonic_object_library -lsonic_logging
