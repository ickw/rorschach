//
//  PolyShape.cpp
//  rorschach
//
//  Created by 市川 on 2015/11/26.
//
//

#include "PolyShape.h"
#include "ofMath.h"


PolyShape::PolyShape() {
    
}

PolyShape::PolyShape(float x, float y, float radius, float randSeed, ofColor color) {
    mCenter.x = x;
    mCenter.y = y;
    mRadius = radius;
    mMaxDist = radius/6;
    mRandSeed = randSeed;
    mColor = color;
    mSmoothParam = 8;
    
    // TODO: Reduce num of vertices by using getSmoothed() method
    for (float a=0; a<360; a+=2) {
        float theta = ofDegToRad(a);
        float _x = mRadius * cos(theta);
        float _y = mRadius * sin(theta);
        mVts.push_back(ofPoint(_x, _y));
    }
    
    mBaseVts = mVts;
    
    polyline.addVertices(mVts);
    polyline.setClosed(true);
}

PolyShape::~PolyShape() {
    
}

void PolyShape::setup() {
    
}

void PolyShape::update(ofPoint center) {
    mCenter = center;
    
    for (int i=0; i<mVts.size(); i++) {
        ofVec2f _v = mVts.at(i);
        
        float _noise = ofSignedNoise(ofGetElapsedTimef() * mRandSeed, _v.x*0.01, _v.y*0.01);
        _v.normalize();
        
        ofVec2f _mom = _v*_noise;
        ofPoint _p = mVts.at(i)+_mom;
        float dist = ofVec2f(mBaseVts.at(i) - _p).length();
        
        if (dist > mMaxDist) _p = mVts.at(i)-_mom;
        
        
        mVts.at(i) = _p;
    }
    
    polyline.clear();
    polyline.addVertices(mVts);
    
    polyline = polyline.getSmoothed(mSmoothParam);
    
    polyline.setClosed(true);
    
    
}

void PolyShape::setSmoothParm(int param) {
    mSmoothParam = param;
}

void PolyShape::drawLine() {
    ofSetLineWidth(2.f);
    ofPushMatrix();
    ofTranslate(mCenter.x, mCenter.y);
    polyline.draw();
    ofPopMatrix();
}

void PolyShape::drawFilled() {
    ofSetColor(mColor);
    
    ofPushMatrix();
    ofTranslate(mCenter.x, mCenter.y);
    
    ofBeginShape();
    ofFill();
    for( int i = 0; i < polyline.getVertices().size(); i++) {
        ofVertex(polyline.getVertices().at(i).x, polyline.getVertices().at(i).y);
    }
    ofEndShape();
    
    ofPopMatrix();
}

void PolyShape::debugDraw() {
    ofNoFill();
    ofSetLineWidth(1.f);
    
    ofPushMatrix();
    ofTranslate(mCenter.x, mCenter.y);
    ofDrawCircle(0, 0, mRadius);
    ofDrawCircle(0, 0, mRadius - mMaxDist);
    ofDrawCircle(0, 0, mRadius + mMaxDist);
    ofPopMatrix();
}

ofPoint PolyShape::getCenter() {
    return mCenter;
}



