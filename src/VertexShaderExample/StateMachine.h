#pragma once
#include "FreeImage.h"
#include "glew.h"
#include "Particle.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

enum class STATE ParticlesUpdate(enum class STATE time_line, RuntimeInfo* runtime_info, Particle* particles, int* particle_number);

enum class STATE EarthUpdate(enum class STATE time_line, RuntimeInfo* runtime_info, Element* earth, int earth_particle_number);

