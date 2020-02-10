#include "StateMachine.h"
#include <algorithm>
using namespace std;


enum class STATE ParticlesUpdate(enum class STATE time_line, RuntimeInfo* runtime_info, Particle* particles, int* particle_number) {
	switch (time_line) {
	case STATE::P0_IDLE: {
		;
	} break;

	case STATE::P1_RESET_DISABLE: {
		for (int i = 0; i < *particle_number; i++)
			particles[i].disable();
	} break;

	case STATE::P1_SET_XPOS: {
		runtime_info->Xpos = -30.0f;
		for (int i = 0; i < 1; i++) {
			particles[i].set_middle(runtime_info->Xpos, 0, 0);
			particles[i].set_scale(3.0f);
			particles[i].enable();
		}
	} break;

	case STATE::P1_X_MOVEMENT: {
		float incre = 0.05f;
		runtime_info->Xpos += incre;
		for (int i = 0; i < 1; i++) {
			particles[i].enable();
			particles[i].set_middle_x(runtime_info->Xpos);
			//particles[i].set_middle_y(0);
			//particles[i].add_middle(float(rand() % 20 - 10) / 5.0f, float(rand()%20-10)/5.0f, 0);
			particles[i].rotate_clockwise();
		}
	} break;

	case STATE::P2_RESET_DISABLE: {
		for (int i = 0; i < *particle_number; i++)
			particles[i].disable();
	} break;

	case STATE::P2_SET_XPOS: {
		runtime_info->Xpos = -50.0f;
		for (int i = 0; i < *particle_number; i++)
			particles[i].set_middle(-10.0f, 0, 0);
	} break;

	case STATE::P2_SET_TIMER: {
		runtime_info->Timer = 500.0f;
		runtime_info->Timer_Down = 25.0f;
	} break;

	case STATE::P2_WAIT_TIMER: {
		runtime_info->Timer -= runtime_info->Timer_Down;
	} break;

	case STATE::P2_X_MOVEMENT: {
		//float incre = float(rand()%100-50)/25.0f + 2.0f;
		float incre = 1.0f;
		runtime_info->Xpos += incre;
		for (int i = 0; i < *particle_number; i++) {
			float radius = 3 * float(120 - rand()%40) / 100.0f;
			float angleX = float(rand() % 100 - 50) / 30.0f * 2 * PI;
			float angleY = float(rand() % 100 - 50) / 30.0f * 2 * PI;
			float angleZ = float(rand() % 100 - 50) / 30.0f * 2 * PI;
			particles[i].enable();
			particles[i].set_middle_x(runtime_info->Xpos);
			particles[i].set_middle_y(0);
			particles[i].set_middle_z(0);
			particles[i].add_middle(
				sin(angleY) * cos(angleX) * radius,
				cos(angleY) * radius,
				sin(angleY) * sin(angleX) * radius
			);
			particles[i].set_scale(float(rand() % 100) / 30.0f + 0.01f);
			particles[i].rotate_clockwise(rand() % 4);
		}

		// Choose some particles as remain effect
		for (int i = 0; i < 20; i++) {
			particles[i].enable();
			particles[i].add_middle(-float(rand() % 100) / 5.0f, 0, 0);
			particles[i].mult_middle(1.0f, 0.1f, 1.0f);
			particles[i].set_scale(max(20-abs(particles[i].get_middle_x() - runtime_info->Xpos),0.0f)/4.0f);
		}
	} break;

	case STATE::P2_5_SET_TIMER: {
		runtime_info->Timer = 500.0f;
		runtime_info->Timer_Down = 5.0f;
	} break;

	case STATE::P2_5_WAIT_TIMER: {
		runtime_info->Timer -= runtime_info->Timer_Down;
	} break;

	case STATE::P3_RESET_DISABLE: {
		for (int i = 0; i < *particle_number; i++)
			particles[i].disable();
	} break;

	case STATE::P3_SET_TIMER: {
		;
	} break;

	case STATE::P3_EARTH_IS_ROTATING: {
		for (int i = 0; i < 50; i++) {
			float radius = 15;
			int random = rand() % 360;
			float angle = 2.0f * PI / 360.0f;
			particles[i].enable();
			particles[i].set_middle(
				sin(random * angle) * radius,
				cos(random * angle) * radius,
				0.0f
			);
			float duse = float(120-rand()%40) / 100.0f;
			particles[i].mult_middle(
				duse,
				duse,
				1.0f
			);
			if (i < 6) {
				particles[i].mult_middle(
					0.7*duse,
					0.7*duse,
					1.0f
				);
			}
			particles[i].set_scale(float(80-rand() % 100) / 30.0f + 1.0f);
			particles[i].rotate_clockwise(rand() % 4);
		}
	} break;

	case STATE::P4_RESET_DISABLE: {
		for (int i = 0; i < *particle_number; i++)
			particles[i].disable();
	} break;

	case STATE::P4_SET_XPOS: {
		runtime_info->Xpos = -60.0f;
		for (int i = 0; i < *particle_number; i++)
			particles[i].set_middle(-10.0f, 0, 0);
	} break;

	case STATE::P4_SET_TIMER: {
		runtime_info->Timer = 500.0f;
		runtime_info->Timer_Down = 40.0f;
	} break;

	case STATE::P4_WAIT_TIMER: {
		runtime_info->Timer -= runtime_info->Timer_Down;
	} break;

	case STATE::P4_EARTH_IS_SIDE: {
		//float incre = float(rand()%100-50)/25.0f + 2.0f;
		float incre = 0.625f;
		runtime_info->Xpos += incre;
		for (int i = 0; i < *particle_number; i++) {
			float radius = 3 * float(120 - rand() % 40) / 100.0f;
			float angleX = float(rand() % 100 - 50) / 20.0f * 2 * PI;
			float angleY = float(rand() % 100 - 50) / 20.0f * 2 * PI;
			float angleZ = float(rand() % 100 - 50) / 20.0f * 2 * PI;
			//particles[i].enable();
			particles[i].set_middle_x(runtime_info->Xpos);
			particles[i].set_middle_y(0);
			particles[i].set_middle_z(0);
			particles[i].add_middle(
				sin(angleY) * cos(angleX) * radius,
				cos(angleY) * radius,
				sin(angleY) * sin(angleX) * radius
			);
			particles[i].set_scale(float(rand() % 100) / 30.0f + 0.01f);
			particles[i].rotate_clockwise(rand() % 4);
		}

		// Choose some particles as remain effect
		for (int i = 0; i < 20; i++) {
			//particles[i].enable();
			particles[i].add_middle(-float(rand() % 100) / 5.0f, 0, 0);
			particles[i].mult_middle(1.0f, 0.1f, 1.0f);
			particles[i].set_scale(max(20 - abs(particles[i].get_middle_x() - runtime_info->Xpos), 0.0f) / 4.0f);
		}
	} break;

	case STATE::P5_RESET_DISABLE: {
		for (int i = 0; i < *particle_number; i++)
			particles[i].enable();
	} break;

	case STATE::P5_SET_XPOS: {
		runtime_info->Xpos = -300.0f;
		for (int i = 0; i < *particle_number; i++)
			particles[i].set_middle(-50.0f, 0, -75.0f);
	} break;

	case STATE::P5_SET_TIMER: {
		runtime_info->Timer = 500.0f;
		runtime_info->Timer_Down = 45.0f;
	} break;

	case STATE::P5_WAIT_TIMER: {
		runtime_info->Timer -= runtime_info->Timer_Down;
	} break;

	case STATE::P5_EARTH_IS_FAR: {
		//float incre = float(rand()%100-50)/25.0f + 2.0f;
		float incre = 3.0f;
		runtime_info->Xpos += incre;
		for (int i = 0; i < *particle_number; i++) {
			float radius = 3 * float(120 - rand() % 40) / 100.0f;
			float angleX = float(rand() % 100 - 50) / 20.0f * 2 * PI;
			float angleY = float(rand() % 100 - 50) / 20.0f * 2 * PI;
			float angleZ = float(rand() % 100 - 50) / 20.0f * 2 * PI;
			particles[i].enable();
			particles[i].set_middle_x(runtime_info->Xpos);
			particles[i].set_middle_y(0);
			particles[i].set_middle_z(-75.0f);
			particles[i].add_middle(
				sin(angleY) * cos(angleX) * radius,
				cos(angleY) * radius,
				sin(angleY) * sin(angleX) * radius
			);
			particles[i].set_scale(float(rand() % 100) / 30.0f + 0.01f);
			particles[i].rotate_clockwise(rand() % 4);
		}

		// Choose some particles as remain effect
		for (int i = 0; i < 20; i++) {
			particles[i].enable();
			particles[i].add_middle(-float(rand() % 100) / 5.0f, 0, 0);
			particles[i].mult_middle(1.0f, 0.1f, 1.0f);
			particles[i].set_scale(max(20 - abs(particles[i].get_middle_x() - runtime_info->Xpos), 0.0f) / 4.0f);
		}

		// Another Effect
		for (int i = 20; i < 45; i++) {
			if (runtime_info->Xpos >= 0.0f) {
				float radius = runtime_info->Xpos;
				float angleX = float(rand() % 100 - 50) / 20.0f * 2 * PI;
				float angleY = float(rand() % 100 - 50) / 20.0f * 2 * PI;
				float angleZ = float(rand() % 100 - 50) / 20.0f * 2 * PI;
				particles[i].enable();
				particles[i].set_middle(
					sin(angleY) * cos(angleX) * radius,
					cos(angleY) * radius,
					sin(angleY) * sin(angleX) * radius
				);
				particles[i].set_scale(1.0f);
			}
		}
	} break;

	case STATE::P5_5_SET_COUNTER: {
		for (int i = 0; i < *particle_number; i++) {
			particles[i].disable();
		}
	} break;

	case STATE::P5_5_SET_TIMER: {

	} break;

	case STATE::P5_5_WAIT_TIMER: {

	} break;

	case STATE::P5_5_EARTH_IS_SHAKING: {

	} break;

	case STATE::P6_RESET_DISABLE: {
		for (int i = 0; i < *particle_number; i++) {
			particles[i].enable();
		}
	} break;

	case STATE::P6_SET_XPOS: {
		runtime_info->Xpos = 0.0f;
		runtime_info->Xpos_Down = 6.5f;
	} break;

	case STATE::P6_SET_TIMER: {
		runtime_info->Timer = 500.0f;
		runtime_info->Timer_Down = 25.0f;
	} break;

	case STATE::P6_WAIT_TIMER: {
		runtime_info->Timer -= runtime_info->Timer_Down;
	} break;

	case STATE::P6_EXPLOSION: {
		float center[3] = { 0, 0, -15.0f };
		set_sphere_explosion(runtime_info, particles, *particle_number, center, max(runtime_info->Xpos,0.0f));
		if (runtime_info->reverse == 0)
			runtime_info->Xpos += 0.1f;
		else if (runtime_info->reverse == 1) {
			if(runtime_info->Xpos <= -3.0f) runtime_info->shaking = 0;
			runtime_info->Xpos_Down -= 1.0f;
			runtime_info->Xpos -= max(runtime_info->Xpos_Down,0.2f);
		}
		else {
			runtime_info->shaking = 1;
			runtime_info->Xpos_Down -= 1.0f;
			runtime_info->Xpos += max(runtime_info->Xpos_Down,0.2f);
		}
		
	} break;

	default: {} break;
	}

	enum STATE next_state;

	switch (time_line) {
	case STATE::P0_IDLE: {
		next_state = STATE::P2_RESET_DISABLE;
	} break;

	case STATE::P1_RESET_DISABLE: {
		next_state = STATE::P1_SET_XPOS;
	} break;

	case STATE::P1_SET_XPOS: {
		next_state = STATE::P1_X_MOVEMENT;
	} break;

	case STATE::P1_X_MOVEMENT: {
		if (runtime_info->Xpos > 15.0f) next_state = STATE::P2_RESET_DISABLE;
		else next_state = STATE::P1_X_MOVEMENT;
	} break;

	case STATE::P2_RESET_DISABLE: {
		next_state = STATE::P2_SET_XPOS;
	} break;

	case STATE::P2_SET_XPOS: {
		next_state = STATE::P2_SET_TIMER;
	} break;

	case STATE::P2_SET_TIMER: {
		next_state = STATE::P2_WAIT_TIMER;
	} break;

	case STATE::P2_WAIT_TIMER: {
		if (runtime_info->Timer < 0.0f) next_state = STATE::P2_X_MOVEMENT;
		else next_state = STATE::P2_WAIT_TIMER;
	} break;

	case STATE::P2_X_MOVEMENT: {
		if (runtime_info->Xpos > 40.0f) next_state = STATE::P2_5_SET_TIMER;
		else next_state = STATE::P2_SET_TIMER;
	} break;

	case STATE::P2_5_SET_TIMER: {
		next_state = STATE::P2_5_WAIT_TIMER;
	} break;

	case STATE::P2_5_WAIT_TIMER: {
		if (runtime_info->Timer < 0.0f) next_state = STATE::P3_RESET_DISABLE;
		else next_state = STATE::P2_5_WAIT_TIMER;
	} break;

	case STATE::P3_RESET_DISABLE: {
		next_state = STATE::P3_SET_TIMER;
	} break;

	case STATE::P3_SET_TIMER: {
		next_state = STATE::P3_EARTH_IS_ROTATING;
	} break;

	case STATE::P3_EARTH_IS_ROTATING: {
		if (runtime_info->Timer < 0.0f) next_state = STATE::P5_RESET_DISABLE;
		else next_state = STATE::P3_EARTH_IS_ROTATING;
	} break;

	case STATE::P4_RESET_DISABLE: {
		next_state = STATE::P4_SET_XPOS;
	} break;

	case STATE::P4_SET_XPOS: {
		next_state = STATE::P4_SET_TIMER;
	} break;

	case STATE::P4_SET_TIMER: {
		next_state = STATE::P4_WAIT_TIMER;
	} break;

	case STATE::P4_WAIT_TIMER: {
		if (runtime_info->Timer < 0.0f) next_state = STATE::P4_EARTH_IS_SIDE;
		else next_state = STATE::P4_WAIT_TIMER;
	} break;

	case STATE::P4_EARTH_IS_SIDE: {
		if (runtime_info->Xpos > -30.0f) next_state = STATE::P5_RESET_DISABLE;
		else next_state = STATE::P4_SET_TIMER;
	} break;

	case STATE::P5_RESET_DISABLE: {
		next_state = STATE::P5_SET_XPOS;
	} break;

	case STATE::P5_SET_XPOS: {
		next_state = STATE::P5_SET_TIMER;
	} break;

	case STATE::P5_SET_TIMER: {
		next_state = STATE::P5_WAIT_TIMER;
	} break;

	case STATE::P5_WAIT_TIMER: {
		if (runtime_info->Timer < 0.0f) next_state = STATE::P5_EARTH_IS_FAR;
		else next_state = STATE::P5_WAIT_TIMER;
	} break;

	case STATE::P5_EARTH_IS_FAR: {
		if (runtime_info->Xpos > 120.0f) next_state = STATE::P5_5_SET_COUNTER;
		else next_state = STATE::P5_SET_TIMER;
	} break;

	case STATE::P5_5_SET_COUNTER: {
		next_state = STATE::P5_5_SET_TIMER;
	} break;

	case STATE::P5_5_SET_TIMER: {
		next_state = STATE::P5_5_WAIT_TIMER;
	} break;

	case STATE::P5_5_WAIT_TIMER: {
		if (runtime_info->Timer < 0.0f) next_state = STATE::P5_5_EARTH_IS_SHAKING;
		else next_state = STATE::P5_5_WAIT_TIMER;
	} break;

	case STATE::P5_5_EARTH_IS_SHAKING: {
		if (runtime_info->counter == 0) next_state = STATE::P6_RESET_DISABLE;
		else next_state = STATE::P5_5_SET_TIMER;
	} break;

	case STATE::P6_RESET_DISABLE: {
		next_state = STATE::P6_SET_XPOS;
	} break;
	
	case STATE::P6_SET_XPOS: {
		next_state = STATE::P6_SET_TIMER;
	} break;

	case STATE::P6_SET_TIMER: {
		next_state = STATE::P6_WAIT_TIMER;
	} break;

	case STATE::P6_WAIT_TIMER: {
		if (runtime_info->Timer < 0.0f) next_state = STATE::P6_EXPLOSION;
		else next_state = STATE::P6_WAIT_TIMER;
	} break;

	case STATE::P6_EXPLOSION: {
		if (runtime_info->Xpos > 30.0f && runtime_info->reverse == 0) {
			runtime_info->Xpos_Down = 6.5f;
			runtime_info->reverse = 1;
			next_state = STATE::P6_SET_TIMER;
		}
		else if (runtime_info->Xpos <= -5.0f && runtime_info->reverse == 1) {
			runtime_info->Xpos_Down = 7.0f;
			runtime_info->reverse = 2;
			next_state = STATE::P6_SET_TIMER;
		}
		else if (runtime_info->Xpos >= 90.0f && runtime_info->reverse == 2) {
			runtime_info->reverse = 0;
			next_state = STATE::P0_IDLE;
		}
		else next_state = STATE::P6_SET_TIMER;
	} break;

	default: {
		next_state = STATE::P0_IDLE;
	} break;
	}

	return next_state;
}


enum class STATE EarthUpdate(enum class STATE time_line, RuntimeInfo* runtime_info, Element* earth, int earth_particle_number) {
	switch (time_line) {
	case STATE::P0_IDLE: {
		for (int i = 0; i < earth_particle_number; i++)
			earth[i].enable = 0;
	} break;

	case STATE::P1_RESET_DISABLE: {
		for (int i = 0; i < earth_particle_number; i++)
			earth[i].enable = 0;
	} break;

	case STATE::P2_RESET_DISABLE: {
		for (int i = 0; i < earth_particle_number; i++)
			earth[i].enable = 0;
	} break;

	case STATE::P3_RESET_DISABLE: {
		for (int i = 0; i < earth_particle_number; i++)
			earth[i].enable = 1;
	} break;

	case STATE::P3_SET_TIMER: {
		runtime_info->Timer = 360.0f;
		runtime_info->Timer_Down = 0.2f;
	} break;

	case STATE::P3_EARTH_IS_ROTATING: {
		runtime_info->Timer -= runtime_info->Timer_Down;
	} break;

	case STATE::P5_5_SET_COUNTER: {
		runtime_info->counter = 15;
	} break;

	case STATE::P5_5_SET_TIMER: {
		runtime_info->Timer = 300.0f;
		runtime_info->Timer_Down = 1.0f;
	} break;

	case STATE::P5_5_WAIT_TIMER: {
		runtime_info->Timer -= runtime_info->Timer_Down;
	} break;

	case STATE::P5_5_EARTH_IS_SHAKING: {
		runtime_info->counter--;
	} break;

	case STATE::P6_RESET_DISABLE: {
		for (int i = 0; i < earth_particle_number; i++)
			earth[i].enable = 1;
	} break;

	case STATE::P6_EXPLOSION: {
		if (runtime_info->Xpos > 10.0f) {
			for (int i = 0; i < earth_particle_number; i++)
				earth[i].enable = 0;
		}
	} break;
	
	default: {} break;
	}

	enum STATE next_state = STATE::P0_IDLE;
	return next_state;
}
