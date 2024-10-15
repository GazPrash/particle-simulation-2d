#pragma once
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
  Vector2 position;
  Vector2 velocity;
  float particle_radius;
  float particle_speed;
  float angle;
  Color color;

} Particle;

typedef struct {
  Particle *parray;
  int TotalParticles;
  Vector2 cluster_velocity;
  float cluster_speed;
  float cluster_angle;
} ParticleCluster;

Particle *SpawnParticles(int n);
void DrawParticles(const Particle *parr, int total_particles);
