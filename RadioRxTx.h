#ifndef _RADIORXTX
#define _RADIORXTX

#include <VirtualWire.h>

class RadioRxTx {
	uint8_t buf[VW_MAX_MESSAGE_LEN];
	uint8_t buflen = 0;
	uint8_t bufpos = 0;
public:
	RadioRxTx() {
	}
	void begin(uint8_t rx, uint8_t tx, uint8_t enable = 10) {
		// Initialise the IO and ISR
		vw_set_tx_pin(tx);
		vw_set_rx_pin(rx);
		vw_set_ptt_pin(enable);
		vw_set_ptt_inverted(true); // Required for DR3100
		vw_setup(2000);	 // Bits per sec
	}
	void write(unsigned char *msg, unsigned char len) {
		vw_send((uint8_t*)msg, len);
		vw_wait_tx(); // Wait until the whole message is gone
	}
	void startRx() {
		vw_rx_start();       // Start the receiver PLL running
	}
	uint8_t available() {
		if (this->bufpos < this->buflen) {
			return this->size();
		}
		uint8_t len = VW_MAX_MESSAGE_LEN;
		// Non-blocking
		if (vw_get_message(this->buf, &len)) {
			this->bufpos = 0;
			this->buflen = len;
			return this->buflen;
		}
		return 0;
	}
	uint8_t size() {
		return this->buflen - this->bufpos;
	}
	int read() {
		if (this->size() == 0) {
			return -1;
		}
		return this->buf[this->bufpos++];
	}
};

#endif