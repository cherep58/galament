#include "random_generator.h"

#include "boost/uuid/random_generator.hpp"

namespace galament::client::helper {

RandomGenerator::RandomGenerator()
	: rng_(std::random_device()())
{
	;
}

common::data_types::Uuid RandomGenerator::GenerateUuid()
{
	boost::uuids::random_generator_mt19937 rand_generator;
	return rand_generator();
}

} // namespace galament::client::helper