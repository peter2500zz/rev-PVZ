#include "pch.h"
#include "graphics.h"


void graphics::destructor(Graphics* g)
{
	using destructor = void(__thiscall*)(Graphics* g);

	destructor fn = reinterpret_cast<destructor>(0x00586B10);

	fn(g);
}

DDImage* graphics::get_DDImage(Graphics* g)
{
	return *reinterpret_cast<DDImage**>(reinterpret_cast<uintptr_t>(g) + 0x4);
}

Color* graphics::get_Color(Graphics* g)
{
	return reinterpret_cast<Color*>(reinterpret_cast<uintptr_t>(g) + 0x30);
}

DrawMode* graphics::get_DrawMode(Graphics* g)
{
	return reinterpret_cast<DrawMode*>(reinterpret_cast<uintptr_t>(g) + 0x44);
}

float_t* graphics::get_mTransX(Graphics* g)
{
	return reinterpret_cast<float_t*>(reinterpret_cast<uintptr_t>(g) + 0x8);
}

float_t* graphics::get_mTransY(Graphics* g)
{
	return reinterpret_cast<float_t*>(reinterpret_cast<uintptr_t>(g) + 0xC);
}

Graphics* graphics::Create(Graphics* g)
{
	using Create = Graphics * (__stdcall*)(Graphics* g);

	Create fn = reinterpret_cast<Create>(0x00586C30);

	return fn(g);
}

void graphics::DrawRect(
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

void graphics::SetColor(Graphics* g, const Color& color)
{
	__asm {
		mov eax, color
		mov ecx, g

		mov edx, 0x00586CC0
		call edx
	}
}

void graphics::DrawLine(
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

void ddimage::DrawLine(
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
