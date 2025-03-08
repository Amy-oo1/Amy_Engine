#pragma once

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <random>

#include "math/Constant.h"

namespace NameSpace_Core::NameSpace_Math {

    template<typename Numeric_Type>
    using Uniform_Distribution = typename std::conditional<
        std::is_integral<Numeric_Type>::value,
        std::uniform_int_distribution<Numeric_Type>,
        std::uniform_real_distribution<Numeric_Type>>::type;

    template<typename Random_Engine = std::default_random_engine>
    class Random_Number_Generator final {
    public:
        template<typename... Params>
        explicit Random_Number_Generator(Params&&... Temp_Params)
            : m_Engine{ std::forward<Params>(Temp_Params)... } {
        }

        template<typename... Params>
        void Seed(Params&&... Seeding) {
            this->m_Engine.seed(std::forward<Params>(Seeding)...);
        }

        template<typename Distribution_Func, typename... Params>
        typename Distribution_Func::result_type Distribution(Params&&... Temp_Params) const {
            Distribution_Func dist(std::forward<Params>(Temp_Params)...);
            return dist(m_Engine);
        }

        template<typename Numeric_Type>
        Numeric_Type Uniform_Distribution(Numeric_Type Lower, Numeric_Type Upper) const {
            return Distribution<Uniform_Distribution<Numeric_Type>>(Lower, Upper);
        }

        float Uniform_Unit() const {
            return Uniform_Distribution(0.f, std::nextafter(1.f, Math_MAX_FLOAT));
        }

        float Uniform_Symmetry() const {
            return Uniform_Distribution(-1.f, std::nextafter(1.f, Math_MAX_FLOAT));
        }

        bool Bernoulli_Distribution(float Probability) const {
            return Distribution<std::bernoulli_distribution>(Probability);
        }

        float Normal_Distribution(float Mean, float Standard_Deviation) const {
            return Distribution<std::normal_distribution<float>>(Mean, Standard_Deviation);
        }

        template<typename Distribution_Func, typename Range, typename... Params>
        void Generator(Range&& Temp_Range, Params&&... Temp_Params) const {
            std::generate(
                std::begin(Temp_Range),
                std::end(Temp_Range),
                [this, ...Temp_Params = std::forward<Params>(Temp_Params)]() mutable {
                    return Distribution<Distribution_Func>(Temp_Params...);
                }
            );
        }

    private:
        Random_Engine m_Engine;

    };

} // namespace NameSpace_Core::NameSpace_Math