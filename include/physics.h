#pragma once
#include "particle.h"
#include <math.h>
#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float GetRandomFloat(float a, float b);
Vector2 LerpMotion(Vector2, Vector2 end, float t);
void BoundsAndGravityCheck(Particle *p, int collisionLess, int enableGravity);
void ParticleRandomMotion(Particle *parr, int total_particles,
                          Vector2 ForceRange, float curveStrength,
                          int enableGravity);
void ParticleClusterMotion(ParticleCluster *cluster, float curveStrength,
                           int enableGravity);
