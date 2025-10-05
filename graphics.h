#pragma once

struct Font;

// 字体
namespace font
{
    inline Font* FONT_BRIANNETOD16 = *reinterpret_cast<Font**>(0x006A7224);
}

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

    inline Color invisible() { return Color{ 0,   0,   0, 0 }; }

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

struct Graphics
{   // 0x68
    // 0x0 vtable*
    // 0x4 DDImage*
	// 0x8 uint32_t mTransX
    // 0xC uint32_t mTransY
    // ...
    // 0x30 Color
	// 0x40 Font*
    // 0x44 DrawMode*
    // ...
};

struct FakeMsvcString32
{
    uint32_t pad0;        // [0] 未用
    const char* ptr;      // [1] -> 你的 C 字符串缓冲
    uint32_t pad8;        // [2] 未用
    uint32_t padC;        // [3] 未用
    uint32_t pad10;       // [4] 未用
    uint32_t size;        // [5] -> 长度
    uint32_t capacity;    // [6] -> 容量 (>=16 以禁用SSO)
};

inline FakeMsvcString32 MakeFakeFrom(const std::string& s)
{
    FakeMsvcString32 f{};
    f.ptr = s.data();                                 // 只读指针
    f.size = static_cast<uint32_t>(s.size());
    uint32_t cap = f.size + 1;
    if (cap < 16) cap = 16;                           // 强制非 SSO
    f.capacity = cap;
    return f;
}

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

    inline void SetFont(Graphics* g, Font* theFont)
	{
		__asm {
            mov eax, g
            mov ecx, theFont

            mov edx, 0x00586CB0
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

    inline void FillRect(
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

            mov edx, 0x00586D50
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

    inline uint32_t DrawStringWordWrapped(Graphics* g, uint32_t theX, uint32_t theY, const std::string& line)
	{
        uint32_t stringHeight;

        const FakeMsvcString32 fake = MakeFakeFrom(line);

        __asm {
            push ebx
            push esi

            push theY
            lea  ebx, fake
            mov esi, g
            mov eax, theX

            mov edx, 0x005886B0
            call edx

            mov stringHeight, eax

            pop esi
            pop ebx
        }

        return stringHeight;
	}
}
