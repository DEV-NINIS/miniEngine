#include <iostream>

#ifndef TIME
#define TIME

namespace Time {
	template <typename T>
	struct TimeValuesResultT {
		T TimeAfterWork;
		T TimeNow;
		T TimeOfWork;
	};
	template <typename T> inline bool CheckIfEndTime(TimeValuesResultT<T>& timeValues);
	template <typename T> inline TimeValuesResultT<T> initTimeAndStartTime(T& TimeWork);
	
}
#include "Time.inl"





#endif