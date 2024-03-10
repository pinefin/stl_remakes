#pragma once

#include "./crt_remakes/crt_remakes.h"

#include "initializer_list.h"
#include <stdio.h>

namespace std {

template <typename T> class vector {

	T *_data;
	size_t _size;
	size_t _capacity;

public:
	vector() : _data(nullptr), _size(0), _capacity(0) {}
	vector(initializer_list<T> il) {
		_size = il.size();
		_capacity = _size;
		_data = new T[_capacity];
		size_t i = 0;
		for (auto &e : il) {
			_data[i++] = e;
		}
	}

	T *data() { return _data; }

	T &at(size_t i) { return _data[i]; }

	T &operator[](size_t i) { return _data[i]; }

	void resize(size_t n) {
		if (n >= _capacity) {
			T *new_data = new T[n];
			for (size_t i = 0; i < _size; i++) {
				new_data[i] = _data[i];
			}
			delete[] _data;
			_data = new_data;
			_capacity = n;
		}
		_size = n;
	}
	void push_back(const T& var) {
	    if (_size >= _capacity) {
	        _capacity = _capacity * 2 + 1;
	        T *new_data = new T[_capacity];
	        for (size_t i = 0; i < _size; i++) {
	            new_data[i] = _data[i];
	        }
	        delete[] _data; // This is where the error could occur
	        _data = new_data;
	    }
	    _data[_size++] = var;
	}

	void pop_back() {	_size--; }

	T* begin() { return _data; }
	T* end() { return _data + _size; }
	T* rbegin() { return _data + _size-1; }
	T* rend() { return _data-1; }

	T& front() { return _data[0]; }
	T& back() { return _data[_size - 1]; }

	size_t size() const { return _size; }
	size_t capacity() { return _capacity; }
	size_t max_size() { return _capacity; }

	bool empty() { return _size == 0; }

	void shrink_to_fit() {
		_capacity = _size;
		T *new_data = new T[_capacity];
		for (size_t i = 0; i < _size; i++) {
			new_data[i] = _data[i];
		}
		delete[] _data;
		_data = new_data;
	}

	void assign(size_t n, const T &t) {
		resize(n);
		for (size_t i = 0; i < n; i++) {
			_data[i] = t;
		}
	}

	T* insert(T* pos, const T &t) {
	    size_t i = pos - _data;
	    if (_size == _capacity) {
	        _capacity = _capacity * 2 + 1;
	        T *new_data = new T[_capacity];
	        for (size_t j = 0; j < i; j++) {
	            new_data[j] = _data[j];
	        }
	        new_data[i] = t;
	        for (size_t j = i + 1; j <= _size; j++) {
	            new_data[j] = _data[j - 1];
	        }
	        delete[] _data; // Deallocate old memory
	        _data = new_data;
	    } else {
	        for (size_t j = _size; j > i; j--) {
	            _data[j] = _data[j - 1];
	        }
	        _data[i] = t;
	    }
	    _size++;
	    return _data + i;
	}

	T* insert(T* pos, size_t n, const T &t) {
		size_t i = pos - _data;
		if (_size + n > _capacity) {
			_capacity = _size + n;
			T *new_data = new T[_capacity];
			for (size_t j = 0; j < i; j++) {
				new_data[j] = _data[j];
			}
			for (size_t j = 0; j < n; j++) {
				new_data[i + j] = t;
			}
			for (size_t j = i; j < _size; j++) {
				new_data[j + n] = _data[j];
			}
			delete[] _data; // Deallocate old memory
			_data = new_data;
		} else {
			for (size_t j = _size; j > i; j--) {
				_data[j + n - 1] = _data[j - 1];
			}
			for (size_t j = 0; j < n; j++) {
				_data[i + j] = t;
			}
		}
		_size += n;
		return _data + i;
	}

	T* erase(T* pos) {
		size_t i = pos - _data;
		for (size_t j = i; j < _size - 1; j++) {
			_data[j] = _data[j + 1];
		}
		_size--;
		return _data + i;
	}

	void swap(vector<T> &v) {
		T *tmp_data = _data;
		size_t tmp_size = _size;
		size_t tmp_capacity = _capacity;
		_data = v._data;
		_size = v._size;
		_capacity = v._capacity;
		v._data = tmp_data;
		v._size = tmp_size;
		v._capacity = tmp_capacity;
	}

	void clear() {
		_size = 0;
	}

	T* emplace(T* pos, const T &t) {
		return insert(pos, t);
	}
	T* emplace_back(const T &t) {
		return insert(_data + _size-1, t);
	}
	T* emplace_back() {
		return insert(_data + _size-1, T());
	}

	bool operator=(std::initializer_list<T>& il) {
		_size = il.size();
		_capacity = _size;
		_data = new T[_capacity];
		size_t i = 0;
		for (auto &e : il) {
			_data[i++] = e;
		}
		return true;
	}

	bool operator== (const vector<T> &v) {
		if (_size != v._size) {
			return false;
		}
		for (size_t i = 0; i < _size; i++) {
			if (_data[i] != v._data[i]) {
				return false;
			}
		}
		return true;
	}
	bool operator!= (const vector<T> &v) {
		if (_size != v._size) {
			return true;
		}
		for (size_t i = 0; i < _size; i++) {
			if (_data[i] != v._data[i]) {
				return true;
			}
		}
		return false;
	}

	bool operator>= (const vector<T> &v) {
		if (_size > v._size) {
			return true;
		}
		if (_size < v._size) {
			return false;
		}
		for (size_t i = 0; i < _size; i++) {
			if (_data[i] > v._data[i]) {
				return true;
			}
			if (_data[i] < v._data[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator<= (const vector<T> &v) {
		if (_size < v._size) {
			return true;
		}
		if (_size > v._size) {
			return false;
		}
		for (size_t i = 0; i < _size; i++) {
			if (_data[i] < v._data[i]) {
				return true;
			}
			if (_data[i] > v._data[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator>(const vector<T> &v) {
		if (_size > v._size) {
			return true;
		}
		if (_size < v._size) {
			return false;
		}
		for (size_t i = 0; i < _size; i++) {
			if (_data[i] > v._data[i]) {
				return true;
			}
			if (_data[i] < v._data[i]) {
				return false;
			}
		}
		return false;
	}

	bool operator< (const vector<T> &v) {
		if (_size < v._size) {
			return true;
		}
		if (_size > v._size) {
			return false;
		}
		for (size_t i = 0; i < _size; i++) {
			if (_data[i] < v._data[i]) {
				return true;
			}
			if (_data[i] > v._data[i]) {
				return false;
			}
		}
		return false;
	}
};

} // namespace std
