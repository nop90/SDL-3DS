ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/base_tools

TARGET_LIB = libSDL_image.a

OBJS =	IMG.o \
	IMG_bmp.o \
	IMG_gif.o \
	IMG_jpg.o \
	IMG_lbm.o \
	IMG_pcx.o \
	IMG_png.o \
	IMG_pnm.o \
	IMG_tga.o \
	IMG_tif.o \
	IMG_webp.o \
	IMG_xcf.o \
	IMG_xpm.o \
	IMG_xv.o \
	IMG_xxx.o 

CTRULIB	:= $(DEVKITPRO)/libctru
INCLUDES = -I./include -I$(CTRULIB)/include 

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH		:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard
CFLAGS		:=	-g -Wall -O2 -mword-relocations \
			-fomit-frame-pointer -ffast-math \
			$(ARCH)
CFLAGS		+=	$(INCLUDES) -DARM11 -D_3DS -D__3DS__ -DENABLE_3DS -DLOAD_BMP \
				-DLOAD_GIF -DLOAD_LBM -DLOAD_PCX -DLOAD_PNM -DLOAD_TGA -DLOAD_XCF \
				-DLOAD_XPM -DLOAD_XV -DLOAD_JPG -DLOAD_PNG \
				-I$(CTRULIB)/../portlibs/armv6k/include -I$(CTRULIB)/../portlibs/3ds/include/SDL
CXXFLAGS	:=      $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11
ASFLAGS		:=	-g $(ARCH)
LDFLAGS		:=	-specs=3dsx.specs -g $(ARCH) -Wl,-Map,$(notdir $*.map)

CFLAGS		+= -Wno-unused-variable

LIBS	:= -jpeg -lSDL -lctru -lm

all: $(OBJS) $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	$(AR) -rc $@ $^

install: $(TARGET_LIB)
	@mkdir -p "$(DEVKITPRO)/portlibs/3ds/lib"
	@cp  $(TARGET_LIB) "$(DEVKITPRO)/portlibs/3ds/lib"
	@mkdir -p "$(DEVKITPRO)/portlibs/3ds/include"
	@mkdir -p "$(DEVKITPRO)/portlibs/3ds/include/SDL"
	@cp SDL_image.h "$(DEVKITPRO)/portlibs/3ds/include/SDL"
	@echo "Installed!"

clean:
	@rm -rf $(OBJS) $(TARGET_LIB)