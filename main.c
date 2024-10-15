#include "include/globals.h"
#include "include/particle.h"
#include "include/physics.h"
#include <raylib.h>

int main(int argc, char *argv[]) {
  //+----------------------------------------------------------------------------------+
  // Configuration Begins
  //+----------------------------------------------------------------------------------+
  srand(time(0));
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT,
             "raylib [particle simulation] - testing");
  Vector2 MotionForceRange = {-15.0f, 15.0f};
  SetTargetFPS(FPS);
  //+----------------------------------------------------------------------------------+
  // Configuration Ends
  //+----------------------------------------------------------------------------------+

  //+----------------------------------------------------------------------------------+
  //  Simuation Physics Config and Render Begins
  //+----------------------------------------------------------------------------------+
  Particle *particle_array = SpawnParticles(TOTAL_PARTICLES);

  // CLuster Properties | Will only be used if CLUSTER_MOTION is true (1)
  Vector2 cluster_velocity = {0.0f, 0.0f};
  float cluster_speed = 5.0f;
  float cluster_angle = GetRandomFloat(0, 2 * PI);

  ParticleCluster cluster = {particle_array, TOTAL_PARTICLES, cluster_velocity,
                             cluster_speed, cluster_angle};
  //+----------------------------------------------------------------------------------+
  //  Simuation Physics Config and Render Ends
  //+----------------------------------------------------------------------------------+

  //+----------------------------------------------------------------------------------+
  //  Text Rendering Variables
  float TextFontSize = 20;
  float TextLeftX = 15;
  float TextLeftY = 20;
  float TextRightX = SCREEN_WIDTH - (14 * 15 + 5);
  float TextRightY = 20;
  //+----------------------------------------------------------------------------------+
  // Main simulation loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    if (IsKeyPressed(RELOAD_SIM)) {
      free(particle_array);
      particle_array = SpawnParticles(TOTAL_PARTICLES);
    }

    //----------------------------------------------------------------------------------
    // Draw/Render Begins here
    //----------------------------------------------------------------------------------
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Particle Simulation 0.1 - Elastic", TextLeftX, TextLeftY,
             TextFontSize, GRAY);
    DrawText("Press 'R' to reload!", TextRightX, TextRightY, TextFontSize,
             GRAY);
    DrawParticles(particle_array, TOTAL_PARTICLES);
    if (CLUSTER_MOTION == 1) {
      ParticleClusterMotion(&cluster, 0.03f, 1);
    } else {
      ParticleRandomMotion(particle_array, TOTAL_PARTICLES, MotionForceRange,
                           0.03f, 1);
    }
    EndDrawing();
    //----------------------------------------------------------------------------------
    // Draw/Render Ends here
    //----------------------------------------------------------------------------------
  }
  free(particle_array);
  return 0;
}
