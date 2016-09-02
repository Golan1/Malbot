#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <fstream>
#include <conio.h>

#include "Wave.h"

Wave::Wave(char * filename)
{
	ok = false;
	buffer = 0;
	HInstance = GetModuleHandle(0);

	std::ifstream infile(filename, std::ios::binary);

	if (!infile)
	{
		std::cout << "Wave::file error: " << filename << std::endl;
		return;
	}

	infile.seekg(0, std::ios::end);   // get length of file
	int length = infile.tellg();
	buffer = new char[length];    // allocate memory
	infile.seekg(0, std::ios::beg);   // position to start of file
	infile.read(buffer, length);  // read entire file

	infile.close();
	ok = true;
}

Wave::~Wave()
{
	PlaySound(NULL, 0, 0); // STOP ANY PLAYING SOUND
	delete[] buffer;      // before deleting buffer.
}
void Wave::play(bool async)
{
	if (!ok)
		return;

	if (async)
		PlaySound(buffer, HInstance, SND_MEMORY | SND_ASYNC);
	else
		PlaySound(buffer, HInstance, SND_MEMORY);
}

bool Wave::isok()
{
	return ok;
}