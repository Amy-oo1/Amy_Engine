#pragma once

#include<cstdint>
#include<memory>
#include<utility>
#include<stdexcept>

#include "spdlog/spdlog.h"

namespace NameSpace_Core::NameSpace_System_Logger {

	using std::shared_ptr;

	class System_Logger final {
	public:
		enum class Level : std::uint8_t {
			trace = static_cast<std::uint8_t>(spdlog::level::trace),
			debug = static_cast<std::uint8_t>(spdlog::level::debug),
			info = static_cast<std::uint8_t>(spdlog::level::info),
			warn = static_cast<std::uint8_t>(spdlog::level::warn),
			err = static_cast<std::uint8_t>(spdlog::level::err),
			critical = static_cast<std::uint8_t>(spdlog::level::critical)
		};

	public:
		System_Logger(void);

		~System_Logger(void);

	private:
		System_Logger(const System_Logger&) = delete;
		System_Logger(System_Logger&&) = delete;

		System_Logger& operator=(const System_Logger&) = delete;
		System_Logger& operator=(System_Logger&&) = delete;

	public:
		static System_Logger& Get_Instance(void);

		template<typename... TARGS>
		void Log(Level Level, TARGS&&... Args)const {
			switch (Level) {
			case Level::trace:
				m_Logger->trace(std::forward<TARGS>(Args)...);
				break;
			case Level::debug:
				m_Logger->debug(std::forward<TARGS>(Args)...);
				break;
			case Level::info:
				m_Logger->info(std::forward<TARGS>(Args)...);
				break;
			case Level::warn:
				m_Logger->warn(std::forward<TARGS>(Args)...);
				break;
			case Level::err:
				m_Logger->error(std::forward<TARGS>(Args)...);
				break;
			case Level::critical:
				m_Logger->critical(std::forward<TARGS>(Args)...);
				System_Logger::FatalCallBack(std::forward<TARGS>(Args)...);
				break;
			}
		}

	private:
		template<typename...TARGS>
		static void FatalCallBack(TARGS&&...args) {
			throw std::runtime_error(fmt::format(std::forward<TARGS>(args)...));
		}

		shared_ptr<spdlog::logger> m_Logger = nullptr;
	};

}// namespace NameSpace_Core::NameSpace_System_Logger