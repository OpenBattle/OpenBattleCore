#ifndef _GENERATED
#define _GENERATED

#include "OpenBattleCore.h"

namespace OpenBattle {
	class BaseInfo : public ISerializable {
	public:
		BaseInfo() : id(0), type(0), state(0) {}
		BaseInfo(short id, char type, char state) : id(id), type(type), state(state) {}
		unsigned short id = 0;
		unsigned char type = 0;
		unsigned char state = 0;

		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->id;
			len += sizeof this->type;
			len += sizeof this->state;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->id == 0 && !serializer->read(&this->id)) {
				return false;
			}
			if (this->type == 0 && !serializer->read(&this->type)) {
				return false;
			}
			if (this->state == 0 && !serializer->read(&this->state)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			serializer->write(this->id, stream);
			serializer->write(this->type, stream);
			serializer->write(this->state, stream);
		}
		void dispose() {
		}
	};

	class TeamInfo : public ISerializable {
	public:
		TeamInfo() : id(0), name(0) {}
		TeamInfo(short id, char* name) : id(id), name(name) {}
		unsigned short id = 0;
		char* name = 0;

		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->id;
			len += serializer->sizeOf(this->name);
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->id == 0 && !serializer->read(&this->id)) {
				return false;
			}
			if (this->name == 0 && !serializer->read(&this->name)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			serializer->write(this->id, stream);
			serializer->write(this->name, stream);
		}
		void dispose() {
			if (this->name != 0) {
				delete this->name;
				this->name = 0;
			}
		}
	};

	class PlayerInfo : public ISerializable {
	public:
		PlayerInfo() : id(0), teamId(0), name(0) {}
		PlayerInfo(short id, short teamId, char* name) : id(id), teamId(teamId), name(name) {}
		unsigned short id = 0;
		unsigned short teamId = 0;
		char* name = 0;

		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->id;
			len += sizeof this->teamId;
			len += serializer->sizeOf(this->name);
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->id == 0 && !serializer->read(&this->id)) {
				return false;
			}
			if (this->teamId == 0 && !serializer->read(&this->teamId)) {
				return false;
			}
			if (this->name == 0 && !serializer->read(&this->name)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			serializer->write(this->id, stream);
			serializer->write(this->teamId, stream);
			serializer->write(this->name, stream);
		}
		void dispose() {
			if (this->name != 0) {
				delete this->name;
				this->name = 0;
			}
		}
	};

	class Rules : public ISerializable {
	public:
		Rules() : magazine(0), ammo(0), totalAmmo(0), fireRate(0), reloadRate(0), reloadMode(0) {}
		Rules(short magazine, short ammo, short totalAmmo, float fireRate, float reloadRate, char reloadMode) : magazine(magazine), ammo(ammo), totalAmmo(totalAmmo), fireRate(fireRate), reloadRate(reloadRate), reloadMode(reloadMode) {}
		unsigned short magazine = 0;
		unsigned short ammo = 0;
		unsigned short totalAmmo = 0;
		float fireRate = 0;
		float reloadRate = 0;
		unsigned char reloadMode = 0;

		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->magazine;
			len += sizeof this->ammo;
			len += sizeof this->totalAmmo;
			len += sizeof this->fireRate;
			len += sizeof this->reloadRate;
			len += sizeof this->reloadMode;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->magazine == 0 && !serializer->read(&this->magazine)) {
				return false;
			}
			if (this->ammo == 0 && !serializer->read(&this->ammo)) {
				return false;
			}
			if (this->totalAmmo == 0 && !serializer->read(&this->totalAmmo)) {
				return false;
			}
			if (this->fireRate == 0 && !serializer->read(&this->fireRate)) {
				return false;
			}
			if (this->reloadRate == 0 && !serializer->read(&this->reloadRate)) {
				return false;
			}
			if (this->reloadMode == 0 && !serializer->read(&this->reloadMode)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			serializer->write(this->magazine, stream);
			serializer->write(this->ammo, stream);
			serializer->write(this->totalAmmo, stream);
			serializer->write(this->fireRate, stream);
			serializer->write(this->reloadRate, stream);
			serializer->write(this->reloadMode, stream);
		}
		void dispose() {
		}
	};

	class GameParameters : public ISerializable {
	public:
		GameParameters() : id(0), players(0), teams(0), bases(0), rules(0) {}
		GameParameters(char* id, Array<PlayerInfo> players, Array<TeamInfo> teams, Array<BaseInfo> bases, Rules* rules) : id(id), players(players), teams(teams), bases(bases), rules(rules) {}
		char* id = 0;
		Array<PlayerInfo> players = 0;
		Array<TeamInfo> teams = 0;
		Array<BaseInfo> bases = 0;
		Rules* rules = 0;

		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += serializer->sizeOf(this->id);
			len += sizeof this->players;
			len += sizeof this->teams;
			len += sizeof this->bases;
			len += serializer->sizeOf(this->rules);
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->id == 0 && !serializer->read(&this->id)) {
				return false;
			}
			if (!this->players.deserialize(serializer)) {
				return false;
			}
			if (!this->teams.deserialize(serializer)) {
				return false;
			}
			if (!this->bases.deserialize(serializer)) {
				return false;
			}
			if (this->rules == 0) {
				this->rules = new Rules();
			}
			if (!this->rules->deserialize(serializer)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			serializer->write(this->id, stream);
			this->players.serialize(serializer, stream);
			this->teams.serialize(serializer, stream);
			this->bases.serialize(serializer, stream);
			this->rules->serialize(serializer, stream);
		}
		void dispose() {
			if (this->id != 0) {
				delete this->id;
				this->id = 0;
			}
			if (this->rules != 0) {
				delete this->rules;
				this->rules = 0;
			}
		}
	};

	#define MSG_GAMEPARAMS 0x1

	class GameParamsMessage : public Message {
		unsigned char ver;
	public:
		GameParamsMessage() : ver(0x1) {}
		GameParamsMessage(unsigned char ver) : ver(ver) {}
		GameParameters* params = 0;

		unsigned char type() { return 0x1; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += serializer->sizeOf(this->params);
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->params == 0) {
				this->params = new GameParameters();
			}
			if (!this->params->deserialize(serializer)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			this->params->serialize(serializer, stream);
		}
		void dispose() {
			if (this->params != 0) {
				delete this->params;
				this->params = 0;
			}
		}
	};
	class GameParamsMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x1; }
		Message* get(unsigned char ver) { return new GameParamsMessage(ver); }
	};

	#define MSG_ASSINGPLAYER 0x2

	class AssingPlayerMessage : public Message {
		unsigned char ver;
	public:
		AssingPlayerMessage() : ver(0x1) {}
		AssingPlayerMessage(unsigned char ver) : ver(ver) {}
		unsigned short playerId = 0;
		unsigned short teamId = 0;

		unsigned char type() { return 0x2; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->playerId;
			len += sizeof this->teamId;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->playerId == 0 && !serializer->read(&this->playerId)) {
				return false;
			}
			if (this->teamId == 0 && !serializer->read(&this->teamId)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->playerId, stream);
			serializer->write(this->teamId, stream);
		}
		void dispose() {
		}
	};
	class AssingPlayerMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x2; }
		Message* get(unsigned char ver) { return new AssingPlayerMessage(ver); }
	};

	#define MSG_ASSINGBASE 0x3

	class AssingBaseMessage : public Message {
		unsigned char ver;
	public:
		AssingBaseMessage() : ver(0x1) {}
		AssingBaseMessage(unsigned char ver) : ver(ver) {}
		unsigned short baseId = 0;

		unsigned char type() { return 0x3; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->baseId;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->baseId == 0 && !serializer->read(&this->baseId)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->baseId, stream);
		}
		void dispose() {
		}
	};
	class AssingBaseMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x3; }
		Message* get(unsigned char ver) { return new AssingBaseMessage(ver); }
	};

	#define MSG_NEUTRALBASE 0x4

	class NeutralBaseMessage : public Message {
		unsigned char ver;
	public:
		NeutralBaseMessage() : ver(0x1) {}
		NeutralBaseMessage(unsigned char ver) : ver(ver) {}
		unsigned short baseId = 0;

		unsigned char type() { return 0x4; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->baseId;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->baseId == 0 && !serializer->read(&this->baseId)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->baseId, stream);
		}
		void dispose() {
		}
	};
	class NeutralBaseMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x4; }
		Message* get(unsigned char ver) { return new NeutralBaseMessage(ver); }
	};

	#define MSG_TEAMBASE 0x5

	class TeamBaseMessage : public Message {
		unsigned char ver;
	public:
		TeamBaseMessage() : ver(0x1) {}
		TeamBaseMessage(unsigned char ver) : ver(ver) {}
		unsigned short baseId = 0;
		unsigned short teamId = 0;

		unsigned char type() { return 0x5; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->baseId;
			len += sizeof this->teamId;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->baseId == 0 && !serializer->read(&this->baseId)) {
				return false;
			}
			if (this->teamId == 0 && !serializer->read(&this->teamId)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->baseId, stream);
			serializer->write(this->teamId, stream);
		}
		void dispose() {
		}
	};
	class TeamBaseMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x5; }
		Message* get(unsigned char ver) { return new TeamBaseMessage(ver); }
	};

	#define MSG_RESUPPLYBASE 0x6

	class ResupplyBaseMessage : public Message {
		unsigned char ver;
	public:
		ResupplyBaseMessage() : ver(0x1) {}
		ResupplyBaseMessage(unsigned char ver) : ver(ver) {}
		unsigned short baseId = 0;
		unsigned short healthRate = 0;
		unsigned short ammoRate = 0;

		unsigned char type() { return 0x6; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->baseId;
			len += sizeof this->healthRate;
			len += sizeof this->ammoRate;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->baseId == 0 && !serializer->read(&this->baseId)) {
				return false;
			}
			if (this->healthRate == 0 && !serializer->read(&this->healthRate)) {
				return false;
			}
			if (this->ammoRate == 0 && !serializer->read(&this->ammoRate)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->baseId, stream);
			serializer->write(this->healthRate, stream);
			serializer->write(this->ammoRate, stream);
		}
		void dispose() {
		}
	};
	class ResupplyBaseMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x6; }
		Message* get(unsigned char ver) { return new ResupplyBaseMessage(ver); }
	};

	#define MSG_HITREPORT 0x7

	class HitReportMessage : public Message {
		unsigned char ver;
	public:
		HitReportMessage() : ver(0x1) {}
		HitReportMessage(unsigned char ver) : ver(ver) {}
		unsigned short targetId = 0;
		unsigned short sourceId = 0;

		unsigned char type() { return 0x7; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->targetId;
			len += sizeof this->sourceId;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->targetId == 0 && !serializer->read(&this->targetId)) {
				return false;
			}
			if (this->sourceId == 0 && !serializer->read(&this->sourceId)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->targetId, stream);
			serializer->write(this->sourceId, stream);
		}
		void dispose() {
		}
	};
	class HitReportMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x7; }
		Message* get(unsigned char ver) { return new HitReportMessage(ver); }
	};

	#define MSG_BASECAPTURE 0x8

	class BaseCaptureMessage : public Message {
		unsigned char ver;
	public:
		BaseCaptureMessage() : ver(0x1) {}
		BaseCaptureMessage(unsigned char ver) : ver(ver) {}
		unsigned short baseId = 0;
		unsigned short playerId = 0;

		unsigned char type() { return 0x8; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->baseId;
			len += sizeof this->playerId;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->baseId == 0 && !serializer->read(&this->baseId)) {
				return false;
			}
			if (this->playerId == 0 && !serializer->read(&this->playerId)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->baseId, stream);
			serializer->write(this->playerId, stream);
		}
		void dispose() {
		}
	};
	class BaseCaptureMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x8; }
		Message* get(unsigned char ver) { return new BaseCaptureMessage(ver); }
	};

	#define MSG_RESUPPLY 0x9

	class ResupplyMessage : public Message {
		unsigned char ver;
	public:
		ResupplyMessage() : ver(0x1) {}
		ResupplyMessage(unsigned char ver) : ver(ver) {}
		unsigned short health = 0;
		unsigned short ammo = 0;

		unsigned char type() { return 0x9; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += sizeof this->health;
			len += sizeof this->ammo;
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->health == 0 && !serializer->read(&this->health)) {
				return false;
			}
			if (this->ammo == 0 && !serializer->read(&this->ammo)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->health, stream);
			serializer->write(this->ammo, stream);
		}
		void dispose() {
		}
	};
	class ResupplyMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0x9; }
		Message* get(unsigned char ver) { return new ResupplyMessage(ver); }
	};

	#define MSG_INFORMATION 0xa

	class InformationMessage : public Message {
		unsigned char ver;
	public:
		InformationMessage() : ver(0x1) {}
		InformationMessage(unsigned char ver) : ver(ver) {}
		char* message = 0;

		unsigned char type() { return 0xa; }
		unsigned char version() { return this->ver; }
		unsigned char length(Serializer* serializer) {
			unsigned char len = 0;
			len += serializer->sizeOf(this->message);
			return len;
		}
		bool deserialize(Serializer *serializer) {
			if (this->message == 0 && !serializer->read(&this->message)) {
				return false;
			}
			return true;
		}
		void serialize(Serializer *serializer, Stream *stream) {
			Message::serialize(serializer, stream);
			serializer->write(this->message, stream);
		}
		void dispose() {
			if (this->message != 0) {
				delete this->message;
				this->message = 0;
			}
		}
	};
	class InformationMessageFactory : public MessageFactory {
	public:
		unsigned char type() { return 0xa; }
		Message* get(unsigned char ver) { return new InformationMessage(ver); }
	};

#define REGISTER(p)	\
	p.addFactory(new GameParamsMessageFactory());	\
	p.addFactory(new AssingPlayerMessageFactory());	\
	p.addFactory(new AssingBaseMessageFactory());	\
	p.addFactory(new NeutralBaseMessageFactory());	\
	p.addFactory(new TeamBaseMessageFactory());	\
	p.addFactory(new ResupplyBaseMessageFactory());	\
	p.addFactory(new HitReportMessageFactory());	\
	p.addFactory(new BaseCaptureMessageFactory());	\
	p.addFactory(new ResupplyMessageFactory());	\
	p.addFactory(new InformationMessageFactory());	\

}
#endif

