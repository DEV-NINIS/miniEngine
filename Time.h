#include <iostream>

#ifndef TIME
#define TIME

template <typename T> inline bool CheckIfEndTime(T& time, T& timeNow, T& TimeAfterWork);

template <typename T>
struct TimeValuesResultT {
	T TimeAfterWork;
	T TimeNow;
	T TimeOfWork;
};

template <typename T> inline TimeValuesResultT<T> initTime(T& TimeWork);

#include "Time.inl"





#endif