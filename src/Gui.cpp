//
//  Gui.cpp
//  rorschach
//
//  Created by 市川 on 2015/11/26.
//
//

#include "Gui.h"

Gui::Gui() {
    
}

Gui::~Gui() {
    
}

void Gui::setup() {
    gui.setup();
    
    gui.add(numShapes.setup("num_shapes", 40, 1, 40));
    
 	gui.add(bound.setup("bound", ofVec2f(700, 850), ofVec2f(100, 250), ofVec2f(700, 850)));
    gui.add(radiusRange.setup("radius_range", ofVec2f(5, 120), ofVec2f(3, 3), ofVec2f(200, 200)));
    gui.add(noiseSeedRange.setup("noise_seed_range", ofVec2f(0.01f, 1.0f), ofVec2f(0.001f, 0.001f), ofVec2f(5.f, 5.f)));
    
    gui.add(redColorRange.setup("red_color_range", ofVec2f(100, 255), ofVec2f(0, 0), ofVec2f(255, 255)));
    gui.add(greenColorRange.setup("green_color_range", ofVec2f(100, 255), ofVec2f(0, 0), ofVec2f(255, 255)));
    gui.add(blueColorRange.setup("blue_color_range", ofVec2f(100, 255), ofVec2f(0, 0), ofVec2f(255, 255)));
    
    gui.add(smoothParam.setup("smooth_param", 16, 2, 32));
    
    gui.add(isGrayScale.set("grayscale", false));
    
    gui.add(isDebug.set("is_debug", false));
    
    gui.add(fps.set("fps", ""));
    
    gui.add(refreshBtn.setup("REFRESH"));
    
}

void Gui::draw() {
    fps = ofToString(ofGetFrameRate());
    gui.draw();
    
    if (refreshBtn) {
        ofNotifyEvent(refreshBtnTapped, refreshBtn);
    }
}

int Gui::getNumShapes() {
    return numShapes;
}

ofVec2f Gui::getBound() {
    return bound;
}

ofVec2f Gui::getRadiusRange() {
    return radiusRange;
}

ofVec2f Gui::getNoiseSeedRange() {
    return noiseSeedRange;
}
ofVec2f Gui::getRedColorRange() {
    return redColorRange;
}

ofVec2f Gui::getGreenColorRange() {
    return greenColorRange;
}

ofVec2f Gui::getBlueColorRange() {
    return blueColorRange;
}

float Gui::getSmoothParam() {
    return smoothParam;
}

bool Gui::getIsGrayScale() {
    return isGrayScale;
}

bool Gui::getIsDebug() {
    return isDebug;
}

