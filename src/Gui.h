//
//  Gui.h
//  rorschach
//
//  Created by 市川 on 2015/11/26.
//
//


#pragma once

#include <stdio.h>
#include "ofMain.h"
#include "ofxGui.h"

class Gui {
    public:
        Gui();
        ~Gui();
        
        void setup();
        void draw();
        int  getNumShapes();
        ofVec2f getBound();
        ofVec2f getRadiusRange();
        ofVec2f getNoiseSeedRange();
        ofVec2f getRedColorRange();
        ofVec2f getGreenColorRange();
        ofVec2f getBlueColorRange();
        float   getSmoothParam();
        bool    getIsDebug();
        bool    getIsGrayScale();
    
        ofEvent<ofxButton> refreshBtnTapped;
    
    private:
        ofxPanel gui;
        ofxIntSlider  numShapes;
        ofxVec2Slider bound;
        ofxVec2Slider radiusRange;
        ofxVec2Slider noiseSeedRange;
        ofxVec2Slider redColorRange;
        ofxVec2Slider greenColorRange;
        ofxVec2Slider blueColorRange;
        ofxIntSlider  smoothParam;
        ofParameter<string>   fps;
        ofParameter<bool> isDebug;
        ofParameter<bool> isGrayScale;
        ofxButton refreshBtn;
    
};