#ifndef _INFRAREDRXTX
#define _INFRAREDRXTX

#include <IRremote.h>
#include <IRremoteInt.h>

#define IR_SIGNAL_LEN 600
#define BUFLEN 97

class InfraredRxTx {
	IRsend sender;
	IRrecv *recv;
	decode_results results;
	unsigned char buffer[16];
	unsigned char bufLen = 0;

	unsigned int sendBuf[BUFLEN] = { IR_SIGNAL_LEN * 3 };

public:
	void begin(unsigned char rx, unsigned char khz = 38) {
		//this->sender = new IRsend();
		this->sender.enableIROut(khz);

		this->recv = new IRrecv(rx);
		this->recv->enableIRIn();
	}
	void write(unsigned char *data, unsigned char len) {
		for (unsigned int i = 0; i < len; i += BUFLEN / 8) {
			if (i > 0) {
				delay(250);
			}
			unsigned char k = 0;
			for (; k < BUFLEN / 8 && k + i < len; k++) {
				for (unsigned char j = 0; j < 8; j++) {
					sendBuf[k * 8 + j + 1] = (data[i + k] >> (7 - j)) & 1 ? IR_SIGNAL_LEN * 2 : IR_SIGNAL_LEN;
				}
			}
			Serial.println(k * 8 + 1);
			this->sender.sendRaw(sendBuf, k * 8 + 1, 40);
		}
	}
	int available() {
		if (this->bufLen == 0 && this->recv->decode(&this->results)) {
			for (unsigned char i = 2; i < this->results.rawlen; i += 8) {
				unsigned char res = 0;
				for (unsigned char j = 0; j < 8; j++) {
					res <<= 1;
					if (this->results.rawbuf[i + j] * 50 >= IR_SIGNAL_LEN * 1.5) {
						res |= 1;
					}
				}
				this->buffer[this->bufLen++] = res;
				Serial.print(String(res, 16) + " ");
			}
			Serial.println();

			this->recv->resume();
		}
		return this->bufLen;
	}
	int read() {
		if (this->bufLen == 0) {
			return -1;
		}
		unsigned char ret = this->buffer[0];
		for (unsigned char i = 1; i < this->bufLen; i++) {
			this->buffer[i - 1] = this->buffer[i];
		}
		this->bufLen--;
		return ret;
	}
};

#endif
