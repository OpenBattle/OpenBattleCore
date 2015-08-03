#ifndef _SERIALIZER
#define _SERIALIZER

#include "global.h"

namespace OpenBattle {
	class OPENBATTLECORESHARED_EXPORT Stream {
	public:
		//virtual void write(unsigned char *, unsigned char) = 0;
		virtual void writeByte(unsigned char c) = 0;
	};

	class OPENBATTLECORESHARED_EXPORT Serializer;

	class OPENBATTLECORESHARED_EXPORT ISerializable {
	public:
		virtual void serialize(Serializer*, Stream*) = 0;
		virtual bool deserialize(Serializer*) = 0;
		virtual unsigned char length(Serializer*) = 0;
	};

	class OPENBATTLECORESHARED_EXPORT Serializer {
		unsigned char *data;
		unsigned short cap ;
		unsigned short len;
		bool read(int len, unsigned char *out);
	public:
		Serializer(unsigned char cap = 16);
		~Serializer();
		void append(unsigned char c);
		void append(unsigned char *data, unsigned short len);
		void append(const char data[], unsigned char len);
		bool readBytes(unsigned char *out, unsigned char len);
		bool read(unsigned char *out);
		bool read(unsigned long *out);
		bool read(unsigned short *out);
		bool read(float *out);
		bool read(char **out);

		void write(unsigned char val, Stream *stream);
		void write(unsigned short val, Stream *stream);
		void write(unsigned int val, Stream *stream);
		void write(unsigned long val, Stream *stream);
		void write(float val, Stream *stream);
		void write(const char* val, Stream *stream);
		void write(ISerializable*, unsigned char count, Stream *stream);

		unsigned char sizeOf(const char *s);
		unsigned char sizeOf(ISerializable*obj);
	};
}

#endif
