#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>

namespace Time {

	template <typename T>
	inline bool CheckIfEndTime(TimeValuesResultT<T>& timeValues) {
		if (timeValues.TimeNow >= timeValues.TimeAfterWork) { return true; }
		else { return false; }
	}

	template <typename T>
	inline TimeValuesResultT<T> initTimeAndStartTime(T& TimeWork) {
		TimeValuesResultT<T> TimeValues;
		TimeValues.TimeAfterWork = static_cast<T>(glfwGetTime()) + TimeWork;
		TimeValues.TimeNow = static_cast<T>(glfwGetTime());
		TimeValues.TimeOfWork = TimeWork;

		return TimeValues;
	}
}


