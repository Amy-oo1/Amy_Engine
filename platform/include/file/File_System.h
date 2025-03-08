#pragma once

#include<tuple>
#include<vector>
#include<string>
#include<optional>
#include<filesystem>

namespace NameSpace_Platform::NameSpace_File {

	using std::filesystem::path;
	using std::tuple;
	using std::vector;
	using std::string;
	using std::optional;
	using std::nullopt;

	class File_System final {
	private:
		File_System(void) = delete;

		File_System(const File_System&) = delete;
		File_System(File_System&&) = delete;

		File_System& operator=(const File_System&) = delete;
		File_System& operator=(File_System&&) = delete;

		~File_System(void) = delete;
	public:

		static  bool Is_Directory(const path& Directory);
		static  bool Is_File(const path& File);
		static const vector<path> Get_Sub_Files(const path& Directory);
		static const vector<path> Get_Sub_Directories(const path& Directory);
		static const tuple<optional<string>, optional<string>, optional<string>> Extensions(const path& Path);
		static const tuple<optional<string>, optional<string>> Split_Path(const path& Path);
		static const path Generate_Relative_Path(const path& Directory, const path& Temp_Path);
		static const vector<string> Path_Sgements(const path& Path);

	};

}// namespace NameSpace_Platform::NameSpace_File