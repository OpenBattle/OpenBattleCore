#include "Serializer.h"

namespace OpenBattle {
	Serializer::Serializer(unsigned char cap)
	{
		this->cap = cap;
		this->len = 0;
		this->data = new unsigned char[this->cap];
	}

	Serializer::~Serializer() {
		//delete[] this->data;
	}

	void Serializer::append(unsigned char c)
	{
		if (this->len == this->cap) {
			unsigned char *buf = new unsigned char[this->cap * 2];
			for (int i = 0; i < this->cap; i++) {
				buf[i] = this->data[i];
			}
			delete[] this->data;
			this->data = buf;
			this->cap *= 2;
		}
		this->data[this->len++] = c;
	}

	void Serializer::append(unsigned char *data, unsigned short len)
	{
		for (unsigned short i = 0; i < len; i++) {
			this->append(data[i]);
		}
	}

	void Serializer::append(const char data[], unsigned char len)
	{
		for (unsigned char i = 0; i < len; i++) {
			this->append(data[i]);
		}
	}

	bool Serializer::read(int len, unsigned char *out) {
		if (this->len < len) {
			return false;
		}
		for (int i = 0; i < len; i++) {
			out[i] = this->data[i];
		}
		if (len < this->len) {
			for (int i = 0; i < this->len - len; i++) {
				this->data[i] = this->data[i + len];
			}
			this->len -= len;
		}
		else {
			this->len = 0;
		}
		return true;
	}

	bool Serializer::read(float *out) {
		return false;
	}

	bool Serializer::read(unsigned char *out) {
		return this->read(1, out);
	}

	bool Serializer::read(unsigned short *out)
	{
		return this->read(2, (unsigned char*)out);
	}

	bool Serializer::read(unsigned long *out) {
		return this->read(4, (unsigned char*)out);
	}

	bool Serializer::read(char **out) {
		if (this->len < 1 || this->len < this->data[0] + 1) {
			return false;
		}
		unsigned char len;
		this->read(&len);
		if (len == 0) {
			(*out) = 0;
			return true;
		}
		(*out) = new char[len + 1];
		this->readBytes((unsigned char*)*out, len);
		(*out)[len] = 0;
		return true;
	}

	bool Serializer::readBytes(unsigned char *out, unsigned char len) {
		if (this->len < len) {
			return false;
		}
		this->read(len, out);
		return true;
	}

	void Serializer::write(float val, Stream *stream) {
	}

	void Serializer::write(unsigned char val, Stream *stream) {
		stream->writeByte(val);
	}

	void Serializer::write(unsigned short val, Stream *stream) {
		for (unsigned char i = 0; i < sizeof(val); i++) {
			stream->writeByte(((unsigned char *)&val)[i]);
		}
	}

	void Serializer::write(unsigned int val, Stream *stream) {
		for (unsigned char i = 0; i < sizeof(val); i++) {
			stream->writeByte(((unsigned char *)&val)[i]);
		}
	}

	void Serializer::write(unsigned long val, Stream *stream) {
		for (unsigned char i = 0; i < sizeof(val); i++) {
			stream->writeByte(((unsigned char *)&val)[i]);
		}
	}

	void Serializer::write(const char *val, Stream *stream) {
		if (val == 0) {
			stream->writeByte(0);
			return;
		}
		unsigned char len = this->sizeOf(val) - 1;
		stream->writeByte(len);
		for (unsigned char i = 0; i < len; i++) {
			stream->writeByte(val[i]);
		}
	}

	void Serializer::write(ISerializable *items, unsigned char count, Stream *stream) {
		stream->writeByte(count);
		for (unsigned char i = 0; i < count; i++) {
			items[0].serialize(this, stream);
		}
	}

	unsigned char Serializer::sizeOf(const char *s) {
		for (unsigned char i = 0;; i++) {
			if (s[i] == 0) {
				return i + 1;
			}
		}
	}

	unsigned char Serializer::sizeOf(ISerializable* obj) {
		return obj->length(this);
	}
}
