#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

struct Bullet {
  olc::vf2d position;
  olc::vf2d velocity;
  Bullet(float x, float y, float dx, float dy) {
    position.x = x;
    position.y = y;
    velocity.x = dx;
    velocity.y = dy;
  }
};
struct weapon {
  olc::vf2d position;
  olc::vf2d velocity;
  weapon(float x, float y, float dx, float dy) {
    position.x = x;
    position.y = y;
    velocity.x = dx;
    velocity.y = dy;
  }
};
struct Shooter {
  olc::vf2d position;
  olc::vf2d velocity;
  float fireRate;
  int fireCount;
  float timer;
  Shooter(float x, float y, float dx, float dy, float fr, int fc) {
    position.x = x;
    position.y = y;
    velocity.x = dx;
    velocity.y = dy;
    fireRate = fr;
    fireCount = fc;
    timer = 1.0f / fr;
  }
};

class Game : public olc::PixelGameEngine {
 public:
  Game() { sAppName = "Insert Game Name Here"; }

 private:
  float timer = 0;
  int frames = 0;
  int fps;

  std::vector<Bullet> bullets;
  std::vector<weapon> plasma;
  std::vector<Shooter> shooters;
  float shooterSpawnTimer = 0;
  float weaponSpawnTimer = 0;

  olc::vf2d shipPosition{WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100};
  olc::vf2d shipVelocity{0, 0};
  olc::vf2d shipAcceleration;

  float acceleration = 3000;
  float deceleration = 7.5;
  float maxSpeed = 1000;

  bool shipAlive = true;
  float explosionTimer = 0;
  int explosionFrames = 25;
  int explosionFrameRate = 20;

  void addBullets(int count, olc::vf2d start) {
    const float TWO_PI = 2 * 3.14159265;
    float offset = TWO_PI * (float)rand() / RAND_MAX;
    for (auto i = 0; i < count; i++) {
      bullets.push_back(Bullet(start.x, start.y,
                               100 * cos(TWO_PI * (float)i / count + offset),
                               100 * sin(TWO_PI * (float)i / count + offset)));
    }
  }
//++++++++++++++++++++++++++++

 void addwapon(int count, olc::vf2d start) {
    for (auto i = 0; i < count; i++) {
      plasma.push_back(weapon(start.x, start.y, 0,-400));
    }
  }
//++++++++++++++++++++++++++++++
  olc::Sprite* backgroundSprite;
  olc::Decal* backgroundDecal;

  olc::Sprite* plasmaSprite;
  olc::Decal* plasmaDecal;

  olc::Sprite* bulletSprite;
  olc::Decal* bulletDecal;

  olc::Sprite* shooterSprite;
  olc::Decal* shooterDecal;

  olc::Sprite* shipSprite;
  olc::Decal* shipDecal;

  olc::Sprite* explosionSprite;
  olc::Decal* explosionDecal;

 public:
  bool OnUserCreate() override {
    /*
      Load resources here
    */

    backgroundSprite = new olc::Sprite("background.png");
    backgroundDecal = new olc::Decal(backgroundSprite);

    plasmaSprite = new olc::Sprite("plasma.png");
    plasmaDecal = new olc::Decal(plasmaSprite);

    bulletSprite = new olc::Sprite("bullet.png");
    bulletDecal = new olc::Decal(bulletSprite);

    shooterSprite = new olc::Sprite("shooter.png");
    shooterDecal = new olc::Decal(shooterSprite);

    shipSprite = new olc::Sprite("ship.png");
    shipDecal = new olc::Decal(shipSprite);

    explosionSprite = new olc::Sprite("explosion.png");
    explosionDecal = new olc::Decal(explosionSprite);

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override {

    // game update
    timer += fElapsedTime;
    frames++;
    if (timer > 1.0) {
      fps = frames;
      frames = 0;
      timer -= 1;
      std::cout << shooters.size() << " shooters. " << bullets.size()
                << " bullets." << plasma.size()<< "plasmaes." <<std::endl;
    }

    olc :: vf2d {shipPosition.y,shipPosition.x} ;



    shooterSpawnTimer -= fElapsedTime;
    if (shooterSpawnTimer < 0) {
      shooterSpawnTimer += 2;
      shooters.push_back(Shooter((float)rand() / RAND_MAX * WINDOW_WIDTH, -20,0, 50, 0.25, 10));
      
    }

    weaponSpawnTimer -= fElapsedTime;

    inputs();
    processes(fElapsedTime);
    outputs();

    //DrawSprite(olc::vf2d {shipPosition.y,shipPosition.x},plasmaSprite);

    if (GetKey(olc::Key::ESCAPE).bPressed) {
      return false;
    } else {
      return true;
    }
  }

  void inputs() {
    /*
      Game controls goes here
    */

    shipAcceleration.x = 0;
    shipAcceleration.y = 0;
    if (GetKey(olc::Key::LEFT).bHeld) shipAcceleration.x -= acceleration;
    if (GetKey(olc::Key::RIGHT).bHeld) shipAcceleration.x += acceleration;
    if (GetKey(olc::Key::UP).bHeld) shipAcceleration.y -= acceleration;
    if (GetKey(olc::Key::DOWN).bHeld) shipAcceleration.y += acceleration;

   /**/ if (GetKey(olc::Key::R).bPressed) {
      shipAlive = true;
      shipVelocity = olc::vf2d{0, 0};
      shipPosition = olc::vf2d{WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100};
      explosionTimer = 0;
    }

    if (GetMouse(0).bHeld) {
      std::cout << "Click!" << std::endl;
    }
  }

  void processes(float fElapsedTime) {
    /*
      Game logic goes here
    */

    if (shipAlive == true) {
      shipVelocity += fElapsedTime * shipAcceleration;

      shipVelocity *= 1 - fElapsedTime * deceleration;

      if (shipVelocity.x < -maxSpeed) shipVelocity.x = -maxSpeed;
      if (shipVelocity.y < -maxSpeed) shipVelocity.y = -maxSpeed;
      if (shipVelocity.x > maxSpeed) shipVelocity.x = maxSpeed;
      if (shipVelocity.y > maxSpeed) shipVelocity.y = maxSpeed;


      //if (GetKey(olc::Key::W).bHeld) {
        olc::vf2d start{shipPosition.x,shipPosition.y};
  
        addwapon(1,start);

      //};

      shipPosition += fElapsedTime * shipVelocity;

      if (shipPosition.x < 25) {
        shipPosition.x = 25;
        shipVelocity.x = 0;
      }
      if (shipPosition.y < 25) {
        shipPosition.y = 25;
        shipVelocity.y = 0;
      }
      if (shipPosition.x > ScreenWidth() - 25) {
        shipPosition.x = ScreenWidth() - 25;
        shipVelocity.x = 0;
      }
      if (shipPosition.y > ScreenHeight() - 25) {
        shipPosition.y = ScreenHeight() - 25;
        shipVelocity.y = 0;
      }
    //} 
    else {
      explosionTimer += fElapsedTime;
    }

    for (auto& bullet : bullets) {
      bullet.position += fElapsedTime * bullet.velocity;
    }

    for (auto& weapon : plasma) {
      weapon.position += fElapsedTime * weapon.velocity;
    }

    for (auto i = 0; i < bullets.size();) {
      bool shipHit = pow(shipPosition.x - bullets[i].position.x, 2) +
                         pow(shipPosition.y - bullets[i].position.y, 2) <
                     pow(25, 2);

      if (shipHit) shipAlive = false;

      if (shipHit || bullets[i].position.x < -20 ||
          bullets[i].position.y < -20 ||
          bullets[i].position.x > WINDOW_WIDTH + 20 ||
          bullets[i].position.y > WINDOW_HEIGHT + 20) {
        bullets.erase(bullets.begin() + i);
      } else {
        i++;
      }
    }

    for (auto& shooter : shooters) {
      shooter.position += fElapsedTime * shooter.velocity;
      shooter.timer -= fElapsedTime;
      if (shooter.timer < 0) {
        shooter.timer += 1.0f / shooter.fireRate;
        addBullets(shooter.fireCount, shooter.position);
      }
    }


    for (auto i = 0; i < plasma.size();) {
      bool shooterHit = false;

      for (auto j = 0; j < shooters.size();) {
        shooterHit =
            pow(shooters[j].position.x - plasma[i].position.x, 2) +
                pow(shooters[j].position.y - plasma[i].position.y, 2) <
            pow(25, 2);
        if (shooterHit) {
          shooters.erase(shooters.begin() + j);
          break;
        } else {
          j++;
        }
      }

      if (shooterHit || plasma[i].position.x < -20 ||
          plasma[i].position.y < -20 ||
          plasma[i].position.x > WINDOW_WIDTH + 20 ||
          plasma[i].position.y > WINDOW_HEIGHT + 20) {
        plasma.erase(plasma.begin() + i);
      } else {
        i++;
      }

     }
     for (auto i = 0; i < shooters.size();) {
        if ((shooters[i].position.x < -20 || shooters[i].position.y < -20 || shooters[i].position.x > WINDOW_WIDTH + 20 ||
             shooters[i].position.y > WINDOW_HEIGHT + 20 )  ) {
            shooters.erase(shooters.begin() + i); 
        } else {
          i++;
       }
      }
    }
  }
  

  void outputs() {
    SetPixelMode(olc::Pixel::NORMAL);

    /*
      Game graphics drawn here
    */

    DrawDecal(olc::vf2d(0, 0), backgroundDecal);

    // draw bullets

    float scale = 0.0333;
    auto centrePoint = scale * olc::vf2d{(float)bulletSprite->width / 2,
                                         (float)bulletSprite->height / 2};

    for (const auto& bullet : bullets) {
      DrawDecal(bullet.position - centrePoint, bulletDecal,
                olc::vf2d{scale, scale});
    }

    // draw bullet

    // draw shooter //

    scale = 0.0333;
    centrePoint = scale * olc::vf2d{(float)shooterSprite->width / 2,
                                    (float)shooterSprite->height / 2};

    for (const auto& shooter : shooters) {
      DrawDecal(shooter.position - centrePoint, shooterDecal,
                olc::vf2d{scale, scale});
    }

    // draw shooter //

    // draw plasma //

    scale = 0.0333;
    centrePoint = scale * olc::vf2d{(float)shipSprite->width / 2,
                                    (float)shipSprite->height / 2};

    for (const auto& weapon : plasma) {
      DrawDecal(weapon.position - centrePoint, plasmaDecal,
                olc::vf2d{scale, scale});
    }

    // draw plasma //


    // check collision //

    if (shipAlive) {
      scale = 1;
      centrePoint = scale * olc::vf2d{(float)shipSprite->width / 2,
                                      (float)shipSprite->height / 2};

      DrawDecal(shipPosition - centrePoint, shipDecal, olc::vf2d{scale, scale});

    } else if (explosionTimer < explosionFrames / explosionFrameRate) {
      float explosionSize = (float)explosionSprite->width / explosionFrames;
      int explosionFrame = explosionTimer * explosionFrameRate;
      centrePoint = olc::vf2d{explosionSize / 2, explosionSize / 2};

      DrawPartialDecal(shipPosition - centrePoint,
                       olc::vf2d{explosionSize, explosionSize}, explosionDecal,
                       olc::vf2d{explosionFrame * explosionSize, 0},
                       olc::vf2d{explosionSize, explosionSize});
    }

    if (fps > 0) {
      auto fpsPosition = olc::vi2d(WINDOW_WIDTH - 70, WINDOW_HEIGHT - 70);
      DrawStringDecal(fpsPosition, "FPS " + std::to_string(fps));
    }

    
  }

  bool OnUserDestroy() override {
    std::cout << "Closing game" << std::endl;
    return true;
  }
};

// game main function //
int main() {
  Game game;
  if (game.Construct(WINDOW_WIDTH, WINDOW_HEIGHT, 1, 1)) game.Start();
  return 0;
}
