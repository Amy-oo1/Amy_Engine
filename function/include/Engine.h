#pragma once

#include<string>
#include <atomic>
#include <chrono>
#include <filesystem>
#include <unordered_set>
#include<memory>

namespace NameSpace_Function {

	using std::string;
	using std::vector;
	using std::unordered_set;
	using std::shared_ptr;

	class Amy_Engine final {
	private:
		Amy_Engine(void) = delete;

		Amy_Engine(const Amy_Engine&) = delete;
		Amy_Engine(Amy_Engine&&) = delete;

		Amy_Engine& operator=(const Amy_Engine&) = delete;
		Amy_Engine& operator=(Amy_Engine&&) = delete;

	public:
		Amy_Engine(const std::vector<string>& Arguments);

		~Amy_Engine(void) = default;
	};

}// namespace NameSpace_Function