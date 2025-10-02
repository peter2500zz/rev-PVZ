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
    inline void DrawLine(
        DDImage* ddimage,
        double_t theStartX,
        double_t theStartY,
        double_t theEndX,
        double_t theEndY,
        const Color& theColor,
        DrawMode theDrawMode
    )
    {
        using DrawLine = void(__thiscall*)
            (
                DDImage* ddimage,
                double_t theStartX,
                double_t theStartY,
                double_t theEndX,
                double_t theEndY,
                const Color& theColor,
                DrawMode theDrawMode
                );

        DrawLine fn = reinterpret_cast<DrawLine>(0x0056E6A0);

        fn(
            ddimage,
            theStartX,
            theStartY,
            theEndX,
            theEndY,
            theColor,
            theDrawMode
        );
    }
}

struct Graphics;

namespace graphics
{
	// 我自己实现的函数
	inline void destructor(Graphics* g)
    {
        using destructor = void(__thiscall*)(Graphics* g);

        destructor fn = reinterpret_cast<destructor>(0x00586B10);

        fn(g);
    }

    inline DDImage* get_DDImage(Graphics* g)
    {
        return *reinterpret_cast<DDImage**>(reinterpret_cast<uintptr_t>(g) + 0x4);
    }

    inline Color* get_Color(Graphics* g)
    {
        return reinterpret_cast<Color*>(reinterpret_cast<uintptr_t>(g) + 0x30);
    }

    inline DrawMode* get_DrawMode(Graphics* g)
    {
        return reinterpret_cast<DrawMode*>(reinterpret_cast<uintptr_t>(g) + 0x44);
    }

    inline float_t* get_mTransX(Graphics* g)
    {
        return reinterpret_cast<float_t*>(reinterpret_cast<uintptr_t>(g) + 0x8);
    }

    inline float_t* get_mTransY(Graphics* g)
    {
        return reinterpret_cast<float_t*>(reinterpret_cast<uintptr_t>(g) + 0xC);
    }

	// 实现的自带函数
	inline Graphics* Create(Graphics* g)
    {
        using Create = Graphics * (__stdcall*)(Graphics* g);

        Create fn = reinterpret_cast<Create>(0x00586C30);

        return fn(g);
    }

    inline void SetColor(Graphics* g, const Color& color)
    {
        __asm {
            mov eax, color
            mov ecx, g

            mov edx, 0x00586CC0
            call edx
        }
    }

	inline void DrawRect(
        Graphics* g,
        uint32_t theX,
        uint32_t theY,
        uint32_t theWidth,
        uint32_t theHeight
    )
    {
        __asm {
            push theHeight
            push theWidth
            push theY
            push theX
            mov eax, g

            mov edx, 0x00586DE0
            call edx
        }
    }

    inline void DrawLine(
        Graphics* g,
        uint32_t theStartX,
        uint32_t theStartY,
        uint32_t theEndX,
        uint32_t theEndY
    )
    {
        DDImage* ddimage = get_DDImage(g);
        Color* color = get_Color(g);
        DrawMode* draw_mode = get_DrawMode(g);

        float_t* mTransX = get_mTransX(g);
        float_t* mTransY = get_mTransY(g);

        ddimage::DrawLine(
            ddimage,
            *mTransX + theStartX,
            *mTransY + theStartY,
            *mTransX + theEndX,
            *mTransY + theEndY,
            *color, *draw_mode
        );
    }
}
