#pragma once

#include "./crt_remakes/crt_remakes.h"

namespace std {
	class string {
	char *_data;

	public:
	static size_t npos;

	string() {
		_data = new char[1];
		_data[0] = '\0';
	}
	string(const char *s) {
		size_t len = strlen(s);
		_data = new char[len + 1];
		memcpy(_data, s, len);
	}
	string(const string &s) {
		size_t len = strlen(s._data);
		_data = new char[len + 1];
		memcpy(_data, s._data, len);
	}
	~string() { delete[] _data; }

	void operator+=(const char *s) {
		size_t len = strlen(s);
		size_t old_len = strlen(_data);
		resize(len + old_len + 1);
		memcpy(_data + old_len, s, len);
	}

	char *begin() { return _data; }
	char *rbegin() { return _data + strlen(_data) - 1; }
	char *end() { return _data + strlen(_data); }
	char *rend() { return _data - 1; }

	size_t size() { return strlen(_data); }

	size_t length() { return this->size(); }

	char &at(size_t i) {
		if (i >= size()) {
			char *ret = new char;
			*ret = '\0';
			return *ret;
		}
		return _data[i];
	}

	char &back() { return _data[strlen(_data) - 1]; }

	char &front() { return _data[0]; }

	void clear() {
		delete[] _data;
		_data = new char[1];
		_data[0] = '\0';
	}

	void erase(size_t pos, size_t len) {
		size_t old_len = strlen(_data);
		if (pos + len > old_len) {
			len = old_len - pos;
		}
		memmove(_data + pos, _data + pos + len, old_len - pos - len + 1);
	}

	int resize(size_t size) {
		char *old = _data;
		_data = new char[size];
		memcpy(_data, old, size);
		size_t oldsz = strlen(old);
		delete[] old;
		return oldsz;
	}

	size_t find(const char *s) {
		char *p = strstr(_data, s);
		if (p == nullptr) {
			return -1;
		}
		return p - _data;
	}

	void append(const char *s) { operator+=(s); };
	void push_back(char c) {
		size_t old_len = strlen(_data);
		resize(old_len + 2);
		_data[old_len] = c;
		_data[old_len + 1] = '\0';
	}

	void insert(size_t pos, const char *s) {
		size_t old_len = strlen(_data);
		size_t len = strlen(s);
		resize(old_len + len + 1);
		memmove(_data + pos + len, _data + pos, old_len - pos + 1);
		memcpy(_data + pos, s, len);
	}

	void replace(size_t pos, size_t len, const char *s) {
		erase(pos, len);
		insert(pos, s);
	}

	void swap(string &other) {
		char *tmp = _data;
		_data = other._data;
		other._data = tmp;
	}

	void pop_back() {
		size_t old_len = strlen(_data);
		if (old_len == 0) {
			return;
		}
		resize(old_len - 1);
	}

	char *data() { return _data; }
	char *data() const { return _data; }
	size_t copy(char *dest, size_t len, size_t pos = 0) {
		size_t old_len = strlen(_data);
		if (pos >= old_len) {
			return 0;
		}
		if (pos + len > old_len) {
			len = old_len - pos;
		}
		memcpy(dest, _data + pos, len);
		return len;
	}

	int compare(std::string s) { return strcmp(_data, s.data()); }

	size_t rfind(std::string s) {
		char *p = strstr(_data, s.data());
		if (p == nullptr) {
			return -1;
		}
		return p - _data;
	}

	size_t find_first_of(const char *s) {
		for (size_t i = 0; i < strlen(_data); i++) {
			for (size_t j = 0; j < strlen(s); j++) {
				if (_data[i] == s[j]) { return i; }
			}
		}
		return -1;
	}

	size_t find_last_of(const char *s) {
		for (size_t i = strlen(_data) - 1; i >= 0; i--) {
			for (size_t j = 0; j < strlen(s); j++) {
				if (_data[i] == s[j]) { return i; }
			}
		}
		return -1;
	}

	size_t find_first_not_of(const char *s) {
		for (size_t i = 0; i < strlen(_data); i++) {
			bool found = false;
			for (size_t j = 0; j < strlen(s); j++) {
				if (_data[i] == s[j]) {
					found = true;
					break;
				}
			}
			if (!found) {
				return i;
			}
		}
		return -1;
	}

	string substr(size_t pos, size_t len) {
		size_t old_len = strlen(_data);
		if (pos >= old_len) {
			return "";
		}

		if (pos + len > old_len) {
			len = old_len - pos;
		}

		char *ret = new char[len + 1];
		memcpy(ret, _data + pos, len);
		ret[len] = '\0';
		return ret;
	}

	const char *c_str() const { return _data; }

	operator const char *() const { return _data; };
	operator char *() const { return _data; };
	char &operator[](size_t i) { return _data[i]; }
	void operator=(const char *s) {
		size_t len = strlen(s);
		this->resize(len + 1);
		memcpy(_data, s, len);
	}
	void operator=(const string &s) {
		size_t len = strlen(s._data);
		this->resize(len + 1);
		memcpy(_data, s._data, len);
	}

	// boolean operators for string
	bool operator==(const string s) { return strcmp(_data, s._data) == 0; }
	bool operator!=(const string s) { return strcmp(_data, s._data) != 0; }
	bool operator<(const string s) { return strcmp(_data, s._data) < 0; }
	bool operator>(const string s) { return strcmp(_data, s._data) > 0; }
	bool operator<=(const string s) { return strcmp(_data, s._data) <= 0; }
	bool operator>=(const string s) { return strcmp(_data, s._data) >= 0; }
	bool operator==(const string &s) const { return strcmp(_data, s._data) == 0; }
	bool operator!=(const string &s) const { return strcmp(_data, s._data) != 0; }
	bool operator<(const string &s) const { return strcmp(_data, s._data) < 0; }
	bool operator>(const string &s) const { return strcmp(_data, s._data) > 0; }
	bool operator<=(const string &s) const { return strcmp(_data, s._data) <= 0; }
	bool operator>=(const string &s) const { return strcmp(_data, s._data) >= 0; }

	// boolean operators for char*
	bool operator==(const char *s) { return strcmp(_data, s) == 0; }
	bool operator!=(const char *s) { return strcmp(_data, s) != 0; }
	bool operator<(const char *s) { return strcmp(_data, s) < 0; }
	bool operator>(const char *s) { return strcmp(_data, s) > 0; }
	bool operator<=(const char *s) { return strcmp(_data, s) <= 0; }
	bool operator>=(const char *s) { return strcmp(_data, s) >= 0; }
	bool operator==(const char *s) const { return strcmp(_data, s) == 0; }
	bool operator!=(const char *s) const { return strcmp(_data, s) != 0; }
	bool operator<(const char *s) const { return strcmp(_data, s) < 0; }
	bool operator>(const char *s) const { return strcmp(_data, s) > 0; }
	bool operator<=(const char *s) const { return strcmp(_data, s) <= 0; }
	bool operator>=(const char *s) const { return strcmp(_data, s) >= 0; }
	}; // namespace std
} // namespace std

size_t std::string::npos = -1;
