//
//  PolyShape.h
//  rorschach
//
//  Created by 市川 on 2015/11/26.
//
//

#pragma once

#include <stdio.h>
#include "ofMain.h"

class PolyShape {
    
    public:
    PolyShape();
        PolyShape(float x, float y, float radius, float randSeed, ofColor color);
        ~PolyShape();
        
        void setup();
        void update(ofPoint center);
        void drawLine();
        void drawFilled();
        void debugDraw();
        void setSmoothParm(int param);
        ofPoint getCenter();
    
    private:
        ofPolyline polyline;
        ofPath path;
        ofColor mColor;
        vector<ofPoint> mVts;
        vector<ofPoint> mBaseVts;
        ofPoint mCenter;
        float mRadius;
        float mMaxDist;
        float mRandSeed;
        int mSmoothParam;
};
