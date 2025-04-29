TOP=../..
include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

LIBRARY_IOC += ntndArrayConverter
INC += ntndArrayConverterAPI.h
ifeq ($(WITH_PVXS), YES)
INC += ntndArrayConverter.h
LIB_SRCS += ntndArrayConverter_pvxs.cpp
USR_CPPFLAGS += -DHAVE_PVXS
else
INC += ntndArrayConverter.h
LIB_SRCS += ntndArrayConverter.cpp
endif

USR_CPPFLAGS += -DBUILDING_ntndArrayConverter_API

LIB_LIBS              += ADBase

ifeq ($(WITH_PVXS),YES)
	LIB_LIBS 			  += pvxs
else
	LIB_LIBS              += pvData
	LIB_LIBS              += nt
endif
LIB_LIBS              += asyn
LIB_LIBS              += $(EPICS_BASE_IOC_LIBS)

#=============================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

