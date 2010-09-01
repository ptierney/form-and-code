
#include <math.h>

#include <cinder/app/AppBasic.h>
#include <cinder/CinderMath.h>
#include <cinder/Rand.h>

class RecursiveTree : public ci::app::AppBasic {
public:
    void prepareSettings(Settings* settings);
    void setup();
    void draw();
    void seed1(float dotSize, float angle, float x, float y);
    void seed2(float dotSize, float angle, float x, float y);

private:
    int width;
    int height;
    float dotSize;
    float angleOffsetA;
    float angleOffsetB;
};

void RecursiveTree::prepareSettings(Settings* settings) {
    width = 900;
    height = 600;
    dotSize = 9;
    settings->setWindowSize(width, height);
    settings->setFrameRate(1.0f);  // Redraw the tree once a second
}

void RecursiveTree::setup() {
    ci::gl::color(ci::Color::black());
    glEnable(GL_SMOOTH);

    angleOffsetA = ci::toRadians(1.5f);
    angleOffsetB = ci::toRadians(50.0f);
}

void RecursiveTree::draw() {
    ci::gl::setMatricesWindow(getWindowSize());
    ci::gl::clear(ci::Color::white());              // White background
    ci::gl::translate(ci::Vec2f(width/2, height));   // Move to the center, bottom of the screen
    seed1(dotSize, ci::toRadians(270.0f), 0, 0);     // Start the tree
}

void RecursiveTree::seed1(float dotSize, float angle, float x, float y) {

    if (dotSize > 1.0) {

        // Create a random numbers between 0 and 1
        float r = ci::Rand::randFloat(0, 1.0f);  

        // 02% chance this will happen
        if (r > 0.02) {
            ci::gl::drawSolidCircle(ci::Vec2f(x, y), dotSize/2);
            float newx = x + cos(angle) * dotSize;
            float newy = y + sin(angle) * dotSize;
            seed1(dotSize * 0.99, angle - angleOffsetA, newx, newy);   
        }
        // 98% chance this will happen
        else {  
            ci::gl::drawSolidCircle(ci::Vec2f(x, y), dotSize/2);
            float newx = x + cos(angle);
            float newy = y + sin(angle);
            seed2(dotSize * 0.99, angle + angleOffsetA, newx, newy);
            seed1(dotSize * 0.60, angle + angleOffsetB, newx, newy);
            seed2(dotSize * 0.50, angle - angleOffsetB, newx, newy);
        } 
    }
}

void RecursiveTree::seed2(float dotSize, float angle, float x, float y) {

    if (dotSize > 1.0) {

        // Create a random numbers between 0 and 1
        float r = ci::Rand::randFloat(0, 1.0);

        // 5% chance this will happen
        if (r > 0.05) {
            ci::gl::drawSolidCircle(ci::Vec2f(x, y), dotSize/2);
            float newx = x + cos(angle) * dotSize;
            float newy = y + sin(angle) * dotSize;
            seed2(dotSize * 0.99, angle + angleOffsetA, newx, newy);
        } 
        // 95% chance this will happen
        else {
            ci::gl::drawSolidCircle(ci::Vec2f(x, y), dotSize/2);
            float newx = x + cos(angle);
            float newy = y + sin(angle);
            seed1(dotSize * 0.99, angle + angleOffsetA, newx, newy);  
            seed2(dotSize * 0.60, angle + angleOffsetB, newx, newy);
            seed1(dotSize * 0.50, angle - angleOffsetB, newx, newy);
        }
    }
}

CINDER_APP_BASIC(RecursiveTree, ci::app::RendererGl)
