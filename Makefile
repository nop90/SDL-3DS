SDL              	:= SDL
SDL_VERSION      	:= $(SDL)-1.2.15

SDL_TTF             := SDL_ttf
SDL_TTF_VERSION     := $(SDL_TTF)-2.0.11
SDL_TTF_SRC         := $(SDL_TTF_VERSION).tar.gz
SDL_TTF_DOWNLOAD    := http://www.libsdl.org/projects/SDL_ttf/release/SDL_ttf-2.0.11.tar.gz

SDL_IMAGE           := SDL_image
SDL_IMAGE_VERSION   := $(SDL_IMAGE)-1.2.12
SDL_IMAGE_SRC       := $(SDL_IMAGE_VERSION).tar.gz
SDL_IMAGE_DOWNLOAD  := "http://www.libsdl.org/projects/SDL_image/release/SDL_image-1.2.12.tar.gz"

SDL_MIXER           := SDL_mixer
SDL_MIXER_VERSION   := $(SDL_MIXER)-1.2.12
SDL_MIXER_SRC       := $(SDL_MIXER_VERSION).tar.gz
SDL_MIXER_DOWNLOAD  := "http://www.libsdl.org/projects/SDL_mixer/release/SDL_mixer-1.2.12.tar.gz"

SDL_NET           := SDL_net
SDL_NET_VERSION   := $(SDL_NET)-1.2.8
SDL_NET_SRC       := $(SDL_NET_VERSION).tar.gz
SDL_NET_DOWNLOAD  := "http://www.libsdl.org/projects/SDL_net/release/SDL_net-1.2.8.tar.gz"

SDL_GFX           := SDL_gfx
SDL_GFX_VERSION   := $(SDL_GFX)-2.0.25
SDL_GFX_SRC       := $(SDL_GFX_VERSION).tar.gz
SDL_GFX_DOWNLOAD  := "https://sourceforge.net/projects/sdlgfx/files/SDL_gfx-2.0.25.tar.gz/download"

SDL_SOUND           := SDL_sound
SDL_SOUND_VERSION   := $(SDL_SOUND)-1.0.3
SDL_SOUND_SRC     := $(SDL_SOUND_VERSION).tar.gz
SDL_SOUND_DOWNLOAD  := "https://www.icculus.org/SDL_sound/downloads/SDL_sound-1.0.3.tar.gz"

export LIBS_PATH  	:= $(DEVKITPRO)/portlibs
export PATH         := $(DEVKITARM)/bin:$(LIBS_PATH)/3ds/bin:$(LIBS_PATH)/armv6k/bin:$(LIBS_PATH)/3ds/include/SDL:$(PATH)
export PKG_CONFIG   := $(PWD)/arm-none-eabi-pkg-config

export CFLAGS       := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft -O3 -g -mword-relocations -std=gnu++11 \
						-fno-rtti -fno-exceptions -fomit-frame-pointer -ffast-math -ffunction-sections -D_3DS
export CPPFLAGS     := -I$(DEVKITPRO)/libctru/include -I$(LIBS_PATH)/3ds/include -I$(LIBS_PATH)/armv6k/include 
export LDFLAGS      := -L$(LIBS_PATH)/3ds/lib -L$(LIBS_PATH)/armv6k/lib -L$(LIBS_PATH)/armv6k/lib -L$(DEVKITPRO)/libctru/lib 

.PHONY: all old_all install clean download \
        $(SDL) \
        $(SDL_TTF) \
        $(SDL_MIXER) \
        $(SDL_IMAGE) \
        $(SDL_NET) \
        $(SDL_GFX) \
        $(SDL_SOUND) 
		
all: SDL SDL_ttf SDL_mixer SDL_image SDL_net SDL_gfx SDL_sound install
	@echo "Finished!"

old_all:
	@echo "Please choose one of the following targets:"
	@echo "  $(SDL)"
	@echo "  $(SDL_TTF)"
	@echo "  $(SDL_MIXER)"
	@echo "  $(SDL_IMAGE)"
	@echo "  $(SDL_NET)"
	@echo "  $(SDL_GFX)"
	@echo "  $(SDL_SOUND)"

DOWNLOAD = wget --no-check-certificate -O "$(1)" "$(2)" || curl -Lo "$(1)" "$(2)"

$(SDL_TTF_SRC):
	$(call DOWNLOAD,$@,$(SDL_TTF_DOWNLOAD))
	
$(SDL_IMAGE_SRC):
	$(call DOWNLOAD,$@,$(SDL_IMAGE_DOWNLOAD))
    
$(SDL_MIXER_SRC):
	$(call DOWNLOAD,$@,$(SDL_MIXER_DOWNLOAD))

$(SDL_NET_SRC):
	$(call DOWNLOAD,$@,$(SDL_NET_DOWNLOAD))

$(SDL_GFX_SRC):
	$(call DOWNLOAD,$@,$(SDL_GFX_DOWNLOAD))

$(SDL_SOUND_SRC):
	$(call DOWNLOAD,$@,$(SDL_SOUND_DOWNLOAD))

$(SDL):
	@cd $(SDL_VERSION) &&\
	 ./autogen.sh &&\
	 ./configure --prefix=$(LIBS_PATH)/3ds --host=arm-none-eabi --enable-n3ds --disable-shared --enable-static
	@$(MAKE) -C $(SDL_VERSION) >&1
	
$(SDL_TTF): $(SDL_TTF_SRC)
	@[ -d $(SDL_TTF_VERSION) ] || tar -xzf $<
	@cd $(SDL_TTF_VERSION) && \
	 ./autogen.sh &&\
	 ./configure --prefix=$(LIBS_PATH)/3ds --host=arm-none-eabi --disable-shared --enable-static
	@$(MAKE) -C $(SDL_TTF_VERSION)

$(SDL_IMAGE): $(SDL_IMAGE_SRC)
	@[ -d $(SDL_IMAGE_VERSION) ] || tar -xzf $<
	@cd $(SDL_IMAGE_VERSION) && \
	 cp ../SDL_image_Makefile Makefile
#	 ./autogen.sh && \
#	 ./configure --prefix=$(LIBS_PATH)/3ds --host=arm-none-eabi --disable-shared --enable-static \	
#	 --enable-bmp --enable-gif --enable-lbm --enable-pcx --enable-pnm --enable-tga --enable-xcf --enable-xpm --enable-xv --enable-jpg --enable-png
	@$(MAKE) -C $(SDL_IMAGE_VERSION)
        
$(SDL_MIXER): $(SDL_MIXER_SRC)
	@[ -d $(SDL_MIXER_VERSION) ] || tar --exclude=SDL_mixer-1.2.12/Xcode -xzf $< 
	@cd $(SDL_MIXER_VERSION) && \
	 patch -Np1 -i ../$(SDL_MIXER_VERSION).patch && \
	 ./autogen.sh &&\
     ./configure --prefix=$(LIBS_PATH)/3ds --host=arm-none-eabi --disable-shared --enable-static \
	 --disable-music-cmd --enable-music-wave --enable-music-midi --enable-music-mod --enable-music-mp3-mad-gpl --enable-music-ogg --enable-music-ogg-tremor 
	@$(MAKE) -C $(SDL_MIXER_VERSION)

$(SDL_NET): $(SDL_NET_SRC)
	@[ -d $(SDL_NET_VERSION) ] || tar -xzf $<
	@cd $(SDL_NET_VERSION) && \
	 patch -Np1 -i ../$(SDL_NET_VERSION).patch && \
	 ./autogen.sh &&\
	 ./configure --prefix=$(LIBS_PATH)/3ds --host=arm-none-eabi --disable-shared --enable-static
	@$(MAKE) -C $(SDL_NET_VERSION)

$(SDL_GFX): $(SDL_GFX_SRC)
	@[ -d $(SDL_GFX_VERSION) ] || tar -xzf $<
	@cd $(SDL_GFX_VERSION) && \
	 cp ../SDL_gfx_Makefile Makefile
#	 ./autogen.sh &&\
#	 ./configure --prefix=$(LIBS_PATH)/3ds --host=arm-none-eabi --disable-shared --enable-static
	@$(MAKE) -C $(SDL_GFX_VERSION)

$(SDL_SOUND): $(SDL_SOUND_SRC)
	@[ -d $(SDL_SOUND_VERSION) ] || tar -xzf $<
	@cd $(SDL_SOUND_VERSION) && \
	 ./configure --prefix=$(LIBS_PATH)/3ds --host=arm-none-eabi --disable-shared --enable-static
	@$(MAKE) -C $(SDL_SOUND_VERSION)

install:
	@[ ! -d $(SDL_VERSION) ] || $(MAKE) -C $(SDL_VERSION) install
	@[ ! -d $(SDL_TTF_VERSION) ] || $(MAKE) -C $(SDL_TTF_VERSION) install
	@[ ! -d $(SDL_IMAGE_VERSION) ] || $(MAKE) -C $(SDL_IMAGE_VERSION) install
	@[ ! -d $(SDL_MIXER_VERSION) ] || $(MAKE) -C $(SDL_MIXER_VERSION) install
	@[ ! -d $(SDL_NET_VERSION) ] || $(MAKE) -C $(SDL_NET_VERSION) install
	@[ ! -d $(SDL_GFX_VERSION) ] || $(MAKE) -C $(SDL_GFX_VERSION) install
	@[ ! -d $(SDL_SOUND_VERSION) ] || $(MAKE) -C $(SDL_SOUND_VERSION) install

clean:
	@$(RM) -r $(SDL_TTF_VERSION)
	@$(RM) -r $(SDL_IMAGE_VERSION)
	@$(RM) -r $(SDL_MIXER_VERSION)
	@$(RM) -r $(SDL_NET_VERSION)
	@$(RM) -r $(SDL_GFX_VERSION)
	@$(RM) -r $(SDL_SOUND_VERSION)	