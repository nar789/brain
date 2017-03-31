#include <stdio.h>
#include <stdlib.h>
#include "brain.h"
#include<iostream>

using namespace std;

int wmain(int argc,wchar_t* argv[]) {
	if (argc < 1 || argv[1]==NULL) {
		printf("brain v1.0.0\t");
		printf("brain [text]\n");
		return 0;
	}
	_wsetlocale(LC_ALL, L"korean");
	wchar_t cmd[255];
	wcscpy(cmd, argv[1]);
	if (argc > 2) {
		for (int i = 2; i < argc; i++) {
			wcscat(cmd, L" ");
			wcscat(cmd, argv[i]);
		}
	}
	wprintf(L"%s\n",cmd);
	brain b;
	b.Load();
	
	b.Input(cmd);
	b.Run();
	return 0;
}