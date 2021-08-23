#ifndef TIMING_H
#define TIMING_H

class TICKS {
public:
	float *time = 0;
	int buffer = 0;
	bool local = false;
	TICKS(float time, float FPS = 0) {// contador em segundos ou frames
		this->time = new float;
		if (FPS > 0.0)*this->time = time / FPS;
		else *this->time = time;
		local = true;
		
	}
	TICKS(float *time, float FPS) {// contador em segundos ou frames
		if (FPS > 0) { this->time = time; *this->time =(int) *time / FPS; }
		else this->time = time;
		local = false;
		
	}
	~TICKS() {
		if (local) delete time;
	}

	inline void wait() { if (buffer > 0)buffer--; } // gera TICKS ate poder disparar e aguarda
	inline bool trigger() { if (buffer < 1) { buffer = *time; return true; } return false; } // dispara, e reseta se possivel
	inline bool tick() { if (buffer < 1) { buffer = *time; return true; } else buffer--; return false; } // tick continuo
	
};

#endif // !TIMING_H