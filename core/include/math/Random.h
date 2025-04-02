#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <random>

#include "math/Constant.h"

namespace NameSpace_Core::NameSpace_Math {

	template<typename NumericType>
	using uniform_distribution = typename std::conditional<std::is_integral<NumericType>::value,
		std::uniform_int_distribution<NumericType>,
		std::uniform_real_distribution<NumericType>>::type;

	template<typename RandomEngine = std::default_random_engine>
	class RandomNumberGenerator  final {
	private:
		RandomEngine m_engine;

	public:
		template<typename... Params>
		explicit RandomNumberGenerator(Params&&... params) : m_engine(std::forward<Params>(params)...) {
		}

		template<typename... Params>
		void Seed(Params&&... seeding)
		{
			m_engine.seed(std::forward<Params>(seeding)...);
		}

		template<typename DistributionFunc, typename... Params>
		typename DistributionFunc::result_type distribution(Params&&... params)
		{
			DistributionFunc dist(std::forward<Params>(params)...);
			return dist(m_engine);
		}

		template<typename NumericType>
		NumericType Uniform_Distribution(NumericType lower, NumericType upper)
		{
			if (lower == upper)
			{
				return lower;
			}
			return distribution<uniform_distribution<NumericType>>(lower, upper);
		}

		float uniformUnit() { return Uniform_Distribution(0.f, std::nextafter(1.f, FLT_MAX)); }

		float uniformSymmetry() { return Uniform_Distribution(-1.f, std::nextafter(1.f, FLT_MAX)); }

		bool bernoulliDistribution(float probability) { return distribution<std::bernoulli_distribution>(probability); }

		float normalDistribution(float mean, float stddev)
		{
			return distribution<std::normal_distribution<float>>(mean, stddev);
		}

		template<typename DistributionFunc, typename Range, typename... Params>
		void Generator(Range&& range, Params&&... params)
		{
			// using ResultType = typename DistributionFunc::result_type;

			DistributionFunc dist(std::forward<Params>(params)...);
			return std::generate(std::begin(range), std::end(range), [&] { return dist(m_engine); });
		}
	};

	using Default_RNG = RandomNumberGenerator<std::mt19937>;
} // namespace NameSpace_Core::NameSpace_Math