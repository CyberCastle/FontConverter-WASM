#ifndef __FONT_CONVERTER_H__
#define __FONT_CONVERTER_H__

#include <cstdint>
#include <sstream>

class FontConverter {
  private:
    // C++ font template
    std::string cplusTemplate = R"(// Code generated by Adafruit fontconvert
const uint8_t $fontName$$fontSize$pt$bits$bBitmaps[] PROGMEM = { 
  $bitmapData$ };

const GFXglyph $fontName$$fontSize$pt$bits$bGlyphs[] PROGMEM = {
$glyphData$ }; 

const GFXfont $fontName$$fontSize$pt$bits$b PROGMEM = {
  (uint8_t  *)$fontName$$fontSize$pt$bits$bBitmaps,
  (GFXglyph *)$fontName$$fontSize$pt$bits$bGlyphs,
  $firstChar$, $lastChar$, $yAdvance$ };)";

    // JSON font template
    std::string jsonTemplate = R"({
    "name":"$fontName$",
    "size":$fontSize$,
    "style":"$fontStyle$",
    "bitmap":[
  $bitmapData$
        ],
    "glyph":[
$glyphData$],
    "bits":$bits$,
    "firstChar":"$firstChar$",
    "lastChar":"$lastChar$",
    "yAdvance":$yAdvance$
})";

    uint8_t row = 0, sum = 0, bit = 0x80, firstCall = 1;
    int outType = 0;
    std::string templateToFill;
    std::stringstream bitmapBuilder;

    void enbit(uint8_t value);
    void fillFontInfo(std::string, int, int, std::string);
    void fillBitmapInfo();
    void fillGlyphInfo();
    void fillFontSpec(int, int, int);

  public:
    int convert(char *fileName, int fontSize, int firstChar, int lastChar);
    const char *getCode();

    FontConverter() {
        this->templateToFill = this->cplusTemplate;
    }
    FontConverter(int outType) {
        this->outType = outType;
        this->templateToFill = this->cplusTemplate;
        if (outType == 1) {
            this->templateToFill = this->jsonTemplate;
        }
    }
    ~FontConverter() {
        // Idea: https://stackoverflow.com/a/20792/11454077
        this->bitmapBuilder.str(std::string());
    }
};

#endif /* __FONT_CONVERTER_H__ */