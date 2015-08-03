#include "Protocol.h"

#define STATE_INITIAL		0
#define STATE_TYPE			4
#define STATE_LEN			1
#define STATE_DESERIALIZE	2
#define STATE_SKIP			3

#define MSG_GAME_DATA 1

namespace OpenBattle {
	Channel::Channel(MessageFactoryCollection *factory, MessageHandlerCollection *handlers, unsigned char cap) {
		this->factory = factory;
		this->handlers = handlers;
		this->state = STATE_INITIAL;
		this->ver = 0;
		this->type = 0;
		this->len = 0;
		this->msg = 0;
		this->serializer = new Serializer(cap);
	}

	void Channel::consume(unsigned char c)
	{
		switch (this->state)
		{
		case STATE_INITIAL:
		initial:
			this->ver = c;
			this->state = STATE_TYPE;
			break;
		case STATE_TYPE:
			this->type = c;
			this->state = STATE_LEN;
			break;
		case STATE_LEN:
			this->len = c;
			this->msg = factory->get(this->type, this->ver);
			this->state = STATE_DESERIALIZE;
			if (this->len == 0) {
				goto handler;
			}
			break;
		case STATE_DESERIALIZE:
			if (this->msg == 0) {
				this->state = STATE_SKIP;
				goto skip;
			}
			this->serializer->append(c);
			if (!this->msg->deserialize(this->serializer)) {
				break;
			}
		handler:
			this->handlers->handle(this->msg);
			if (this->msg != 0) {
				this->msg->dispose();
				delete this->msg;
				this->msg = 0;
			}
			this->len = 0;
			this->type = 0;
			this->state = STATE_INITIAL;
			break;
		case STATE_SKIP:
		skip :
			if (this->len == 0) {
				goto initial;
			}
			 this->len--;
			 break;
		}
	}

	Protocol::Protocol(unsigned char channels, unsigned char cap)
	{
		this->factory = new MessageFactoryCollection();
		this->handlers = new MessageHandlerCollection();
		this->channels = new Channel*[channels];
		for (int i = 0; i < channels; i++) {
			this->channels[i] = new Channel(this->factory, this->handlers, cap);
		}
	}

	void Protocol::consume(unsigned char c, unsigned char channel) {
		this->channels[channel]->consume(c);
	}

	void Protocol::addFactory(MessageFactory *factory)
	{
		this->factory->add(factory);
	}

	void Protocol::addHandler(MessageHandler *handler) {
		this->handlers->add(handler);
	}

	MessageFactoryCollection::MessageFactoryCollection(unsigned char size)
	{
		this->len = 0;
		this->cap = size;
		this->factories = new MessageFactory*[size];
	}

	void MessageFactoryCollection::add(MessageFactory *factory)
	{
		this->factories[this->len++] = factory;
	}

	Message *MessageFactoryCollection::get(unsigned char type, unsigned char ver)
	{
		for (int i = 0; i < this->len; i++) {
			MessageFactory *factory = this->factories[i];
			if (factory->type() == type) {
				return factory->get(ver);
			}
		}
		return 0;
	}

	MessageHandlerCollection::MessageHandlerCollection(unsigned char size)
	{
		this->len = 0;
		this->cap = size;
		this->handlers = new MessageHandler*[size];
	}

	void MessageHandlerCollection::add(MessageHandler *handler)
	{
		this->handlers[this->len++] = handler;
	}

	void MessageHandlerCollection::handle(Message *msg)
	{
		for (int i = 0; i < this->len; i++) {
			MessageHandler *handler = this->handlers[i];
			if (handler->type() == msg->type()) {
				handler->invoke(msg);
			}
		}
	}
}
