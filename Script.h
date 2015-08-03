#ifndef _SCRIPT
#define _SCRIPT

namespace OpenBattle {
	struct Step
	{
	public:
		void(*callback)() = 0;
		unsigned long duration;
		Step(unsigned long duration, void(*callback)() = 0) : duration(duration), callback(callback) {
		}
	};

	class Script {
		unsigned char numSteps;
		unsigned char currStep;
		unsigned long stepRemain;
		Step **steps;
	public:
		Script(Step *steps[], unsigned char numSteps) : steps(steps), numSteps(numSteps) {
			//this->stepRemain = this->steps[0]->duration;
			this->stepRemain = 0;
			this->currStep = numSteps - 1;
		}
		unsigned char step() {
			return this->currStep % this->numSteps;
		}
		void update(unsigned long delta) {
			if (delta < this->stepRemain) {
				this->stepRemain -= delta;
				return;
			}
			if (this->stepRemain > 0) {
				delta -= this->stepRemain;
			}
			this->currStep++;
			if (this->steps[this->step()]->callback != 0) {
				this->steps[this->step()]->callback();
			}
			this->stepRemain = this->steps[this->step()]->duration;
			this->update(delta);
		}
	};

	class ScriptRunner {
		Script *script;
		unsigned long lastUpdate = 0;
	public:
		ScriptRunner(Script* script = 0) : script(script) { }
		void setScript(Script *script) {
			this->script = script;
		}
		void update(unsigned long time) {
			if (this->script == 0) {
				return;
			}
			this->script->update(time - this->lastUpdate);
			this->lastUpdate = time;
		}
	};
}

#endif
