#include "glmAnimation3D.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

template <typename T> inline T setCHANGE_DIRECTION_ROTATE_MATRIX() {

}
template <typename T> inline T setCHANGE_SIZE_Z() {

}
template <typename T> inline T setCHANGE_SIZE_Y() {

}
template <typename T> inline T setCHANGE_SIZE_X() {
	T* size2 = nullptr; size2 = new T;
	ImGui::SliderFloat("sizeX", &*size2, -2, 3);
	if (*size2 > -401602080) {
		LastedFloatFrameX = *size2;
		return *size2;
	}
	else {
		return LastedFloatFrameX;
	}
	delete size2;
}
template <typename T> inline T setADD_NODE_CHANGE_FOV() {

}
template <typename T> inline T setCHANGE_COLOR_OBJECT() {

}
template <typename T> inline T setCHANGE_COLOR_FRAME() {

}
template <typename T> inline T setCHANGE_POSITION_Z() {

}
template <typename T> inline T setCHANGE_POSITION_Y() {

}
template<typename T> inline T setCHANGE_POSITION_X() {

}
template<typename T> inline T setCHANGE_PERCENT_TEXTURE() {

}
template<typename T> inline T setCHANGE_CAMERA_SPEED() {

}
template<typename T> inline T setROTATE_AROUND_Z_MATRIX() {

}
template<typename T> inline T setROTATE_AROUND_Y_MATRIX() {

}
template<typename T> inline T setROTATE_AROUD_X_MATRIX() {

}
template<typename T> inline T setMOVE_CAMERA_DOWN() {

}
template<typename T> inline T setMOVE_CAMERA_UP() {

}
template<typename T> inline T setMOVE_CAMERA_RIGHT() {

}
template<typename T> inline T setMOVE_CAMERA_LEFT() {

}
