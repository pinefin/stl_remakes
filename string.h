namespace std {
  class string {
    char *data;
  
public:
    static size_t npos;
  
    string(const char *s) {
      size_t len = strlen(s);
      data = new char[len + 1];
      memcpy(data, s, len);
    }
  
    void operator+=(const char *s) {
      size_t len = strlen(s);
      size_t old_len = strlen(data);
      resize(len + old_len + 1);
      memcpy(data + old_len, s, len);
    }
  
    char *begin() { return data; }
  
    char *end() { return data + strlen(data); }
  
    size_t size() { return strlen(data); }
  
    size_t length() { return this->size(); }
  
    char &at(size_t i) {
      if (i >= size()) {
        char *ret = new char;
        *ret = '\0';
        return *ret;
      }
      return data[i];
    }
  
    int resize(size_t size) {
      char *old = data;
      data = new char[size];
      memcpy(data, old, size);
      size_t oldsz = strlen(old);
      delete[] old;
      return oldsz;
    }
  
    size_t find(const char *s) {
      char *p = strstr(data, s);
      if (p == nullptr) {
        return -1;
      }
      return p - data;
    }
  
    void append(const char *s) { operator+=(s); };
  
    const char *c_str() const { return data; }
  
    operator const char *() const { return data; };
    operator char *() const { return data; };
    char &operator[](size_t i) { return data[i]; }
    void operator=(const char *s) {
      size_t len = strlen(s);
      this->resize(len + 1);
      memcpy(data, s, len);
    }
  };
} // namespace std

size_t std::string::npos = -1;
