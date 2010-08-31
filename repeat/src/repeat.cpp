
#include <cinder/app/AppBasic.h>
#include <cinder/CinderMath.h>

class Repeat : public ci::app::AppBasic {
public:
  void prepareSettings(Settings* settings);
  void setup();
  void draw();

  void mouseDown(ci::app::MouseEvent);

private:
  void arc(const ci::Vec2f& center, float radius, float start, float stop);
  float map(float val, float inMin, float inMax, float outMin, float outMax);

  int width;
  int height;
  int option;
};

void Repeat::prepareSettings(Settings* settings) {
  width = 400;
  height = 300;
  settings->setWindowSize(width, height);
}

void Repeat::setup() {
  option = 1;
  glEnable(GL_LINE_SMOOTH);
  glLineWidth(1.2f);
  ci::gl::color(ci::Color().black());
}

void Repeat::draw() {
  ci::gl::clear(ci::Color().white());

  if (option == 1) {
    // Option 1: Stitches
    for (int x = 50; x <= width-50; x += 20) {
      for (int y = 50; y <= height-50; y+=20) {
        ci::gl::drawLine(ci::Vec2f(x-5, y-5), ci::Vec2f(x+5, y+5));
        ci::gl::drawLine(ci::Vec2f(x+5, y-5), ci::Vec2f(x-5, y+5));
      }
    }
  }
  else if (option == 2) {
    // Option 2: Perspective
    for (int x = 50; x <= width-50; x += 20) {
      for (int y = 50; y <= height-50; y+=20) {
        ci::gl::drawLine(ci::Vec2f(x, y), ci::Vec2f(width/2, height/2));
      }
    }
  }
  else if (option == 3) {
    // Option 3: Overlapping circles
    for (int x = 50; x <= width-50; x += 20) {
      for (int y = 50; y <= height-50; y+=20) {
        ci::gl::drawStrokedCircle(ci::Vec2f(x, y), 40/2);
      }
    }
  }
  else if (option == 4) {
    // Option 4: Rotating arcs
    int count = 120;
    for (int x = 50; x <= width-50; x += 20) {
      for (int y = 50; y <= height-50; y +=20) {
        float s = map(count, 120, 0, 0, M_PI*2*2);
        arc(ci::Vec2f(x, y), 14/2, s, s + M_PI);
        count--;
      }
    }
  }
  else if (option == 5) {
    // Option 5: Groups of five
    for (int x = 50; x < width-50; x += 20) {
      for (int y = 50; y < height-50; y+=20) {
        //rect(x-10, y-10, 22, 22);
        for (int i = 0; i < 16; i+=4) {
          ci::gl::drawLine(ci::Vec2f(x + i, y), ci::Vec2f(x + i, y + 12));
        }
        ci::gl::drawLine(ci::Vec2f(x, y), ci::Vec2f(x + 12, y + 12));
      }
    }
  }
}

void Repeat::mouseDown(ci::app::MouseEvent /*event*/) {
  option++;
  if (option > 5) option = 1;
}

float Repeat::map(float val, float inMin, float inMax, float outMin, float outMax) {
    return outMin + (outMax - outMin) * ((val - inMin) / (inMax - inMin));
}

void Repeat::arc(const ci::Vec2f& center, float radius, float start, float stop) {
    // automatically determine the number of segments from the circumference
    int numSegments = (int) ci::math<double>::floor(radius * M_PI * 2);
    int startSegments = (int) ci::math<double>::floor(radius * start);
    int endSegments = (int) ci::math<double>::floor(radius * stop);

    if (numSegments < 2) numSegments = 2;
    int numVerts = (endSegments-startSegments)*2;
    if (numVerts < 2) numVerts = 2;
    GLfloat* verts = new float[numVerts];
    
    int i = 0;
    for(int s = startSegments; s < endSegments; s++) {
        float t = s / (float)numSegments * 2.0f * 3.14159f;
        verts[i*2+0] = center.x + ci::math<float>::cos(t) * radius;
        verts[i*2+1] = center.y + ci::math<float>::sin(t) * radius;
        i++;
    }
    
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, verts);
    glDrawArrays(GL_LINE_STRIP, 0, numVerts / 2);
    glDisableClientState(GL_VERTEX_ARRAY);

    delete [] verts;
}

CINDER_APP_BASIC(Repeat, ci::app::RendererGl)