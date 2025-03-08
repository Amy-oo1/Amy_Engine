#include "meta/Meta_Info.h"

#include "meta/Meta_Utils.h"

namespace NameSpace_Meta_Parser::NameSpace_Meta {

	Meta_Info::Meta_Info(const Cursor& Temp_Cursor) {
		for (const auto& Temp_Child : Temp_Cursor.Get_Children())
			if (Temp_Child.Get_Cursor_Kind() == Cursor::Cursor_Kind::CURSOR_ANNOTATEATTR)
				for (const auto& [Config, Value] : Meta_Info::Extract_Properties(Temp_Child))
					this->m_Properties[Config] = Value;
	}

	const string Meta_Info::Get_Property(const string& Key) const {
		auto Iter_Target = this->m_Properties.find(Key);

		return (Iter_Target == this->m_Properties.end()) ? string{} : Iter_Target->second;

	}

	const bool Meta_Info::Get_Flag(const string& Key) const {
		return this->m_Properties.find(Key) != this->m_Properties.end();
	}

	const vector<pair<string, string>> Meta_Info::Extract_Properties(const Cursor& Temp_Cursor) {
		vector<pair<string, string>> List;

		for (const auto& Property_Item : NameSpace_Utils::Split(Temp_Cursor.Get_Display_Name(), ',')) {
			vector<string> Item_Details = NameSpace_Utils::Split(Property_Item, ':');

			string Key_Str = NameSpace_Utils::Trim(Item_Details[0]);
			if (!Key_Str.empty())
				List.emplace_back(Key_Str, (Item_Details.size() > 1) ? NameSpace_Utils::Trim(Item_Details[1]) : string{});
		}

		return List;
	}

}// namespace NameSpace_Meta_Parser::NameSpace_Meta