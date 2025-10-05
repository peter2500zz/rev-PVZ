#include "pch.h"
#include "hook.h"

#include "lawn_app.h"
#include "widget_manager.h"
#include "board.h"


namespace
{
	// LawnApp构造
	MID_HOOK post_lawn_app_constructor_origin = nullptr;

	// 在LawnApp构造完毕后赋值指针
	void __stdcall post_lawn_app_constructor(LawnApp* lawn_app)
	{
		//debug(L"LawnApp被构造");

		theLawnApp = lawn_app;
	}

	__declspec(naked) void post_lawn_app_constructor_helper()
	{
		__asm {
			pushad
			pushfd

			push esi
			call post_lawn_app_constructor

			popfd
			popad

			jmp post_lawn_app_constructor_origin
		}
	}

	// LawnApp析构
	MID_HOOK post_lawn_app_destructor_origin = nullptr;

	// 在LawnApp析构时清空指针
	void post_lawn_app_destructor()
	{
		theLawnApp = nullptr;

		//debug(L"LawnApp析构成功");

		post_lawn_app_destructor_origin();
	}

	// WidgetManager构造
	MID_HOOK post_widget_manager_constructor_origin = nullptr;

	void __stdcall post_widget_manager_constructor(WidgetManager* wm)
	{
		//debug(L"WidgetManager被构造");

		theWidgetManager = wm;
	}

	__declspec(naked) void post_widget_manager_constructor_helper()
	{
		__asm {
			pushad
			pushfd

			push esi
			call post_widget_manager_constructor

			popfd
			popad

			jmp post_widget_manager_constructor_origin
		}
	}

	// WidgetManager析构
	MID_HOOK post_widget_manager_destructor_origin = nullptr;

	void post_widget_manager_destructor()
	{
		theWidgetManager = nullptr;

		//debug(L"WidgetManager析构成功");

		post_widget_manager_destructor_origin();
	}
}

void classlifetime::hook() {
	// LawnApp
	MH_CreateHook(
		POST_LAWNAPP_CONSTRUCTOR,
		&post_lawn_app_constructor_helper,
		reinterpret_cast<LPVOID*>(&post_lawn_app_constructor_origin)
	);
	MH_EnableHook(POST_LAWNAPP_CONSTRUCTOR);

	MH_CreateHook(
		POST_LAWNAPP_DESTRUCTOR,
		&post_lawn_app_destructor,
		reinterpret_cast<LPVOID*>(&post_lawn_app_destructor_origin)
	);
	MH_EnableHook(POST_LAWNAPP_DESTRUCTOR);

	// WidgetManager
	MH_CreateHook(
		POST_WIDGETMANAGER_CONSTRUCTOR,
		&post_widget_manager_constructor_helper,
		reinterpret_cast<LPVOID*>(&post_widget_manager_constructor_origin)
	);
	MH_EnableHook(POST_WIDGETMANAGER_CONSTRUCTOR);

	MH_CreateHook(
		POST_WIDGETMANAGER_DESTRUCTOR,
		&post_widget_manager_destructor,
		reinterpret_cast<LPVOID*>(&post_widget_manager_destructor_origin)
	);
	MH_EnableHook(POST_WIDGETMANAGER_DESTRUCTOR);
}
