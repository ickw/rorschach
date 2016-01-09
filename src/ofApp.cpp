#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetBackgroundColor(255);
    ofSetCircleResolution(60);
    ofSetWindowTitle("Rorschach");
    
    ofEnableAlphaBlending();
    
    // Gui
    gui.setup();
    ofAddListener(gui.refreshBtnTapped, this, &ofApp::refresh); // Gui Event Listener
    bOnlyOnce = false;
    
    // Grayscale flag
    isGrayScale = gui.getIsGrayScale();

    // Number of PolyShape
    numPolyShape = gui.getNumShapes();
    
    // PolyShape
    float bx = 200;
    float by = 150;
    float bw = gui.getBound().x;
    float bh = gui.getBound().y;
    float minRad = gui.getRadiusRange().x;
    float maxRad = gui.getRadiusRange().y;
    float minSeed = gui.getNoiseSeedRange().x;
    float maxSeed = gui.getNoiseSeedRange().y;
    float minRed = gui.getRedColorRange().x;
    float maxRed = gui.getRedColorRange().y;
    float minGreen = gui.getGreenColorRange().x;
    float maxGreen = gui.getGreenColorRange().y;
    float minBlue = gui.getBlueColorRange().x;
    float maxBlue = gui.getBlueColorRange().y;
    int   smoothParam = gui.getSmoothParam();
    polyBound = ofRectangle(bx, by, bw, bh);
    fboBound = ofRectangle(0, 0, bx+bw, ofGetHeight());
    
    
    for (int i=0; i<numPolyShape; i++) {
        PolyShape *p = new PolyShape(ofRandom(polyBound.getX(), polyBound.getX()+polyBound.getWidth()), ofRandom(polyBound.getY(), polyBound.getY()+polyBound.getHeight()), ofRandom(minRad, maxRad), ofRandom(minSeed, maxSeed), ofColor(ofRandom(minRed, maxRed), ofRandom(minGreen, maxGreen), ofRandom(minBlue, maxBlue)));
        
        p->setSmoothParm(smoothParam);
        
        polyshapes.push_back(*p);
        
    }
    
    // Fbo
    //fbo.allocate(fboBound.getWidth(), fboBound.getHeight(), GL_RGBA32F_ARB, 8);
    fbo.allocate(fboBound.getWidth(), fboBound.getHeight());
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();
    
    
    // InkSim
    inkSim.setup();
    inkSim.setDrawMode(ofxInkSim::INKFIX);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i=0; i<numPolyShape; i++) {
        polyshapes.at(i).update(polyshapes.at(i).getCenter());
    }
    
    isDebug = gui.getIsDebug();
    
    drawIntoFbo();
    
    // InkSim
    inkSim.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // To Draw Original
    /*
    for (int i=0; i<NUM_POLYSHAPE; i++) {
        polyshapes.at(i).drawFilled();
        
        if (isDebug) {
            ofSetColor(0, 255, 0);
            polyshapes.at(i).drawLine();
            
            ofSetColor(255, 0, 0);
            polyshapes.at(i).debugDraw();
        }
    }
     */
    
    
    // Draw Fbos
    inkSim.begin();
    
    ofSetColor(255, 255);
    fbo.draw(0, 0, fboBound.getWidth(), fboBound.getHeight()); // left
    float _fx = fboBound.getX() + fboBound.getWidth();
    fbo.draw(_fx*2, 0, -fboBound.getWidth(), fboBound.getHeight()); // right
    
    inkSim.end();
    

    inkSim.draw();

    
    
    // Debug visuals
    if(isDebug) {
        ofSetLineWidth(2.f);
        ofSetColor(255, 255, 0);
        ofNoFill();
        ofDrawRectangle(polyBound.getX(), polyBound.getY(), polyBound.getWidth(), polyBound.getHeight());
        
        ofSetColor(0, 255, 255);
        ofDrawRectangle(fboBound.getX(), fboBound.getY(), fboBound.getWidth(), fboBound.getHeight());
    }
    
    
    // Gui
    gui.draw();
}

void ofApp::drawIntoFbo() {
    fbo.begin();
    {
        ofClear(255, 255, 255, 0);
        for (int i=0; i<numPolyShape; i++) {
            polyshapes.at(i).drawFilled();
            
            if (isDebug) {
                ofSetColor(0, 255, 0);
                polyshapes.at(i).drawLine();
                
                ofSetColor(255, 0, 0);
                polyshapes.at(i).debugDraw();
                
            }
        }
    }
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::reset() {
    
    inkSim.clear();
    
    numPolyShape = gui.getNumShapes();
    
    isGrayScale = gui.getIsGrayScale();
    
    float bx = 200;
    float by = 150;
    float bw = gui.getBound().x;
    float bh = gui.getBound().y;
    float minRad = gui.getRadiusRange().x;
    float maxRad = gui.getRadiusRange().y;
    float minSeed = gui.getNoiseSeedRange().x;
    float maxSeed = gui.getNoiseSeedRange().y;
    float minRed = gui.getRedColorRange().x;
    float maxRed = gui.getRedColorRange().y;
    float minGreen = gui.getGreenColorRange().x;
    float maxGreen = gui.getGreenColorRange().y;
    float minBlue = gui.getBlueColorRange().x;
    float maxBlue = gui.getBlueColorRange().y;
    int   smoothParam = gui.getSmoothParam();
    polyBound = ofRectangle(bx, by, bw, bh);
    fboBound = ofRectangle(0, 0, bx+bw, ofGetHeight());
    
    fbo.clear();
    fbo.allocate(fboBound.getWidth(), fboBound.getHeight(), GL_RGBA32F_ARB, 8);
    fbo.begin();
    ofClear(255, 255, 255, 0);
    fbo.end();
    
    polyshapes.clear();
    for (int i=0; i<numPolyShape; i++) {
        
        if (isGrayScale)
        {
            PolyShape *p = new PolyShape(ofRandom(polyBound.getX(), polyBound.getX()+polyBound.getWidth()), ofRandom(polyBound.getY(), polyBound.getY()+polyBound.getHeight()), ofRandom(minRad, maxRad), ofRandom(minSeed, maxSeed), ofColor(ofRandom(minRed, maxRed)));
            
            p->setSmoothParm(smoothParam);
            
            polyshapes.push_back(*p);
            
        }
        else
        {
            PolyShape *p = new PolyShape(ofRandom(polyBound.getX(), polyBound.getX()+polyBound.getWidth()), ofRandom(polyBound.getY(), polyBound.getY()+polyBound.getHeight()), ofRandom(minRad, maxRad), ofRandom(minSeed, maxSeed), ofColor(ofRandom(minRed, maxRed), ofRandom(minGreen, maxGreen), ofRandom(minBlue, maxBlue)));
            
            p->setSmoothParm(smoothParam);
            
            polyshapes.push_back(*p);
        }
    }
}

void ofApp::refresh(ofxButton &tapped) {
    bOnlyOnce = !bOnlyOnce;
    if (bOnlyOnce) {
        reset();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'c')
    {
        inkSim.clear();
    }
    else if (key == '1')
    {
        inkSim.setDrawMode(ofxInkSim::INKFIX);
    }
    else if (key == '2')
    {
        inkSim.setDrawMode(ofxInkSim::INKSURF);
    }
    else if (key == '3')
    {
        inkSim.setDrawMode(ofxInkSim::INKFLOW);
    }
    else if (key == '4')
    {
        inkSim.setDrawMode(ofxInkSim::WATERFLOW);
    }
    else if (key == 'd')
    {
        inkSim.toggleDebug();
    }
}



//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
