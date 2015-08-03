#ifndef _PROTOCOL
#define _PROTOCOL

#include "Serializer.h"
#include "Message.h"

namespace OpenBattle {
	class Channel {
		MessageFactoryCollection *factory;
		MessageHandlerCollection *handlers;
		Serializer *serializer;
		unsigned char state;
		unsigned char ver;
		unsigned char type;
		unsigned char len;
		Message *msg;
	public:
		Channel(MessageFactoryCollection *factory, MessageHandlerCollection *handlers, unsigned char cap);
		void consume(unsigned char c);
	};

	class OPENBATTLECORESHARED_EXPORT Protocol {
		MessageFactoryCollection *factory;
		MessageHandlerCollection *handlers;
		Channel **channels;
	public:
		Protocol(unsigned char channels = 1, unsigned char cap = 16);
		void addFactory(MessageFactory *factory);
		void addHandler(MessageHandler *handler);
		void consume(unsigned char c, unsigned char channel = 0);
	};
}
#endif
