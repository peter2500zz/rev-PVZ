#pragma once

struct Color
{
    DWORD r;
    DWORD g;
    DWORD b;
    DWORD a;
};

namespace color
{
    inline Color rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        return Color {
            static_cast<DWORD>(r),
            static_cast<DWORD>(g),
            static_cast<DWORD>(b),
            static_cast<DWORD>(a)
        };
    }

    inline Color rgb(uint8_t r, uint8_t g, uint8_t b)
    {
        return Color{
            static_cast<DWORD>(r),
            static_cast<DWORD>(g),
            static_cast<DWORD>(b),
            255
        };
    }

    inline Color black() { return Color{ 0,   0,   0, 255 }; }
    inline Color white() { return Color{ 255, 255, 255, 255 }; }
    inline Color red() { return Color{ 255,   0,   0, 255 }; }
    inline Color green() { return Color{ 0, 255,   0, 255 }; }
    inline Color blue() { return Color{ 0,   0, 255, 255 }; }
    inline Color yellow() { return Color{ 255, 255,   0, 255 }; }
    inline Color cyan() { return Color{ 0, 255, 255, 255 }; }
    inline Color magenta() { return Color{ 255,   0, 255, 255 }; }
    inline Color orange() { return Color{ 255, 165,   0, 255 }; }
    inline Color purple() { return Color{ 128,   0, 128, 255 }; }
    inline Color gray() { return Color{ 128, 128, 128, 255 }; }
    inline Color silver() { return Color{ 192, 192, 192, 255 }; }
    inline Color brown() { return Color{ 165,  42,  42, 255 }; }
    inline Color pink() { return Color{ 255, 192, 203, 255 }; }
}

using DrawMode = uint32_t;

struct DDImage;

namespace ddimage
{
    void DrawLine(
        DDImage* ddimage, 
        double_t theStartX, 
        double_t theStartY, 
        double_t theEndX, 
        double_t theEndY, 
        const Color& theColor, 
        DrawMode theDrawMode
    );
}

struct Graphics;

namespace graphics
{
	// 我自己实现的函数
	void destructor(Graphics* g);
    DDImage* get_DDImage(Graphics* g);
    Color* get_Color(Graphics* g);
    DrawMode* get_DrawMode(Graphics* g);
    float_t* get_mTransX(Graphics* g);
    float_t* get_mTransY(Graphics* g);

	// 实现的自带函数
	Graphics* Create(Graphics* g);
    void SetColor(Graphics* g, const Color& color);
	void DrawRect(
        Graphics* g, 
        uint32_t theX, 
        uint32_t theY, 
        uint32_t theWidth, 
        uint32_t theHeight
    );
    void DrawLine(
        Graphics* g, 
        uint32_t theStartX, 
        uint32_t theStartY, 
        uint32_t theEndX, 
        uint32_t theEndY
    );
}
