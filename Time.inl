#include <glad/glad.h>
#include <GLFW/glfw3.h>

template <typename T>
inline bool CheckIfEndTime(T& time, T& timebasic, T& TimeAfterWork) {
	if (timebasic >= TimeAfterWork) { return true; }
	else							{ return false; }
}

template <typename T> 
inline TimeValuesResultT<T> initTime(T& TimeWork) {
	TimeValuesResultT<T> TimeValues;
	TimeValues.TimeAfterWork = glfwGetTime() + TimeWork;
	TimeValues.TimeNow = glfwGetTime();
	TimeValues.TimeOfWork = TimeWork;

	return TimeValues;
}


