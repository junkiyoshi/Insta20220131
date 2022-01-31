#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(280, 6);
	this->mesh = ico_sphere.getMesh();
	for (int index = 0; index < this->mesh.getNumVertices(); index++) {

		this->mesh.addColor(ofColor(0));
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	auto noise_min = 0.45;
	auto noise_max = 0.8;

	for (int index = 0; index < this->mesh.getNumVertices(); index++) {

		auto noise_value = ofNoise(this->mesh.getVertex(index).x * 0.0035, this->mesh.getVertex(index).y * 0.0035, this->mesh.getVertex(index).z * 0.02 + ofGetFrameNum() * 0.018);
		auto color_value = 255;
		if (noise_value > noise_min) {
		
			if (noise_value < noise_max) {

				color_value = ofMap(noise_value, noise_min, noise_max, 255, 0);
			}
			else {

				color_value = 0;
			}
		}

		this->mesh.setColor(index, ofColor(color_value));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	this->mesh.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}