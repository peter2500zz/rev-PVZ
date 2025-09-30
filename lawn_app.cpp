#include "pch.h"
#include "lawn_app.h"


LawnApp* lawn_app::from_base_address(uintptr_t base_address) {
	return *reinterpret_cast<LawnApp**>(base_address);
}


Board* lawn_app::get_board(LawnApp* lawn_app) {
	return *reinterpret_cast<Board**>(reinterpret_cast<uintptr_t>(lawn_app) + 0x768);
}

WidgetManager* lawn_app::get_widget_manager(LawnApp* lawn_app) {
	return *reinterpret_cast<WidgetManager**>(reinterpret_cast<uintptr_t>(lawn_app) + 0x320);
}
