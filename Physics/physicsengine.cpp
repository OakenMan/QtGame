#include "physicsengine.h"
#include "QDateTime"
#include <iostream>
#include <chrono>

PhysicsEngine::PhysicsEngine()
{
}

void PhysicsEngine::run()
{
    const float fps = 60;
    const float dt = 1 / fps;
    float accumulator = 0;

    std::chrono::time_point<std::chrono::system_clock> chrono_start, chrono_current;

    // In units seconds
    chrono_start = std::chrono::system_clock::now();

    // main loop
    while(true)
    {
      chrono_current = std::chrono::system_clock::now();

      // Store the time elapsed since the last frame began
      accumulator += (chrono_current - chrono_start).count();

      // Record the starting of this frame
      chrono_start = chrono_current;

      // Avoid spiral of death and clamp dt, thus clamping
      // how many times the UpdatePhysics can be called in
      // a single game loop.
      if(accumulator > 0.2f)
      {
        accumulator = 0.2f;
      }

//      std::cout << "accumulator : " << accumulator << std::endl;
//      std::cout << "dt : " << dt << std::endl << std::endl;

      while(accumulator > dt)
      {
        updatePhysics( dt );
        accumulator -= dt;
      }
    }
}

void PhysicsEngine::updatePhysics(float dt)
{
    printf("On update la physic !\n");
}
