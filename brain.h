#pragma once

#include <stdio.h>
#include <vector>
#include "action.h"
#include <wchar.h>

#define COUNT 5 //Count of Wk's samples.
#define W wchar_t

using namespace std;

class brain {
public :
	vector<action> v;
	vector<W*> word;

	void Input(W* cmd) {
		W* pch = wcstok(cmd, L" .\t");
		while (pch != NULL) {
			word.push_back(pch);
			pch = wcstok(NULL, L" .");
		}
	}

	void Load() {
		FILE *in = fopen("load.txt", "r");
		if (in) {
			W cmd[255];
			
			while (fgetws(cmd,255,in)!=NULL) {
				cmd[wcslen(cmd) - 1] = 0;
				action s;
				s.setcmd(cmd);
				for (int i = 0; i < COUNT; i++)
				{
					W sample[255];
					fgetws(sample, 255, in);
					sample[wcslen(sample)-1] = 0;
					W* pch;
					pch = wcstok(sample, L" .\t");
					while (pch != NULL) {
						s.add(pch);
						pch = wcstok(NULL, L" .");
					}
				}
				v.push_back(s);
			}
			fclose(in);
		}
	}
	double getcoststr(const W* a,const W* b)
	{
		double ret = 0;
		int dist = (wcslen(a) < wcslen(b)) ? (wcslen(a)) : (wcslen(b));
		for (int i = 0; i < dist; i++) {
			ret += abs(a[i] - b[i])*(wcslen(b)-i);
		}
		return ret/(double)dist;
	}
	void Run() {
		
		double maxP = -10.0f;
		vector<action>::iterator it;
		for (auto i = v.begin(); i != v.end();++i) {
			double P = -10.0f;
			for (W* a : word) {
				int cnt = 0;
				if (i->s.count(a))
					cnt = i->s[a];
				if (cnt > 0)
				{
					if(P<=-10.0f)
						P = log((double)(cnt) / (double)(i->N));
					else
						P += log((double)(cnt) / (double)(i->N));
				}
			}
			printf("%lf\n",P);
			if (maxP < P) {
				it = i;
				maxP = P;
			}
		}
		if (maxP > -10.0f)
			it->Run();
		else {
			printf("Didn't find.\n");
			vector<action>::iterator it;
			double mink = 0x7fffffff;
			for (auto i = v.begin(); i != v.end(); ++i) {
				for (W* a : word) {
					for (auto k = i->s.begin(); k != i->s.end(); ++k) {
						double cost = getcoststr(k->first.c_str(), a);
						if (mink > cost)
						{
							mink = cost;
							it = i;
						}
						wprintf(L"%s %lf\n", k->first.c_str(), cost);
					}
				}
			}
			if(v.size()>0)
				it->Run();
		}
	}

};