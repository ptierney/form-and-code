/**
 * Parameterize: Chair from Form+Code in Art, Design, and Architecture
 * implemented in C++ by Patrick Tierney (patrick.l.tierney@gmail.com)
 *
 * Requires Cinder 0.8.2 available at http://libcinder.org
 *
 * Project files are located at https://github.com/hlp/form-and-code
 *
 * For more information about Form+Code visit http://formandcode.com
 */

#include <boost/date_time.hpp>

#include <cinder/gl/gl.h>
#include <cinder/app/AppBasic.h>
#include <cinder/Rand.h>

class Chair : public ci::app::AppBasic {
public:
    void prepareSettings(Settings* settings);
    void setup();
    void draw();

    void drawChair();
    void scrambleChair();

    void mouseDown(ci::app::MouseEvent);

private:
    int chairSeatHeight;
    int chairWidth;
    int chairDepth;
    int chairBackHeight;
    int chairFrameThickness;

    ci::Rand rand;
};

void Chair::prepareSettings(Settings* settings) {
    settings->setWindowSize(1024, 1024);
}

void Chair::setup() {
    chairSeatHeight = 100;
    chairWidth = 50;
    chairDepth = 50;
    chairBackHeight = 100;
    chairFrameThickness = 10;

    boost::posix_time::ptime epoch(boost::gregorian::date(1970,1,1));
    boost::posix_time::ptime now(boost::posix_time::second_clock::universal_time());
    unsigned int seed = (now - epoch).total_seconds();
        
    rand.seed(seed);

    scrambleChair();

    ci::gl::color(ci::Color::black());
}

void Chair::draw() {
    ci::gl::clear(ci::Color::white());
    // set to orthographic. how do you do this in Cinder ?

    ci::gl::pushMatrices();
    ci::gl::translate(ci::Vec2f(getWindowWidth(), getWindowHeight()));
    ci::gl::rotate(ci::Vec3f(-M_PI / 9.f, M_PI / 8.f, 0.f));

    drawChair();
    ci::gl::popMatrices();
}

void Chair::drawChair() {
    // back
    ci::gl::pushMatrices();
    ci::gl::translate(ci::Vec3f(chairWidth/2, chairBackHeight/2, 0.f));
    ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(chairWidth, chairBackHeight, 
        chairFrameThickness));
    ci::gl::popMatrices();
    
    // seat
    ci::gl::pushMatrices();
    ci::gl::translate(ci::Vec3f(chairWidth/2, chairBackHeight + 
        chairFrameThickness/2, chairDepth/2 - chairFrameThickness/2));
    ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(chairWidth, chairFrameThickness, 
        chairDepth));
    ci::gl::popMatrices();
   
    // legs
    ci::gl::pushMatrices();
    ci::gl::translate(ci::Vec3f(chairFrameThickness/2, chairBackHeight + 
        chairSeatHeight/2 + chairFrameThickness, 0));
    ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(chairFrameThickness, 
        chairSeatHeight, chairFrameThickness));
    ci::gl::popMatrices();

    ci::gl::pushMatrices();
    ci::gl::translate(ci::Vec3f(chairWidth - chairFrameThickness/2, 
        chairBackHeight + chairSeatHeight/2 + chairFrameThickness, 0));
    ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(chairFrameThickness, 
        chairSeatHeight, chairFrameThickness));
    ci::gl::popMatrices();

    ci::gl::pushMatrices();
    ci::gl::translate(ci::Vec3f(chairWidth - chairFrameThickness/2, 
        chairBackHeight + chairSeatHeight/2 + chairFrameThickness, 
        chairDepth - chairFrameThickness));
    ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(chairFrameThickness, 
        chairSeatHeight, chairFrameThickness));
    ci::gl::popMatrices();

    ci::gl::pushMatrices();
    ci::gl::translate(ci::Vec3f(chairFrameThickness/2, chairBackHeight + 
        chairSeatHeight/2 + chairFrameThickness, chairDepth - chairFrameThickness));
    ci::gl::drawCube(ci::Vec3f::zero(), ci::Vec3f(chairFrameThickness, 
        chairSeatHeight, chairFrameThickness));
    ci::gl::popMatrices();
}

void Chair::scrambleChair() {
    chairSeatHeight = rand.randInt(10, 200);
    chairWidth = rand.randInt(10, 200);
    chairDepth = rand.randInt(10, 200);
    chairBackHeight = rand.randInt(10, 200);
}

void Chair::mouseDown(ci::app::MouseEvent /*event*/) {
    scrambleChair();
}

CINDER_APP_BASIC(Chair, ci::app::RendererGl)
