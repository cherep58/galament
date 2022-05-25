#ifndef GALAMENT_CLIENT_HELPER_RANDOM_GENERATOR_H
#define GALAMENT_CLIENT_HELPER_RANDOM_GENERATOR_H

#include "common/data_types/uuid.h"

#include <random>
#include <chrono>

namespace galament::client::helper {

class RandomGenerator {
public:
	RandomGenerator();

	template <class T>
	T GenerateReal(T min, T max) {
		std::uniform_real_distribution<T> dis(min, max);
		return dis(rng_);
	}

	template <class T>
	T GenerateInt(T min, T max) {
		std::uniform_int_distribution<T> dis(min, max);
		return dis(rng_);
	}

	template <class T>
	T GenerateDuration(T min, T max) {
		std::uniform_int_distribution<typename T::rep> dis(min.count(), max.count());
		return T(dis(rng_));
	}

	common::data_types::Uuid GenerateUuid();

private:
	std::mt19937 rng_;
};

} // namespace galament::client::helper

#endif