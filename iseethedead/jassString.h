#pragma once
struct CJassStringData {
	unsigned int vtable;
	unsigned int refCount;
	unsigned int dwUnk1;
	unsigned int pUnk2;
	unsigned int pUnk3;
	unsigned int pUnk4;
	unsigned int pUnk5;
	char* data;
};

struct CJassString {
	unsigned int vtable;
	unsigned int dw0;
	CJassStringData* data;
	unsigned int dw1;
};

class jassString {
private:
	CJassString* str;
	size_t len;
public:
	jassString(const char* buff);
	~jassString();
	bool ChangeStr(char* buff);
	CJassString* GetJassStr();
	char* GetCStr();
};