#ifndef GUARD_PALETTE_UTIL_H
#define GUARD_PALETTE_UTIL_H

struct PulseBlendSettings
{
    u16 blendColor;
    u16 paletteOffset;
    u8 numColors;
    u8 delay;
    u8 numFadeCycles;
    s8 maxBlendCoeff:4;
    s8 fadeType:2;
    s8 restorePaletteOnUnload:1;
    s8 unk7_7:1;
};

struct PulseBlendPalette
{
    u8 paletteSelector;
    u8 blendCoeff:4;
    u8 fadeDirection:1;
    s8 unk1_5:1;
    s8 available:1;
    u32 inUse:1;
    u8 delayCounter;
    u8 fadeCycleCounter;
    struct PulseBlendSettings pulseBlendSettings;
};

struct PulseBlend
{
    u16 usedPulseBlendPalettes;
    struct PulseBlendPalette pulseBlendPalettes[16];
};

#define FLASHUTIL_USE_EXISTING_COLOR (1 << 15)

struct RouletteFlashSettings
{
    u16 color;
    u16 paletteOffset;
    u8 numColors;
    u8 delay;
    u8 unk6;      // Set but never used
    s8 numFadeCycles:5;
    s8 unk7_5:2;  // Set but never used
    s8 colorDeltaDir:1;
};

struct RouletteFlashPalette
{
    u8 state:7;
    u8 available:1;
    u8 delayCounter;
    s8 fadeCycleCounter;
    s8 colorDelta;
    struct RouletteFlashSettings settings;
};

struct RouletteFlashUtil
{
    u8 enabled;
    u8 unused;
    u16 flags;
    struct RouletteFlashPalette palettes[16];
};

void RouletteFlash_Reset(struct RouletteFlashUtil *);
u8 RouletteFlash_Add(struct RouletteFlashUtil *, u8, const struct RouletteFlashSettings *);
void RouletteFlash_Run(struct RouletteFlashUtil *);
void RouletteFlash_Enable(struct RouletteFlashUtil *, u16);
void RouletteFlash_Stop(struct RouletteFlashUtil *, u16);
void InitPulseBlend(struct PulseBlend *);
int InitPulseBlendPaletteSettings(struct PulseBlend *, const struct PulseBlendSettings *);
void UnloadUsedPulseBlendPalettes(struct PulseBlend *, u16, u8);
void MarkUsedPulseBlendPalettes(struct PulseBlend *, u16, u8);
void UnmarkUsedPulseBlendPalettes(struct PulseBlend *, u16, u8);
void UpdatePulseBlend(struct PulseBlend *);
void FillTilemapRect(u16 *dest, u16 src, u8 left, u8 top, u8 width, u8 height);
void SetTilemapRect(u16 *dest, u16 *src, u8 left, u8 top, u8 width, u8 height);

#endif // GUARD_PALETTE_UTIL_H
