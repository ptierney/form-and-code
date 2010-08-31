
#include <vector>

#include <cinder/app/AppBasic.h>
#include <cinder/ImageIo.h>
#include <cinder/Camera.h>
#include <cinder/MayaCamUI.h>
#include <cinder/CinderResources.h>

class Transform : public ci::app::AppBasic {
public:
    void prepareSettings(Settings* settings);
    void setup();
    void draw();

    void mouseDown(ci::app::MouseEvent);
    void mouseDrag(ci::app::MouseEvent);

private:
    ci::Surface img;
    std::vector<std::vector<int> > values;
    float angle;

    ci::MayaCamUI cam;
    float far_clip;

    int width;
    int height;
};

void Transform::prepareSettings(Settings* settings) {
    width = 1024;
    height = 768;
    far_clip = 10000.0f;
    angle = 0.0f;
    settings->setWindowSize(width, height);
}

void Transform::setup() {
    glEnable(GL_SMOOTH);

    ci::CameraPersp new_cam = cam.getCamera();
    new_cam.setFarClip(far_clip);
    new_cam.setEyePoint(ci::Vec3f(width/2, height/2, -600.0f));
    cam.setCurrentCam(new_cam);

    img = ci::loadImage("/projects/cinder/nasa-iceberg.jpg");

    ci::Surface::Iter it = img.getIter();

    values.resize(img.getWidth());

    for (std::vector<std::vector<int> >::iterator it = values.begin(); it != values.end(); ++it) {
        it->resize(img.getHeight());
    }

    int i = 0;
    while(it.line()) {
        int j = 0;
		while(it.pixel()) {
            ci::Color c = ci::Color(it.r(), it.g(), it.b());
            values[j][i] = c.get(ci::ColorModel::CM_HSV)[2];
            j++;
		}
        i++;
	}
}

void Transform::draw() {
    ci::gl::setMatricesWindow(getWindowSize());
    ci::gl::setMatrices(cam.getCamera());
    ci::gl::clear(ci::Color().black());                  // Set black background
    ci::gl::translate(ci::Vec3f(width/2, height/2, 0));  // Move to the center
    ci::gl::scale(ci::Vec3f(4.0f, 4.0f, 4.0f));          // Scale to 400%
    
    // Update the angle
    angle += ci::toDegrees(0.005f);
    ci::gl::rotate(ci::Vec3f(0.0f, angle, 0.0f));

    // Display the image mass
    for (int i = 0; i < img.getHeight(); i += 2) {
        for (int j = 0; j < img.getWidth(); j += 2) {
            float cf = (float)(values[j][i]) / 255.0f;
            glColor4f(cf, cf, cf, 153.0f/255.0f);
            float x1 = j-img.getWidth()/2;
            float y1 = i-img.getHeight()/2;
            float z1 = -values[j][i]/2;
            float x2 = j-img.getWidth()/2;
            float y2 = i-img.getHeight()/2;
            float z2 = -values[j][i]/2-4;
            ci::gl::drawLine(ci::Vec3f(x1, y1, z1), ci::Vec3f(x2, y2, z2));
        }
    }
}

void Transform::mouseDown(ci::app::MouseEvent event) {
    cam.mouseDown(event.getPos());
}

void Transform::mouseDrag(ci::app::MouseEvent event) {
    cam.mouseDrag(event.getPos(), event.isLeftDown(), event.isMiddleDown(), 
        event.isRightDown());
}

CINDER_APP_BASIC(Transform, ci::app::RendererGl)
