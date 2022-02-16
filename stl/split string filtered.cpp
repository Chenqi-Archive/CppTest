#include <string>
#include <vector>


#pragma warning(push)
#pragma warning(disable : 26800)  // Use of a moved from object
std::vector<std::wstring> split_string_filtered(const std::wstring& str) {
	std::vector<std::wstring> result;
	std::wstring current_line;
	std::wstring::const_iterator begin = str.begin(), end = begin;
	while (end != str.end()) {
		if (iswcntrl(*end)) {
			current_line.append(begin, end);
			begin = end + 1;
			if (*end == L'\r' || *end == L'\n') {
				if (*end == L'\r' && begin != str.end() && *begin == L'\n') { ++begin; }
				result.push_back(std::move(current_line));
			}
			end = begin;
		} else {
			++end;
		}
	}
	result.push_back(std::move(current_line.append(begin, end)));
	return result;
}
#pragma warning(pop)


int main() {
	std::vector<std::wstring> res;
	res = split_string_filtered(L"");  // [""]
	res = split_string_filtered(L"t");  // ["t"]
	res = split_string_filtered(L"\n");  // ["", ""]
	res = split_string_filtered(L"t\n");  // ["t", ""]
	res = split_string_filtered(L"\r\n\r\r\r\n\n\r\n");  // ["", "", "", "", "", "", "", ""]
	res = split_string_filtered(L"face\thi\r\nok\r\r\nget\nt\r\n");  // ["facehi", "ok", "", "get", "t", ""]
	res = split_string_filtered(L"fa😀ce\thi测试\r\nok\r\r\nget\nt");  // ["fa😀cehi测试", "ok", "", "get", "t"]
}
