#pragma once

#include "ofMain.h"
#include "PolyShape.h"
#include "Gui.h"
#include "ofxInkSim.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void drawIntoFbo();
        void reset();
        void refresh(ofxButton & tapped);
    
        Gui gui;
    
        vector<PolyShape> polyshapes;
    
        bool isDebug = false;
    
        ofRectangle fboBound;
        ofRectangle polyBound;

        ofFbo fbo;
    
        int numPolyShape;
    
        // ofxButton called twice, so...
        bool bOnlyOnce;
    
    
        bool isGrayScale;
    
        ofxInkSim inkSim;
};
