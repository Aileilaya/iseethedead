#include "pch.h"
#include "jassString.h"
jassString::jassString(const char* buff) {
	len = strlen(buff);
	str = new CJassString;
	str->data = new CJassStringData;
	str->data->data = new char[len + 1];
	memcpy(str->data->data, buff, len);
	str->data->data[len] = 0;
}
jassString::~jassString() {
	delete[] str->data->data;
	delete str->data;
	delete str;
}
bool jassString::ChangeStr(char* buff) {
	if (!buff) return false;
	bool ret = false;
	size_t buff_len = strlen(buff);
	if (this->len < buff_len) {
		delete[] str->data->data;
		str->data->data = new char[buff_len + 1];
		this->len = buff_len;
		ret = true;
	}
	memcpy(str->data->data, buff, buff_len);
	str->data->data[buff_len] = 0;
	return ret;
}
CJassString* jassString::GetJassStr() {
	return this->str;
}

char* jassString::GetCStr() {
	return this->str->data->data;
}