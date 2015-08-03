#ifndef _ARRAY
#define _ARRAY

#include "Serializer.h"

template <class TYPE> class Array
{
	unsigned char len;
	char cap;
	TYPE** values = 0;
public:
	Array(TYPE** values, unsigned char len) {
		this->len = this->cap = len;
		this->values = new TYPE*[len];
		for (unsigned char i = 0; i < len; i++) {
			this->values[i] = values[i];
		}
	}
	Array(unsigned char) : cap(-1), len(0) { }
	Array() : cap(-1), len(0), values(0) {	}
	TYPE* get(unsigned char index) {
		return this->values[index];
	}
	void set(unsigned char index, TYPE* value) {
		this->values[index] = value;
	}
	unsigned char length() {
		return this->len;
	}
	bool deserialize(OpenBattle::Serializer* serializer) {
		if (this->cap < 0) {
			unsigned char len;
			if (!serializer->read(&len)) {
				return false;
			}
			this->cap = this->len = len;
			this->values = new TYPE*[len];
			for (unsigned char i = 0; i < len; i++) {
				this->values[i] = 0;
			}
		}
		for (unsigned char i = 0; i < this->cap; i++) {
			if (this->values[i] == 0) {
				this->values[i] = new TYPE();
			}
			if (!this->values[i]->deserialize(serializer)) {
				return false;
			}
		}
		return true;
	}
	void serialize(OpenBattle::Serializer* serializer, OpenBattle::Stream* stream) {
		serializer->write(this->len, stream);
		for (unsigned char i = 0; i < this->len; i++) {
			this->values[i]->serialize(serializer, stream);
		}
	}
};

#endif
