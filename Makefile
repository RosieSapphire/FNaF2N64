GAME=fnaf2
BUILD_DIR=build
CFLAGS=-pedantic -Wextra -Iinclude
include $(N64_INST)/include/n64.mk

src = $(wildcard src/*.c)
assets_wav = $(wildcard assets/*.wav)
assets_png = $(wildcard assets/*.png)
assets_ttf = $(wildcard assets/*.ttf)

assets_conv = $(addprefix filesystem/,$(notdir $(assets_wav:%.wav=%.wav64))) \
              $(addprefix filesystem/,$(notdir $(assets_png:%.png=%.sprite))) \
              $(addprefix filesystem/,$(notdir $(assets_ttf:%.ttf=%.font64)))

AUDIOCONV_FLAGS=--yw-compress
#MKSPRITE_FLAGS=--compress
MKSPRITE_FLAGS=--dither RANDOM
#MKSPRITE_FLAGS=

all: $(GAME).z64

filesystem/%.wav64: assets/%.wav
	@mkdir -p $(dir $@)
	@echo "    [AUDIO] $@"
	@$(N64_AUDIOCONV) -o filesystem $<

filesystem/%.sprite: assets/%.png
	@mkdir -p $(dir $@)
	@echo "    [SPRITE] $@"
	@$(N64_MKSPRITE) $(MKSPRITE_FLAGS) -o filesystem "$<"

filesystem/medium.font64: assets/medium.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) --size 18 $(MKFONT_FLAGS) -o filesystem "$<"

filesystem/ocr.font64: assets/ocr.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) --size 24 $(MKFONT_FLAGS) -o filesystem "$<"

filesystem/ocr2.font64: assets/ocr2.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) --size 18 $(MKFONT_FLAGS) -o filesystem "$<"

filesystem/pixel.font64: assets/pixel.ttf
	@mkdir -p $(dir $@)
	@echo "    [FONT] $@"
	@$(N64_MKFONT) --size 8 $(MKFONT_FLAGS) -o filesystem "$<"

$(BUILD_DIR)/$(GAME).dfs: $(assets_conv)
$(BUILD_DIR)/$(GAME).elf: $(src:%.c=$(BUILD_DIR)/%.o)

$(GAME).z64: N64_ROM_TITLE="FNAF 2"
$(GAME).z64: $(BUILD_DIR)/$(GAME).dfs 

clean:
	rm -rf $(BUILD_DIR) $(GAME).z64

-include $(wildcard $(BUILD_DIR)/*.d)

.PHONY: all clean
