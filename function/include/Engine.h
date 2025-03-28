#pragma once

#include<string>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <unordered_set>

namespace NameSpace_Function {

	class Amy_Engine final {
	private:
		Amy_Engine(void) = delete;

		Amy_Engine(const Amy_Engine&) = delete;
		Amy_Engine(Amy_Engine&&) = delete;

		Amy_Engine& operator=(const Amy_Engine&) = delete;
		Amy_Engine& operator=(Amy_Engine&&) = delete;

	public:
		Amy_Engine(const std::vector<std::string>& Arguments);

		~Amy_Engine(void) = default;
	};

}// namespace NameSpace_Function