## Makefile.am -- Process this file with automake to produce Makefile.in


lib_LTLIBRARIES = libwxservdisc.la
libwxservdisc_la_SOURCES = 1035.c mdnsd.c wxServDisc.cpp 1035.h mdnsd.h
include_HEADERS = wxServDisc.h
libwxservdisc_la_CFLAGS = -g -Wall
libwxservdisc_la_CXXFLAGS = -g -Wall
libwxservdisc_la_CPPFLAGS = $(WX_CPPFLAGS)
libwxservdisc_la_LDFLAGS = $(WX_LDFLAGS)
if MINGW
libwxservdisc_la_LIBADD = -lws2_32
libwxservdisc_la_LDFLAGS += -no-undefined -version-info 0:3:0 -static-libgcc -static-libstdc++
endif




