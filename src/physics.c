
#include "../include/physics.h"
#include "../include/globals.h"

float GetRandomFloat(float a, float b) {
  return a + ((float)rand() / RAND_MAX) * (b - a);
}

Vector2 LerpMotion(Vector2 start, Vector2 end, float t) {
  // t : lerpFactor
  return (Vector2){start.x + t * (end.x - start.x),
                   start.y + t * (end.y - start.y)};
}

void BoundsAndGravityCheck(Particle *p, int collisionLess, int enableGravity) {
  float paddingX = 15.0f;
  float paddingY = 15.0f;
  float pushFactor = 3.25f;
  float clamp_speed = 8.0f;

  float gravitationalConst = 5.0f;
  float pullStrength = 0.05f;

  if (enableGravity == 1) {
    Vector2 target_velocity = p->velocity;
    target_velocity.y += gravitationalConst * pullStrength;
    p->velocity = LerpMotion(p->velocity, target_velocity, 0.05f);
  }

  if (p->velocity.x > clamp_speed)
    p->velocity.x = clamp_speed;
  if (p->velocity.y > clamp_speed)
    p->velocity.y = clamp_speed;

  if (p->velocity.x < -clamp_speed)
    p->velocity.x = -clamp_speed;
  if (p->velocity.y < -clamp_speed)
    p->velocity.y = -clamp_speed;

  if (collisionLess == 1) {
    // Applying boundary wrapping instead of collisions
    if (p->position.x > SCREEN_WIDTH)
      p->position.x = 0;
    if (p->position.x < 0)
      p->position.x = SCREEN_WIDTH;
    if (p->position.y > SCREEN_HEIGHT)
      p->position.y = 0;
    if (p->position.y < 0)
      p->position.y = SCREEN_HEIGHT;
  } else {
    // Applying Boundary Collisions instead of wrapping
    if (p->position.x >= (SCREEN_WIDTH - paddingX) ||
        p->position.x <= paddingX) {
      p->velocity.x *= -1; // Reverse the x-direction
      p->position.x += (p->velocity.x / fabs(p->velocity.x)) * pushFactor;
      p->angle = PI - p->angle;
    }
    if (p->position.y >= (SCREEN_HEIGHT - paddingY) ||
        p->position.y <= paddingY) {
      p->velocity.y *= -1; // Reverse the y-direction
      p->position.y += (p->velocity.y / fabs(p->velocity.y)) * pushFactor;
      p->angle = -p->angle;
    }
  }
}
void ParticleRandomMotion(Particle *parr, int total_particles,
                          Vector2 ForceRange, float curveStrength,
                          int enableGravity) {
  for (int i = 0; i < total_particles; i++) {
    Particle *p = &parr[i];
    Vector2 target_velocity = p->velocity;
    p->angle += curveStrength * GetRandomFloat(-0.25, 0.25);
    // if (p->angle >= 2 * PI)
    //   p->angle = 0.0f;
    target_velocity.x +=
        (0.05f * ((float)GetRandomValue(0, p->particle_speed))) * sin(p->angle);
    target_velocity.y +=
        0.05f * ((float)GetRandomValue(0, p->particle_speed)) * cos(p->angle);

    float lerp_factor = 0.05f;
    p->velocity = LerpMotion(p->velocity, target_velocity, lerp_factor);
    p->position.x += p->velocity.x;
    p->position.y += p->velocity.y;
    BoundsAndGravityCheck(p, 0, enableGravity);
  }
}

void ParticleClusterMotion(ParticleCluster *cluster, float curveStrength,
                           int enableGravity) {

  cluster->cluster_angle += curveStrength * GetRandomFloat(-1, 1);
  cluster->cluster_velocity.x +=
      (0.05f * ((float)GetRandomValue(0, cluster->cluster_speed))) *
      sin(cluster->cluster_angle);
  cluster->cluster_velocity.y +=
      0.05f * ((float)GetRandomValue(0, cluster->cluster_speed)) *
      cos(cluster->cluster_angle);

  for (int i = 0; i < cluster->TotalParticles; i++) {

    Particle *p = &cluster->parray[i];
    p->angle = cluster->cluster_angle;
    // p->angle += curveStrength * GetRandomFloat(-.1f, .1f);
    p->angle += curveStrength * GetRandomFloat(-1, 1);
    p->velocity = cluster->cluster_velocity;
    p->velocity.x += (0.05f * ((float)GetRandomFloat(-1, 1))) * sin(p->angle);
    p->velocity.y += 0.05f * ((float)GetRandomFloat(-1, 1)) * cos(p->angle);
    p->position.x += p->velocity.x;
    p->position.y += p->velocity.y;
    BoundsAndGravityCheck(p, 1, enableGravity);
  }
}
