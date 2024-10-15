// #include "../include/particle.h"
#include "../include/particle.h"
#include "../include/globals.h"
#include "../include/physics.h"

Particle *SpawnParticles(int n) {
  // NOTE: Heap Allocatin here
  float paddingX = 15.0f;
  float paddingY = 15.0f;
  Particle *particle_array = (Particle *)malloc(sizeof(Particle) * n);
  for (int i = 0; i < n; i++) {
    float x_posn = GetRandomFloat(0, SCREEN_WIDTH) - paddingX;
    float y_posn = GetRandomFloat(0, SCREEN_HEIGHT) - paddingY;
    float angle = (float)GetRandomFloat(-2 * PI, 2 * PI);
    Particle p = {{x_posn, y_posn}, {0.0f, 0.0f}, 10.0f,
                  PARTICLE_SPEED,   angle,        RED};
    particle_array[i] = p;
  }
  return particle_array;
}

void DrawParticles(const Particle *parr, int total_particles) {
  for (int i = 0; i < total_particles; i++) {
    Particle p = parr[i];
    DrawCircleV(p.position, p.particle_radius, p.color);
  }
}
