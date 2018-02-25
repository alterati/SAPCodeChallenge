/*
 *  MCColorUtil.h *
 *  Created by Daniel Cascais on 3/19/11.
 *  Copyright 2011 MeLLmo. All rights reserved.
 *
 */

#ifndef MC_COLOR_UTIL_H
#define MC_COLOR_UTIL_H


#include <math.h>
#include "MCMathUtils.h"

#define HEX_TO_RGB_RED(hex) ((hex >> 16) & 0xFF) / 255.0f
#define HEX_TO_RGB_GREEN(hex) ((hex >> 8) & 0xFF) / 255.0f
#define HEX_TO_RGB_BLUE(hex) (hex & 0xFF) / 255.0f

#define HEX_TO_RGBA_RED(hex) ((hex >> 24) & 0xFF) / 255.0f
#define HEX_TO_RGBA_GREEN(hex) ((hex >> 16) & 0xFF) / 255.0f
#define HEX_TO_RGBA_BLUE(hex) ((hex >> 8) & 0xFF) / 255.0f
#define HEX_TO_RGBA_ALPHA(hex) (hex & 0xFF) / 255.0f

#define RGB_TO_RGBA(hex) ((hex << 0x8) + 0xFF)
#define RGBA_TO_RGB(hex) (hex >> 8)

/**
 *  Performs a linear brightness adjustment of an RGB color.
 *
 *  <p>The same amount is added to the red, green, and blue channels
 *  of an RGB color.
 *  Each color channel is limited to the range 0 through 255.</p>
 *
 *  @param rgb Original RGB color.
 *
 *  @param brite Amount to be added to each color channel.
 *  The range for this parameter is -255 to 255;
 *  -255 produces black while 255 produces white.
 *  If this parameter is 0, the RGB color returned
 *  is the same as the original color.
 *
 *  @return New RGB color.
 */
static inline unsigned int MCColorUtilAdjustBrightness(unsigned int rgb, unsigned int brite)
{
    unsigned int r = MCMaxUnsignedInt(MCMinUnsignedInt(((rgb >> 16) & 0xFF) + brite, 255), 0);
    unsigned int g = MCMaxUnsignedInt(MCMinUnsignedInt(((rgb >> 8) & 0xFF) + brite, 255), 0);
    unsigned int b = MCMaxUnsignedInt(MCMinUnsignedInt((rgb & 0xFF) + brite, 255), 0);

    return (r << 16) | (g << 8) | b;
}

/**
 *  Performs a scaled brightness adjustment of an RGB color.
 *
 *  @param rgb Original RGB color.
 *
 *  @param brite The percentage to brighten or darken the original color.
 *  If positive, the original color is brightened toward white
 *  by this percentage. If negative, it is darkened toward black
 *  by this percentage.
 *  The range for this parameter is -100 to 100;
 *  -100 produces black while 100 produces white.
 *  If this parameter is 0, the RGB color returned
 *  is the same as the original color.
 *
 *  @return New RGB color.
 */
static inline unsigned int MCColorUtilAdjustBrightness2(unsigned int rgb, float brite)
{
    unsigned int r;
    unsigned int g;
    unsigned int b;

    if (brite == 0.0f)
    {
        return rgb;
    }

    if (brite < 0.0f)
    {
        brite = (100.0f + brite) / 100.0f;

        r = roundf((float) ((rgb >> 16) & 0xFF) * brite);
        g = roundf((float) ((rgb >> 8) & 0xFF) * brite);
        b = roundf((float) (rgb & 0xFF) * brite);
    }
    else // brite > 0
    {
        brite /= 100.0f;
        r = ((rgb >> 16) & 0xFF);
        g = ((rgb >> 8) & 0xFF);
        b = (rgb & 0xFF);

        r += ((0xFF - r) * brite);
        g += ((0xFF - g) * brite);
        b += ((0xFF - b) * brite);

        r = MCMinUnsignedInt(r, 255);
        g = MCMinUnsignedInt(g, 255);
        b = MCMinUnsignedInt(b, 255);
    }

    return (r << 16) | (g << 8) | b;
}

/**
 *  Performs an RGB multiplication of two RGB colors.
 *
 *  <p>This always results in a darker number than either
 *  original color unless one of them is white,
 *  in which case the other color is returned.</p>
 *
 *  @param rgb1 First RGB color.
 *
 *  @param rgb2 Second RGB color.
 *
 *  @return RGB multiplication of the two colors.
 */
static inline unsigned int MCColorUtilRGBbMultiply(unsigned int rgb1, unsigned int rgb2)
{
    unsigned int r1 = (rgb1 >> 16) & 0xFF;
    unsigned int g1 = (rgb1 >> 8) & 0xFF;
    unsigned int b1 = rgb1 & 0xFF;

    unsigned int r2 = (rgb2 >> 16) & 0xFF;
    unsigned int g2 = (rgb2 >> 8) & 0xFF;
    unsigned int b2 = rgb2 & 0xFF;

    return ((r1 * r2 / 255) << 16) | ((g1 * g2 / 255) << 8) | (b1 * b2 / 255);
}

/**
 * Performs an RGB interpolation of two RGB colors.
 *
 * @param fromColor Color to interpolate from.
 *
 * @param toColor Color to interpolate to.
 *
 * @param progress Step between 0.0 - 1.0 that indicates the progress of the interpolation.
 *
 * @return RGB interpolation of the two colors.
 */
static inline unsigned int MCColorUtilInterpolateColors(unsigned int fromColor, unsigned int toColor, float progress)
{
    float q = 1.0f - progress;

    unsigned int fromAlpha = (fromColor >> 24) & 0xFF;
    unsigned int fromRed   = (fromColor >> 16) & 0xFF;
    unsigned int fromGreen = (fromColor >>  8) & 0xFF;
    unsigned int fromBlue  = fromColor         & 0xFF;

    unsigned int toAlpha = (toColor >> 24) & 0xFF;
    unsigned int toRed   = (toColor >> 16) & 0xFF;
    unsigned int toGreen = (toColor >> 8)  & 0xFF;
    unsigned int toBlue  = toColor         & 0xFF;

    unsigned int interpolatedAlpha = (int) roundf(fromAlpha * q + toAlpha * progress);
    unsigned int interpolatedRed   = (int) roundf(fromRed   * q + toRed   * progress);
    unsigned int interpolatedGreen = (int) roundf(fromGreen * q + toGreen * progress);
    unsigned int interpolatedBlue  = (int) roundf(fromBlue  * q + toBlue  * progress);

    unsigned int interpolatedColor = interpolatedAlpha << 24 | interpolatedRed << 16 | interpolatedGreen << 8 | interpolatedBlue;

    return interpolatedColor;
}

static inline unsigned int MCColorUtilRGBToRGBA(unsigned int rgb, unsigned int a)
{
    return (rgb << 8) | a;
}

typedef unsigned int MCColor;

struct MCColorHSV
{
    float h;
    float s;
    float v;
};
typedef struct MCColorHSV MCColorHSV;

struct MCColorHSL
{
    float h;
    float s;
    float l;
};
typedef struct MCColorHSL MCColorHSL;

struct MCColorRGB
{
    unsigned int r;
    unsigned int g;
    unsigned int b;
};
typedef struct MCColorRGB MCColorRGB;

static inline float hue2rgb(float p, float q, float t)
{
    if(t < 0)
    {
        t += 1;
    }

    if(t > 1)
    {
        t -= 1;
    }

    if(t < 1.0f / 6)
    {
        return p + (q - p) * 6 * t;
    }

    if(t < 1.0f / 2)
    {
        return q;
    }

    if(t < 2.0f / 3)
    {
        return p + (q - p) * (2.0f / 3 - t) * 6;
    }

    return p;
}

/**
 * Converts an RGB color value to HSL. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes r, g, and b are contained in the set [0, 255] and
 * returns h, s, and l in the set [0, 1].
 *
 * @param   Number  r       The red color value
 * @param   Number  g       The green color value
 * @param   Number  b       The blue color value
 * @return  Array           The HSL representation
 */
static inline MCColorHSL rgbToHsl(MCColorRGB colorRGB)
{
    float r = (float) colorRGB.r / 255;
    float g = (float) colorRGB.g / 255;
    float b = (float) colorRGB.b / 255;

    float max = fmaxf(fmaxf(r, g), b);
    float min = fminf(fminf(r, g), b);

    float sumOver2 = (max + min) / 2;
    float h = sumOver2;
    float s;// = sumOver2;
    float l = sumOver2;

    if(max == min)
    {
        h = s = 0; // achromatic
    }
    else
    {
        float d = max - min;

        s = l > 0.5f ? d / (2.0f - max - min) : d / (max + min);

        if (max == r)
        {
            h = (g - b) / d + (g < b ? 6 : 0);
        }
        else if (max == g)
        {
            h = (b - r) / d + 2;
        }
        else if (max == b)
        {
            h = (r - g) / d + 4;
        }

        h /= 6;
    }

    MCColorHSL colorHSL;
    colorHSL.h = h;
    colorHSL.s = s;
    colorHSL.l = l;

    return colorHSL;
}

/**
 * Converts an HSL color value to RGB. Conversion formula
 * adapted from http://en.wikipedia.org/wiki/HSL_color_space.
 * Assumes h, s, and l are contained in the set [0, 1] and
 * returns r, g, and b in the set [0, 255].
 *
 * @param   Number  h       The hue
 * @param   Number  s       The saturation
 * @param   Number  l       The lightness
 * @return  Array           The RGB representation
 */
static inline MCColorRGB hslToRgb(MCColorHSL colorHSL)
{
    float r;
    float g;
    float b;

    if(colorHSL.s == 0)
    {
        r = g = b = colorHSL.l; // achromatic
    }
    else
    {
        float q = colorHSL.l < 0.5 ? colorHSL.l * (1 + colorHSL.s) : colorHSL.l + colorHSL.s - colorHSL.l * colorHSL.s;
        float p = 2 * colorHSL.l - q;

        r = hue2rgb(p, q, colorHSL.h + 1.0f / 3);
        g = hue2rgb(p, q, colorHSL.h);
        b = hue2rgb(p, q, colorHSL.h - 1.0f / 3);
    }

    MCColorRGB colorRGB;
    colorRGB.r = r * 255;
    colorRGB.g = g * 255;
    colorRGB.b = b * 255;

    return colorRGB;
}

static inline MCColorRGB MCColorUtilRGBHexToMCColorRGB(unsigned int colorRGBHex)
{
    unsigned int r = (colorRGBHex >> 16) & 0xFF;
    unsigned int g = (colorRGBHex >> 8) & 0xFF;
    unsigned int b = colorRGBHex & 0xFF;

    MCColorRGB colorRGB;
    colorRGB.r = r;
    colorRGB.g = g;
    colorRGB.b = b;

    return colorRGB;
}

static inline unsigned int MCColorUtilMCColorRGBToRGBHex(MCColorRGB colorRGB)
{
    return (colorRGB.r << 16) | (colorRGB.g << 8) | colorRGB.b;
}

static inline unsigned int MCColorUtilHexToRGBRed(unsigned int hex)
{
    return ((hex >> 16) & 0xFF) / 255.0f;
}

static inline unsigned int MCColorUtilHexToRGBGreen(unsigned int hex)
{
    return ((hex >> 8) & 0xFF) / 255.0f;
}

static inline unsigned int MCColorUtilHexToRGBBlue(unsigned int hex)
{
    return (hex & 0xFF) / 255.0f;
}

#if !TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR

unsigned int MCColorUtilAdjustBrightnessWrap(unsigned int rgb, unsigned int brite);
unsigned int MCColorUtilAdjustBrightness2Wrap(unsigned int rgb, float brite);
unsigned int MCColorUtilRGBbMultiplyWrap(unsigned int rgb1, unsigned int rgb2);
unsigned int MCColorUtilInterpolateColorsWrap(unsigned int fromColor, unsigned int toColor, float progress);
unsigned int MCColorUtilRGBToRGBAWrap(unsigned int rgb, unsigned int a);
float hue2rgbWrap(float p, float q, float t);
MCColorHSL rgbToHslWrap(MCColorRGB colorRGB);
MCColorRGB hslToRgbWrap(MCColorHSL colorHSL);
MCColorHSV rgbToHsvWrap(MCColorRGB colorRGB);
MCColorRGB hsvToRgbWrap(MCColorHSV colorHSV);
MCColorRGB MCColorUtilRGBHexToMCColorRGBWrap(unsigned int colorRGBHex);
unsigned int MCColorUtilMCColorRGBToRGBHexWrap(MCColorRGB colorRGB);
unsigned int MCColorUtilHexToRGBRedWrap(unsigned int hex);
unsigned int MCColorUtilHexToRGBGreenWrap(unsigned int hex);
unsigned int MCColorUtilHexToRGBBlueWrap(unsigned int hex);

#endif // !TARGET_OS_MAC && !TARGET_OS_IPHONE && !TARGET_IPHONE_SIMULATOR

#endif
