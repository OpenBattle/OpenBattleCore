#ifndef _MESSAGE
#define _MESSAGE

#include "global.h"
#include "Serializer.h"

namespace OpenBattle {
	class OPENBATTLECORESHARED_EXPORT Message {
	public:
		virtual unsigned char version() {
			return 1;
		}
		virtual unsigned char type() = 0;
		virtual bool deserialize(Serializer*) = 0;
		virtual unsigned char length(Serializer *serializer) {
			return 0;
		}
		void serialize(Serializer* serializer, Stream* stream) {
			serializer->write(this->version(), stream);
			serializer->write(this->type(), stream);
			serializer->write(this->length(serializer), stream);
		}
		virtual void dispose() = 0;
	};

	class OPENBATTLECORESHARED_EXPORT MessageFactory {
	public:
		virtual unsigned char type() = 0;
		virtual Message *get(unsigned char ver) = 0;
	};

	class OPENBATTLECORESHARED_EXPORT MessageFactoryCollection {
		unsigned char len;
		unsigned char cap;
		MessageFactory **factories;
	public:
		MessageFactoryCollection(unsigned char size = 32);
		void add(MessageFactory *factory);
		Message *get(unsigned char type, unsigned char ver);
	};

	class OPENBATTLECORESHARED_EXPORT MessageHandler {
	public:
		virtual unsigned char type() = 0;
		virtual void invoke(Message *msg) = 0;
	};

	class OPENBATTLECORESHARED_EXPORT MessageHandlerCollection {
		unsigned char len;
		unsigned char cap;
		MessageHandler **handlers;
	public:
		MessageHandlerCollection(unsigned char size = 16);
		void add(MessageHandler *handler);
		void handle(Message *msg);
	};
}

#endif
