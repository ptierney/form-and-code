
#include <cinder/app/AppBasic.h>

class Superformula : public ci::app::AppBasic {
public:
    void prepareSettings(Settings* settings);
    void setup();
    void draw();

private:
    std::vector<ci::Vec2f> superformula(float m, float n1, float n2, float n3);
    ci::Vec2f superformulaPoint(float m, float n1, float n2, float n3, float phi);

    float scaler;
    int m;
    float n1;
    float n2;
    float n3;
};

void Superformula::prepareSettings(Settings* settings) {
    scaler = 200.0f;
    m = 2;
    n1 = 18;
    n2 = 1;
    n3 = 1;
    settings->setWindowSize(700, 700);
}

void Superformula::setup() {
    glEnable(GL_SMOOTH);
    ci::gl::color(ci::Color::white());
}

void Superformula::draw() {
    ci::gl::setMatricesWindow(getWindowSize());
    ci::gl::clear(ci::Color::black());

    ci::gl::pushMatrices();
    ci::gl::translate(ci::Vec2f(getWindowWidth()/2, getWindowHeight()/2));

    float newscaler = scaler;
    for (int s = 16; s > 0; s--) {
        glBegin(GL_LINE_STRIP);

        float mm = m + s;
        float nn1 = n1 + s;
        float nn2 = n2 + s;
        float nn3 = n3 + s;
        newscaler = newscaler * 0.98;
        float sscaler = newscaler;

        std::vector<ci::Vec2f> points = superformula(mm, nn1, nn2, nn3);
        glVertex2f(points[points.size()-1].x * sscaler, points[points.size()-1].y * sscaler);
        std::for_each(points.begin(), points.end(), [sscaler](ci::Vec2f vec) { glVertex2f(vec.x * sscaler, vec.y * sscaler); });
        glVertex2f(points[points.size()-1].x * sscaler, points[points.size()-1].y * sscaler);

        glEnd();
    }
    ci::gl::popMatrices();
}

std::vector<ci::Vec2f> Superformula::superformula(float m, float n1, float n2, float n3) {
    int numPoints = 360;
    float phi = 2.0f * M_PI / numPoints;
    std::vector<ci::Vec2f> points;
    for (int i = 0; i <= numPoints; i++) {
        points.push_back(superformulaPoint(m,n1,n2,n3,phi * i));
    }
    return points;
}

ci::Vec2f Superformula::superformulaPoint(float m, float n1, float n2, float n3, float phi) {
    float r;
    float t1,t2;
    float a=1,b=1;
    float x = 0;
    float y = 0;

    t1 = ci::math<float>::cos(m * phi / 4) / a;
    t1 = ci::math<float>::abs(t1);
    t1 = ci::math<float>::pow(t1,n2);

    t2 = ci::math<float>::sin(m * phi / 4) / b;
    t2 = ci::math<float>::abs(t2);
    t2 = ci::math<float>::pow(t2,n3);

    r = ci::math<float>::pow(t1+t2,1/n1);
    if (ci::math<float>::abs(r) == 0) {
        x = 0;
        y = 0;
    }
    else {
        r = 1 / r;
        x = r * ci::math<float>::cos(phi);
        y = r * ci::math<float>::sin(phi);
    }

    return ci::Vec2f(x, y);
}

CINDER_APP_BASIC(Superformula, ci::app::RendererGl)
