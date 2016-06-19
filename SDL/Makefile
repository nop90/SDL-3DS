ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_tools

TARGET_LIB = libSDL.a

OBJS =	src/SDL.o \
	src/SDL_error.o \
	src/SDL_fatal.o \
	src/audio/SDL_audio.o \
	src/audio/SDL_audiocvt.o \
	src/audio/SDL_audiodev.o \
	src/audio/SDL_mixer.o \
	src/audio/SDL_wave.o \
	src/audio/3ds/SDL_3dsaudio.o \
	src/cdrom/SDL_cdrom.o \
	src/cdrom/dummy/SDL_syscdrom.o \
	src/cpuinfo/SDL_cpuinfo.o \
	src/events/SDL_active.o \
	src/events/SDL_events.o \
	src/events/SDL_expose.o \
	src/events/SDL_keyboard.o \
	src/events/SDL_mouse.o \
	src/events/SDL_quit.o \
	src/events/SDL_resize.o \
	src/file/SDL_rwops.o \
	src/joystick/SDL_joystick.o \
	src/joystick/3ds/SDL_sysjoystick.o \
	src/loadso/dummy/SDL_sysloadso.o \
	src/stdlib/SDL_getenv.o \
	src/stdlib/SDL_iconv.o \
	src/stdlib/SDL_malloc.o \
	src/stdlib/SDL_qsort.o \
	src/stdlib/SDL_stdlib.o \
	src/stdlib/SDL_string.o \
	src/thread/SDL_thread.o \
	src/thread/generic/SDL_syssem.o \
	src/thread/generic/SDL_systhread.o \
	src/thread/generic/SDL_sysmutex.o \
	src/thread/generic/SDL_syscond.o \
	src/timer/SDL_timer.o \
	src/timer/3ds/SDL_systimer.o \
	src/video/SDL_blit.o \
	src/video/SDL_blit_0.o \
	src/video/SDL_blit_1.o \
	src/video/SDL_blit_A.o \
	src/video/SDL_blit_N.o \
	src/video/SDL_bmp.o \
	src/video/SDL_cursor.o \
	src/video/SDL_gamma.o \
	src/video/SDL_pixels.o \
	src/video/SDL_RLEaccel.o \
	src/video/SDL_stretch.o \
	src/video/SDL_surface.o \
	src/video/SDL_video.o \
	src/video/SDL_yuv.o \
	src/video/SDL_yuv_sw.o \
	src/video/3ds/SDL_3dsevents.o \
	src/video/3ds/SDL_3dsvideo.o \
	src/video/3ds/SDL_3dsmouse.o

CTRULIB	:= $(DEVKITPRO)/libctru
INCLUDES = -I./include -I$(CTRULIB)/include

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard
CFLAGS		:=	-g -Wall -O2 -mword-relocations -fno-short-enums \
			-fomit-frame-pointer -ffast-math \
			$(ARCH)
CFLAGS		+=	$(INCLUDES) -DARM11 -D_3DS -D__3DS__ -DSDL_BUILDING_3DS
CXXFLAGS	:=      $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
ASFLAGS		:=	-g $(ARCH)
LDFLAGS		:=	-specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

CFLAGS		+= -Wno-unused-variable

LIBS	:= -lctru -lm

all: $(OBJS) $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(AR) -rc $@ $^

install: $(TARGET_LIB)
	@mkdir -p "$(DEVKITPRO)/portlibs/armv6k/lib"
	@cp  $(TARGET_LIB) "$(DEVKITPRO)/portlibs/armv6k/lib"
	@mkdir -p "$(DEVKITPRO)/portlibs/armv6k/include/SDL"
	@cp include/*.h "$(DEVKITPRO)/portlibs/armv6k/include/SDL"
	@echo "Installed!"

clean:
	@rm -rf $(OBJS) $(TARGET_LIB)