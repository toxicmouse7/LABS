#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

//bool IsDirectoryEqualToOld(vector<pair<wstring, DWORD>> filenames, vector<pair<wstring, DWORD>> new_filenames)
//{
//	if (filenames.size() != new_filenames.size())
//		return false;
//	else for (int i = 0; i < filenames.size(); i++)
//	{
//		if (filenames[i] != new_filenames[i])
//			return false;
//	}
//
//	return true;
//}
//
//void WhatChanged(vector<pair<wstring, DWORD>> filenames, vector<pair<wstring, DWORD>> new_filenames)
//{
//	if (IsDirectoryEqualToOld(filenames, new_filenames) == true)
//		return;
//	else
//	{
//		if (filenames.size() < new_filenames.size())
//		{
//			filenames[filenames.size()-1].second
//		}
//	}
//}

int main(int argc, char* argv[])
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	SYSTEMTIME sys_time;
	vector<pair<wstring, DWORD>> filenames, new_filenames;

	hf = FindFirstFileW(L"*", &FindFileData);

	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			wcout << FindFileData.cFileName << endl;
			new_filenames.push_back(make_pair((wstring)FindFileData.cFileName, FindFileData.ftCreationTime.dwHighDateTime));
		} while (FindNextFileW(hf, &FindFileData) != 0);
		FindClose(hf);
	}

	while (true)
	{
		int i = 0;
		hf = FindFirstFileW(L"*", &FindFileData);

		if (hf != INVALID_HANDLE_VALUE)
		{
			do
			{
				
				
			} while (FindNextFileW(hf, &FindFileData) != 0);
			FindClose(hf);
		}

		/*if (filenames.size() == 0)
		{
			filenames = new_filenames;
			new_filenames.clear();
			continue;
		}
		else
		{

		}*/
		Sleep(3000);
	}


	return 0;
}