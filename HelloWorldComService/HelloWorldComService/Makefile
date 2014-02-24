include ../os_detect.mak

PROJDIRS     = .

BINNAME      = cominterface

INCLUDES     = $(foreach DIR, $(PROJDIRS), $(DIR)) 

# INCLUDES     = $(foreach DIR, $(PROJDIRS), $(DIR)) \
                      # ../engine \
                      # ../engine/ai \
                      # ../engine/behavior \
                      # ../engine/category \
                      # ../engine/compat \
                      # ../engine/config \
                      # ../engine/resource \
                      # ../engine/sql \
                      # ../../java/gensrc \
                      # ../utility

# SYSINCLUDES         = ../lib/jdk1.6.0_34/include
# SYSINCLUDES.windows = ../lib/jdk1.6.0_34/include/win32
# SYSINCLUDES.linux   = ../lib/jdk1.6.0_34/include/linux

CXXFLAGS.EXTRA = -fpermissive

COM_INTERFACE_RES=  HelloWorldComServer.res

EXCLUDES     = 

LIBDIRS      = 

LIBS         = uuid ole32 oleaut32

MACROS       = CPP_WRAPPER_LIB UTILITY_STATIC
MACROS.linux = LINUX_BLD


.PHONY: all clean gensrc

all: HelloWorldComServer.res \
     $(call GET_TARGETS,build/dist/windows/static/lib$(BINNAME).a,build/dist/linux/static/lib$(BINNAME).a)

clean:
	-@$(RMDIR) build

gensrc:

HelloWorldComServer.res : HelloWorldComServer.rc
	/home/blockm/ics/trunk/trunk/compilers/cross64/build/binutils-2.22.90/binutils/windres -i HelloWorldComServer.rc  -o build/obj/windows/HelloWorldComServer.res -O res


include ../common.mak
