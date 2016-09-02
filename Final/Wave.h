#pragma once


class Wave {

public:
	Wave(char * filename);
	~Wave();
	void play(bool async = true);
	bool isok();

private:
	char * buffer;
	bool ok;
	HINSTANCE HInstance;
};