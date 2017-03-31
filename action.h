#pragma once

#include <map>
#include <string>

using namespace std;

class action {
public:
	std::map<wstring, int> s;
	int N;
	wchar_t cmd[255];
	action() {
		N = 0;
	}
	void setcmd(wchar_t* c) {
		wcscpy(cmd, c);
	}
	void add(wchar_t* key) {
		if (s.find(key) == s.end())
			s.insert(make_pair(key, 1));
		else
			s[key]=s[key]+1;

		N++;
	}
	void Run() {
		//wprintf(L"%s",cmd);
		//_wexecl(cmd,L"");
		_wsystem(cmd);
	}
};