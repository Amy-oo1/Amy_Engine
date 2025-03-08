#include "file/File_System.h"

#include<cassert>

namespace NameSpace_Platform::NameSpace_File {

	bool File_System::Is_Directory(const path& Directory) {
		return std::filesystem::is_directory(Directory);
	}

	bool File_System::Is_File(const path& File) {
		return std::filesystem::is_regular_file(File);
	}

	const vector<path> File_System::Get_Sub_Files(const path& Directory) {
		assert(Is_Directory(Directory));

		vector<path> Files{};

		for (const auto& Entry : std::filesystem::directory_iterator{ Directory })
			if (File_System::Is_File(Entry))
				Files.push_back(Entry.path());

		return Files;
	}

	const vector<path> File_System::Get_Sub_Directories(const path& Directory) {
		assert(Is_Directory(Directory));
		vector<path> Directories{};

		for (const auto& Entry : std::filesystem::directory_iterator{ Directory })
			if (File_System::Is_Directory(Entry))
				Directories.push_back(Entry.path());

		return Directories;
	}

	const tuple<optional<string>, optional<string>, optional<string>> File_System::Extensions(const path& Path) {
		return {
			Path.extension().empty() ? nullopt : optional{ Path.extension().generic_string()},
			Path.stem().extension().empty() ? nullopt : optional{ Path.stem().extension().generic_string()},
			Path.stem().stem().extension().empty() ? nullopt : optional{ Path.stem().stem().extension().generic_string()}
		};
	}

	const tuple<optional<string>, optional<string>> File_System::Split_Path(const path& Path) {
		return {
			Path.stem().empty() ? nullopt : optional{Path.stem().string()},
			Path.extension().empty() ? nullopt : optional{Path.extension().string()}
		};
	}

	const path File_System::Generate_Relative_Path(const path& Directory, const path& Temp_Path) {
		return Temp_Path.lexically_relative(Directory);
	}

	const vector<string> File_System::Path_Sgements(const path& Path) {
		vector<string> Segments{};

		for (const auto& Segment : Path)
			Segments.push_back(Segment.generic_string());

		return Segments;
	}

}// namespace NameSpace_Platform::NameSpace_File