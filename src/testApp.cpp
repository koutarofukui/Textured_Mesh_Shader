#include "testApp.h"

ofShader shader;
ofImage colormap, bumpmap;
ofMesh mainMesh;
ofImage texImage;

ofEasyCam	mCamMain;

ofTexture	mTexDepth;

ofFbo fbo;

int width = ofNextPow2(640);
int height = ofNextPow2(480);

float size = 0;
float color = 0;

void testApp::setup(){
    ofSetCircleResolution(60);
    
    ofDisableArbTex();
    shader.load("displace.vert", "displace.frag");
    fbo.allocate(width, height, GL_RGBA);
//    ofFbo::Settings settings;
//    settings.width = width;
//    settings.height = height;
//    settings.textureTarget = GL_TEXTURE_2D;
//    settings.useDepth = true;
//    settings.useStencil = true;
//    settings.depthStencilAsTexture = true;
//    fbo.allocate(settings);
    //texImage.loadImage("art.jpg");
    //texImage.resize(width, height);
    
    //printf("tex dim %0.f %0.f\n", texImage.getWidth(), texImage.getHeight());
    
    //mainMesh.setMode(OF_PRIMITIVE_POINTS);
    
    //    //add one vertex to the mesh for each pixel
    for (int y = 0; y < height; y++){
        for (int x = 0; x<width; x++){
            mainMesh.addVertex(ofPoint(x,y,0));   // mesh index = x + y*width
            mainMesh.addTexCoord(ofVec2f((float)x/float(width),(float)y/float(height)));
        }
    }
}


void testApp::update() {
    if (size < 500 ) {
        size += 1;
        if(color < 255)
        {
            color += 1;
        }else{
            color = 255;
        }
    }else{
        size = 0;
        color = 0;
    }
    
}
void testApp::draw(){
    ofBackground(128, 128, 128);
    //ofEnableDepthTest();
	// we don't care about alpha blending in this example, and by default alpha blending is on in openFrameworks > 0.8.0
	// so we de-activate it for now.
	//ofDisableAlphaBlending();
    ofDisableArbTex();
    
    //texture FBO
    fbo.begin();
        ofClear(0);
        ofBackground(0);
        ofSetColor(color);
        ofFill();
        ofCircle(width/2, height/2, size);
    fbo.end();
    
    ofEnableArbTex();
    
    mCamMain.begin();
    
        ofPushMatrix();
        ofScale(640/1024.0, 480/512.0);
            shader.begin();
                shader.setUniformTexture("colormap", fbo.getTextureReference(), 0);
                mainMesh.drawWireframe();
            shader.end();
        ofPopMatrix();
    
    mCamMain.end();
    
    ofDisableDepthTest();
    
    //display fbo texture
//    ofDisableAlphaBlending();
//    
//    fbo.draw(0, 0);
//    
//	ofSetColor(ofColor::white);
//
//	ofEnableAlphaBlending();
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
