#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofBackground(239);
	ofSetWindowTitle("Insta");

	ofEnableDepthTest();
	ofSetColor(39);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 150, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<vector<string>> words = {
		{ "‚ ", "‚¢", "‚¤", "‚¦", "‚¨" },
		{ "‚©", "‚«", "‚­", "‚¯", "‚±" },
		{ "‚³", "‚µ", "‚·", "‚¹", "‚»" },
		{ "‚½", "‚¿", "‚Â", "‚Ä", "‚Æ" },
		{ "‚È", "‚É", "‚Ê", "‚Ë", "‚Ì" },
	};

	this->cam.begin();
	ofRotateX(180);

	int span = 144;
	for (int y = 0; y < words.size(); y++) {

		for (int x = 0; x < words[y].size(); x++) {
			
			this->draw_character_sphere(ofPoint(x * span - ofGetWidth() / 2 + span / 2, y * span - ofGetHeight() / 2 + span / 2), words[y][x], 80);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
void ofApp::draw_character_sphere(ofPoint point, string word, int radius) {

	ofPoint word_size = ofPoint(this->font.stringWidth(word), this->font.stringHeight(word));
	vector<ofTTFCharacter> word_paths = this->font.getStringAsPoints(word);
	ofPoint start, end;

	ofPushMatrix();
	ofTranslate(point);

	int deg_param = ofGetFrameNum() % 1080;
	if (deg_param > 720) {

		ofRotateY(deg_param - 720);
	}
	else if (deg_param > 360) {

		ofRotateZ(deg_param - 360);
	}
	else {

		ofRotateX(deg_param);
	}

	 

	for (int w_index = 0; w_index < word_paths.size(); w_index++) {

		vector<ofPolyline> outline = word_paths[w_index].getOutline();
		ofVec3f center = outline[0].getCentroid2D();
		for (int o_index = 0; o_index < outline.size(); o_index++) {

			outline[o_index] = outline[o_index].getResampledBySpacing(3);
			vector<ofPoint> vertices = outline[o_index].getVertices();
			for (int v_index = 1; v_index < vertices.size(); v_index++) {

				start = ofPoint(vertices[v_index - 1].x - word_size.x / 2, vertices[v_index - 1].y + word_size.y / 2, -radius);
				end = ofPoint(vertices[v_index].x - word_size.x / 2, vertices[v_index].y + word_size.y / 2, -radius);
				ofDrawLine(start.normalized() * radius, end.normalized() * radius);
			}
			start = ofPoint(vertices[0].x - word_size.x / 2, vertices[0].y + word_size.y / 2, -radius);
			end = ofPoint(vertices[vertices.size() - 1].x - word_size.x / 2, vertices[vertices.size() - 1].y + word_size.y / 2, -radius);
			ofDrawLine(start.normalized() * radius, end.normalized() * radius);
		}
	}

	ofPopMatrix();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}