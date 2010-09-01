
#include <cinder/app/AppBasic.h>

class Particle;

class Particles : public ci::app::AppBasic {
public:
  void prepareSettings(Settings* settings);
  void setup();
  void update();
  void draw();

  static float map(float val, float inMin, float inMax, float outMin, float outMax);
}


private:
  std::vector<Particle> particles;
  bool saving;
};

class Particle {
public:
  Particle(ci::Vec2f l) {
    counter = 0;

    float randmin = -M_PI / 2.0f;
    float randmax = 0;
    
    float r = ci::Rand::randFloat(0, M_PI * 2.0f);
    float x = ci::math<float>::cos(r);
    float y = ci::math<float>::sin(r);
    acc = ci::Vec2f(x / 250, y / 250);
    
    float q = ci::Rand::randFloat(0, 1);
    x = ci::math::<float>::cos(r) * q;
    y = ci::math::<float>::sin(r) * q;
    vel = ci::Vec2f(x, y);
    loc = l;
    hist.resize(1000);
  }
  
  void update() {
    vel += acc;
    loc += vel;
    // save location every 10 frames
    if (frame % 10 == 0 && counter < hist.size()) {
      hist.push_back(loc);      
    }
  }

  void drawArrowHead(ci::Vec2f v, ci::Vec2f loc, float scale) {
    ci::gl::pushMatricies();
    float arrowsize = 4;
    // Translate to location to render vector
    ci::gl::translate(loc.x, loc.y);
    
    // rotate to heading
    ci::gl::rotate(0.0f, 0.0f, v.heading2D());
    
    // Calculate length of vector & scale it to be bigger or smaller if necessary
    float len = v.mag()*scale;
    arrowsize = Particles::map(len, 0, 10, 0, 1) * arrowsize;

    // Draw point
    
    
  }

  void draw() {
    float c = 100.0f/255.0f;
    glColor4f(c, c, c, 50.0f/255.0f);
    drawArrowHead(vel,loc,10);

  }

private:
  ci::Vec2f loc;
  ci::Vec2f vel;
  ci::Vec2f acc;
  
  std::vector<ci::Vec2f> hist;
  int counter;

};

float Particles::map(float val, float inMin, float inMax, float outMin, float outMax) {
    return outMin + (outMax - outMin) * ((val - inMin) / (inMax - inMin));
}
