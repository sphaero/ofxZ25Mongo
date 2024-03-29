include config.make
# openFrameworks universal makefile
#
# make help : shows this message
# make Debug:  makes the application with debug symbols
# make Release: makes the app with optimizations
# make: the same as make Release
# make CleanDebug: cleans the Debug target
# make CleanRelease: cleans the Release target
# make clean: cleans everything
#
#
# this should work with any OF app, just copy any example
# change the name of the folder and it should compile
# only .cpp support, don't use .c files
# it will look for files in any folder inside the application
# folder except that in the EXCLUDE_FROM_SOURCE variable
# it doesn't autodetect include paths yet
# add the include paths in the USER_CFLAGS variable
# using the gcc syntax: -Ipath
#
# to add addons to your application, edit the addons.make file
# in this directory and add the names of the addons you want to
# include
#
# edit the following  vars to customize the makefile

ifeq ($(findstring Android,$(MAKECMDGOALS)),Android)
	include $(OF_ROOT)/libs/openFrameworksCompiled/project/android/paths.make
	ARCH = android
	ifeq ($(shell uname),Darwin)
		HOST_PLATFORM = darwin-x86
	else ifeq ($(shell uname),MINGW32_NT-6.1)
		HOST_PLATFORM = windows
	else
		HOST_PLATFORM = linux-x86
	endif
endif

ifndef ARCH
	ARCH=$(shell uname -m)
endif

ifeq ($(ARCH),android)
	include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/Makefile.android
else
    ifeq ($(ARCH),armv7l)
        include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/Makefile.arm
    else
        include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/Makefile.linux
    endif
endif




# you shouldn't modify anything below this line


SHELL =  /bin/sh

NODEPS = clean
SED_EXCLUDE_FROM_SRC = $(shell echo  $(EXCLUDE_FROM_SOURCE) | sed 's/\,/\\|/g')\|^\..*\|\/\..**
SOURCE_DIRS = $(shell find . -type d | sed s/.\\/// | grep -v "$(SED_EXCLUDE_FROM_SRC)")
SOURCES = $(shell find $(SOURCE_DIRS) -maxdepth 1 -name "*.cpp" -or -name "*.c" -or -name "*.cc" -or -name "*.cxx" )
OBJFILES = $(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst %.cxx,%.o,$(patsubst %.cc,%.o,$(SOURCES)))))

ifneq (,$(USER_SOURCE_DIR))
	USER_SOURCES = $(shell find $(USER_SOURCE_DIR) -name "*.cpp" -or -name "*.c" -or -name "*.cc" -or -name "*.cxx")
	USER_OBJFILES =  $(subst $(USER_SOURCE_DIR)/, ,$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst %.cxx,%.o,$(patsubst %.cc,%.o,$(USER_SOURCES))))))
endif

ifeq ($(APPNAME),)
    APPNAME = $(shell basename `pwd`)
endif
CORE_INCLUDES = $(shell find $(OF_ROOT)/libs/openFrameworks/ -type d)
CORE_INCLUDE_FLAGS = $(addprefix -I,$(CORE_INCLUDES))
INCLUDES = $(shell find $(OF_ROOT)/libs/*/include -type d | grep -v glu | grep -v quicktime | grep -v poco | grep -v glew)
INCLUDES_FLAGS += $(addprefix -I,$(INCLUDES))
INCLUDES_FLAGS += -I$(OF_ROOT)/libs/poco/include

LIB_STATIC += $(shell ls $(OF_ROOT)/libs/*/lib/$(LIBSPATH)/*.a  2> /dev/null | grep -v openFrameworksCompiled | grep -v Poco)
LIB_SHARED += $(shell ls $(OF_ROOT)/libs/*/lib/$(LIBSPATH)/*.so  2> /dev/null | grep -v openFrameworksCompiled | sed "s/.*\\/lib\([^/]*\)\.so/-l\1/")
LIB_PATHS_FLAGS = $(shell ls -d $(OF_ROOT)/libs/*/lib/$(LIBSPATH) | sed "s/\(\.*\)/-L\1/")

CFLAGS += -Wall -fexceptions
CFLAGS += -I.
CFLAGS += $(INCLUDES_FLAGS)
CFLAGS += $(CORE_INCLUDE_FLAGS)

ifeq ($(findstring Debug,$(TARGET_NAME)),Debug)
	CFLAGS += -g3
	TARGET_LIBS = $(OF_ROOT)/libs/openFrameworksCompiled/lib/$(LIBSPATH)/libopenFrameworksDebug.a
endif

ifeq ($(findstring Release,$(TARGET_NAME)),Release)
	CFLAGS += $(COMPILER_OPTIMIZATION)
	TARGET_LIBS = $(OF_ROOT)/libs/openFrameworksCompiled/lib/$(LIBSPATH)/libopenFrameworks.a
endif


ifeq ($(findstring addons.make,$(wildcard *.make)),addons.make)
	ifneq ($(ARCH),android)
		ADDONS = $(shell cat addons.make | grep -v ofxAndroid)
	else
		ADDONS = $(shell cat addons.make)
	endif
	
	ifneq ($(strip $(ADDONS)),)
	    ADDONS_REL_DIRS = $(addsuffix /src, $(ADDONS))
	    ADDONS_LIBS_REL_DIRS = $(addsuffix /libs, $(ADDONS))
	    ADDONS_DIRS = $(addprefix $(OF_ROOT)/addons/, $(ADDONS_REL_DIRS) )
	    ADDONS_LIBS_DIRS = $(addprefix $(OF_ROOT)/addons/, $(ADDONS_LIBS_REL_DIRS) )
	    ADDONS_BIN_LIBS_DIRS = $(addsuffix /*/lib/$(LIBSPATH), $(ADDONS_LIBS_DIRS) )
	
	    ADDONS_INCLUDES = $(ADDONS_DIRS)
	    ADDONS_INCLUDES = $(ADDONS_LIBS_DIRS)
	    ADDONS_INCLUDES += $(shell find $(ADDONS_DIRS) -type d 2> /dev/null)
	    ADDONS_INCLUDES += $(shell find $(ADDONS_LIBS_DIRS) -type d 2> /dev/null)
	    ADDONSCFLAGS = $(addprefix -I,$(ADDONS_INCLUDES))

	    ifeq ($(findstring libsorder.make,$(shell find $(ADDONS_BIN_LIBS_DIRS) -name libsorder.make 2> /dev/null)),libsorder.make)
		    ADDONS_LIBS_W_ORDER = $(shell cat $(shell find $(ADDONS_BIN_LIBS_DIRS) -name libsorder.make 2> /dev/null))
		    EXCLUDE_LIBS_FILTER = $(addprefix %,$(addsuffix .a,$(ADDONS_LIBS_W_ORDER)))
		    ADDONS_LIBS_STATICS = $(filter-out $(EXCLUDE_LIBS_FILTER), $(shell find $(ADDONS_BIN_LIBS_DIRS) -name *.a))
        	ADDONS_LIBS_STATICS += $(addprefix $(shell find $(ADDONS_BIN_LIBS_DIRS) -name libsorder.make 2> /dev/null | sed s/libsorder.make//g),$(ADDONS_LIBS_W_ORDER))
	    else
		    ADDONS_LIBS_STATICS = $(shell find $(ADDONS_BIN_LIBS_DIRS) -name *.a 2> /dev/null)
	    endif

	    ADDONS_LIBS_SHARED = $(shell find $(ADDONS_BIN_LIBS_DIRS) -name *.so 2> /dev/null)
	    ADDONSLIBS = $(ADDONS_LIBS_STATICS)
	    ADDONSLIBS += $(ADDONS_LIBS_SHARED)


	    ADDONS_SOURCES = $(shell find $(ADDONS_DIRS) -name "*.cpp" -or -name "*.c" 2> /dev/null)
	    ADDONS_SOURCES += $(shell find $(ADDONS_LIBS_DIRS) -name "*.cpp" -or -name "*.c" -or -name "*.cc" -or -name "*.cxx" 2>/dev/null)
	    ADDONS_OBJFILES = $(subst $(OF_ROOT)/, ,$(patsubst %.cc,%.o,$(patsubst %.c,%.o,$(patsubst %.cxx,%.o,$(patsubst %.cpp,%.o,$(ADDONS_SOURCES))))))
	endif
endif

ifeq ($(MAKECMDGOALS),clean)
	TARGET = bin/$(APPNAME)_debug bin/$(APPNAME)
	TARGET_NAME = Release
endif


OBJ_OUTPUT = obj/$(ARCH)$(TARGET_NAME)/
CLEANTARGET = clean$(TARGET_NAME)

OBJS = $(addprefix $(OBJ_OUTPUT), $(OBJFILES))
DEPFILES = $(patsubst %.o,%.d,$(OBJS))

USER_OBJS = $(addprefix $(OBJ_OUTPUT), $(USER_OBJFILES))
DEPFILES += $(patsubst %.o,%.d,$(USER_OBJS))

ifeq ($(findstring addons.make,$(wildcard *.make)),addons.make)
	ADDONS_OBJS = $(addprefix $(OBJ_OUTPUT), $(ADDONS_OBJFILES))
    DEPFILES += $(patsubst %.o,%.d,$(ADDONS_OBJS))
endif

ifeq ($(TARGET_LIBS),)
    TARGET_LIBS = $(OF_ROOT)/libs/openFrameworksCompiled/lib/$(LIBSPATH)/libopenFrameworks.a
endif

.PHONY: Debug Release all after

Release: $(TARGET) after

Debug: $(TARGET) after

all:
	$(MAKE) Release


#This rule does the compilation
#$(OBJS): $(SOURCES)
$(OBJ_OUTPUT)%.o: %.cpp
	@echo "compiling $(ARCH) object for: " $<
	mkdir -p $(@D)
	$(CXX) -c $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o$@ -c $<
	
$(OBJ_OUTPUT)%.o: %.cxx
	@echo "compiling $(ARCH) object for: " $<
	mkdir -p $(@D)
	$(CXX) -c $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o$@ -c $<

$(OBJ_OUTPUT)%.o: %.c
	@echo "compiling $(ARCH) object for: " $<
	mkdir -p $(@D)
	$(CC) -c $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o$@ -c $<

$(OBJ_OUTPUT)%.o: %.cc
	@echo "compiling $(ARCH) object for: " $<
	mkdir -p $(@D)
	$(CC) -c $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o$@ -c $<

$(OBJ_OUTPUT)%.o: $(OF_ROOT)/%.cpp
	@echo "compiling addon $(ARCH) object for" $<
	mkdir -p $(@D)
	$(CXX) $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o $@ -c $<
	
$(OBJ_OUTPUT)%.o: $(OF_ROOT)/%.cxx
	@echo "compiling addon $(ARCH) object for" $<
	mkdir -p $(@D)
	$(CXX) $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o $@ -c $<

$(OBJ_OUTPUT)%.o: $(OF_ROOT)/%.c
	@echo "compiling addon $(ARCH) object for" $<
	mkdir -p $(@D)
	$(CC) $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o $@ -c $<
	
$(OBJ_OUTPUT)%.o: $(OF_ROOT)/%.cc
	@echo "compiling addon $(ARCH) object for" $<
	mkdir -p $(@D)
	$(CC) $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o $@ -c $<

$(OBJ_OUTPUT)%.o: $(USER_SOURCE_DIR)/%.c
	@echo "compiling $(ARCH) object for: " $<
	mkdir -p $(@D)
	$(CC) $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o$@ -c $<
	
$(OBJ_OUTPUT)%.o: $(USER_SOURCE_DIR)/%.cc
	@echo "compiling $(ARCH) object for: " $<
	mkdir -p $(@D)
	$(CC) $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o$@ -c $<

$(OBJ_OUTPUT)%.o: $(USER_SOURCE_DIR)/%.cpp
	@echo "compiling $(ARCH) object for: " $<
	mkdir -p $(@D)
	$(CXX) $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o$@ -c $<
	
$(OBJ_OUTPUT)%.o: $(USER_SOURCE_DIR)/%.cxx
	@echo "compiling $(ARCH) object for: " $<
	mkdir -p $(@D)
	$(CXX) $(TARGET_CFLAGS) $(CFLAGS) $(ADDONSCFLAGS) $(USER_CFLAGS) -MMD -MP -MF$(OBJ_OUTPUT)$*.d -MT$(OBJ_OUTPUT)$*.o -o$@ -c $<
	
$(TARGET): $(OBJS) $(ADDONS_OBJS) $(USER_OBJS) $(TARGET_LIBS) $(LIB_STATIC)
	@echo 'linking $(ARCH) $(TARGET) $(LIBSPATH)'
	mkdir -p $(@D)
	$(CXX) -o $@ $(OBJS) $(ADDONS_OBJS) $(USER_OBJS) $(LDFLAGS) $(TARGET_LIBS) $(ADDONSLIBS) $(USER_LIBS) $(LIB_STATIC) $(LIB_PATHS_FLAGS) $(USER_LDFLAGS) $(LIB_SHARED) $(SYSTEMLIBS)

-include $(DEPFILES)

.PHONY: clean cleanDebug cleanRelease

clean:
	rm -rf $(OBJ_OUTPUT)
	rm -f $(TARGET)
	rm -rf bin/libs

ifneq ($(CLEANTARGET),clean)
	$(CLEANTARGET):
		rm -rf $(OBJ_OUTPUT)
		rm -f $(TARGET)
		rm -rf bin/libs
endif


after:$(TARGET)
	cp -r $(OF_ROOT)/export/$(LIBSPATH)/libs bin/
	@echo
	@echo "     compiling done"
	@echo "     to launch the application"
	@echo
	@echo "     cd bin"
	@echo "     ./$(BIN_NAME)"
	@echo


.PHONY: help
help:
	@echo
	@echo openFrameworks universal makefile
	@echo
	@echo targets:
	@echo "make Debug:		builds the application with debug symbols"
	@echo "make Release:		builds the app with optimizations"
	@echo "make:			= make Release"
	@echo "make all:		= make Release"
	@echo "make CleanDebug:	cleans the Debug target"
	@echo "make CleanRelease:	cleans the Release target"
	@echo "make clean:		cleans everything"
	@echo
	@echo this should work with any OF app, just copy any example
	@echo change the name of the folder and it should compile
	@echo "only .cpp support, don't use .c files"
	@echo it will look for files in any folder inside the application
	@echo folder except that in the EXCLUDE_FROM_SOURCE variable.
	@echo "it doesn't autodetect include paths yet"
	@echo "add the include paths editing the var USER_CFLAGS"
	@echo at the beginning of the makefile using the gcc syntax:
	@echo -Ipath
	@echo
	@echo to add addons to your application, edit the addons.make file
	@echo in this directory and add the names of the addons you want to
	@echo include
	@echo
