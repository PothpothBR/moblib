/*
  ----------------------------------------------------
  |              Biblioteca feita por                |
  |     [Bruno Dalagnol] [2018] [versao: sei la]     |
  |--------------------------------------------------|
  |                                                  |
  |			    /\         /\       ___              |
  |			   /--\_______/--\     /  _|             |
  |			   |  Y       Y  |    / /                |
  |			   |    ==T==    |   / /                 |
  |			   \_____________/  / /                  |
  |				  |  _____   \ / /                   |
  |				  |           \ /                    |
  |				  |  |--|  |\  |                     |
  |				  |__||_|__||__|                     |
  ----------------------------------------------------
*/

#ifndef TIMING_H
#define TIMING_H

class MOB_TICKS {
public:
	float *time = 0;
	int buffer = 0;
	bool local = false;
// contador em segundos ou frames

	MOB_TICKS(){}

	MOB_TICKS(float time, float FPS = 0) {
		this->time = new float;
		if (FPS > 0.0)*this->time = time / FPS;
		else *this->time = time;
		local = true;
		
	}
	// contador em segundos ou frames
	MOB_TICKS(float *time, float FPS = 0.0) {
		if (FPS > 0.0) { this->time = time; *this->time =(int) *time / FPS; }
		else this->time = time;
		local = false;
		
	}
	~MOB_TICKS() {
		if (local) delete time;
	}
 // gera MOB_TICKS ate poder disparar e aguarda
	inline void wait() { if (buffer > 0)buffer--; }
// dispara, e reseta se possivel
	inline bool trigger() { if (buffer < 1) { buffer = *time; return true; } return false; } 
 // tick continuo
	inline bool tick() { if (buffer <= 1) { buffer = *time; return true; } else buffer--; return false; }

	inline void set_time(float time, float FPS = 0.0) {
		this->time = new float;
		if (FPS > 0.0)*this->time = time / FPS;
		else *this->time = time;
		local = true;
	}

	inline void set_time(float *time, float FPS = 0.0) {
		if (FPS > 0.0) { this->time = time; *this->time = (int)*time / FPS; }
		else this->time = time;
		local = false;
	}

	inline void reset() {
		buffer = *time;
	}

	inline void charge() {
		buffer = 0;
	}
	
};

#endif // !TIMING_H