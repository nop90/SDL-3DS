ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_tools

TARGET_LIB = libSDL_mixer.a

OBJS =	dynamic_flac.o \
	dynamic_fluidsynth.o \
	dynamic_mod.o \
	dynamic_mp3.o \
	dynamic_ogg.o \
	effect_position.o \
	effect_stereoreverse.o \
	effects_internal.o \
	fluidsynth.o \
	load_aiff.o \
	load_flac.o \
	load_ogg.o \
	load_voc.o \
	mixer.o \
	music.o \
	music_cmd.o \
	music_flac.o \
	music_mad.o \
	music_mod.o \
	music_modplug.o \
	music_ogg.o \
	wavestream.o 

CTRULIB	:= $(DEVKITPRO)/libctru
INCLUDES = -I./include -I$(CTRULIB)/include 

SUPPORT_TREMOR = false
SUPPORT_VORBIS = false
SUPPORT_MAD = true

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard
CFLAGS		:=	-g -Wall -O2 -mword-relocations  \
			-fomit-frame-pointer -ffast-math  -fno-pic \
			$(ARCH)
CFLAGS		+=	$(INCLUDES) -DARM11 -D_3DS -D__3DS__ -DENABLE_3DS -DWAV_MUSIC -DMOD_MUSIC \
				-I$(CTRULIB)/../portlibs/armv6k/include -I$(CTRULIB)/../portlibs/3ds/include/SDL

ifeq ($(SUPPORT_TREMOR), true)
CFLAGS += -DOGG_MUSIC -DOGG_USE_TREMOR
endif

ifeq ($(SUPPORT_VORBIS), true)
CFLAGS += -DOGG_MUSIC
endif

ifeq ($(SUPPORT_MAD), true)
CFLAGS += -DMP3_MAD_MUSIC
endif

CXXFLAGS	:=      $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
ASFLAGS		:=	-g $(ARCH)
LDFLAGS		:=	-specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

CFLAGS		+= -Wno-unused-variable

LIBS	:= -lmad -lmikmod -lvorbis -lSDL -lctru -lm

all: $(OBJS) $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(AR) -rc $@ $^

install: $(TARGET_LIB)
	@mkdir -p "$(DEVKITPRO)/portlibs/3ds/lib"
	@cp  $(TARGET_LIB) "$(DEVKITPRO)/portlibs/3ds/lib"
	@mkdir -p "$(DEVKITPRO)/portlibs/3ds/include"
	@mkdir -p "$(DEVKITPRO)/portlibs/3ds/include/SDL"
	@cp SDL_mixer.h "$(DEVKITPRO)/portlibs/3ds/include/SDL"
	@echo "Installed!"

clean:
	@rm -rf $(OBJS) $(TARGET_LIB)