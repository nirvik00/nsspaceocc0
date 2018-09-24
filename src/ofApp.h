#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "Pt.h"
#include <vector>


struct Quad {
public:
	Pt A, B, C, D;
	Pt pts[4];
	Quad (){}
	Quad(Pt a, Pt b, Pt c, Pt d) {
		A = a; B = b; C = c; D = d;
		pts[0] = A; pts[1] = B;
		pts[2] = C; pts[3] = D;
	}
	void setupPreservePts(Pt a, Pt b, Pt c, Pt d) {
		A = a; B = b; C = c; D = d;
		pts[0] = A; pts[1] = B;
		pts[2] = C; pts[3] = D;
	}
	void display() {
		ofPath path;
		path.setFillColor(ofColor(0, 150, 155, 20));
		path.setStrokeWidth(2);
		path.setStrokeColor(ofColor(0, 0, 0, 155));
		path.moveTo(A.x, A.y);
		path.lineTo(B.x, B.y);
		path.lineTo(C.x, C.y);
		path.lineTo(D.x, D.y);
		path.close();
		path.draw();
	}
	void display2() {
		ofPath path;
		path.setStrokeWidth(1);
		path.setFilled(false);
		path.setStrokeColor(ofColor(0, 0, 0, 150));
		path.moveTo(A.x, A.y);
		path.lineTo(B.x, B.y);
		path.lineTo(C.x, C.y);
		path.lineTo(D.x, D.y);
		path.close();
		path.draw();
	}
};

struct Seg{
public:
	Pt A,B;
	Seg() {};
	Seg(Pt a, Pt b) { A = a; B = b; }
	void setup(Pt a, Pt b) { A = a; B = b; }
	void display() { ofSetColor(150); ofDrawLine(A.x, A.y, B.x, B.y); }
};

struct sortSegDesc {
	bool operator() (Seg a, Seg b) {
		return a.A.di(a.B) > b.A.di(b.B);
	}
};

struct Tri {
	Pt A, B, C;
	Tri(Pt a, Pt b, Pt c) { A = a; B = b; C = c; }
};

struct sortTriDesc {
	bool operator() (Tri a, Tri b) {
		float u = a.A.di(a.B) + a.A.di(a.C) + a.B.di(a.C);
		float v = b.A.di(b.B) + b.A.di(b.C) + b.B.di(b.C);
		return  u > v;
	}
};


struct sortPtXAsc {
	bool operator() (Pt a, Pt b) {
		return a.x < b.x;
	}
};

struct sortPtYAsc {
	bool operator() (Pt a, Pt b) {
		return a.y < b.y;
	}
};

class ofApp : public ofBaseApp{

	public:
		//ofApp() {}
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
	
		/* NS METHODS */
		vector<Seg> getsegvec(vector<Pt>);
		vector<vector<Pt>> getcrvpts(vector<Pt>);
		vector<Pt> gensmoothboundary(vector<Pt>);
		vector<Pt> genintsmoothspine(vector<Pt>);
		vector<Pt> genintsmoothspine3pt(vector<Pt>);
		vector<Pt> geninternalboundary(vector<Pt>, float);
		vector<Pt> Lerp(Pt, Pt, Pt);
		Pt intxPt(Pt, Pt, Pt, Pt);
		Pt intxPt2(Pt, Pt, Pt, Pt);
		Pt intxPt4(Pt, Pt, Pt, Pt);
		int doesintx(Pt, Pt, Pt, Pt);
		Pt initPeripheralSys(Pt, Pt, Pt, float);
		float heron(Pt, Pt, Pt);
		int heronContains(Pt, Pt, Pt, Pt);
		Pt proj(Pt, Pt, Pt);
		vector<Quad> initSubdiv(Pt, Pt, Pt, Pt, int, vector<Quad>);
		void subdiv(Quad, int, int);
		vector<Pt> ofApp::gensmoothboundary(Pt, Pt, Pt, Pt);
		void initSpineBBSubdiv();
		vector<Quad> periIntQuad(Quad, float, float);
		vector<ofPath> genDoorSwing(Quad, int);

		/* NS VARIABLES */
		vector<Pt> oriptvec;
		vector<Pt> iniptvec;
		vector<Pt> revptvec;
		vector<Pt> intptvec;
		vector<Pt> revintptvec;
		vector<Pt> intgridptvec;
		vector<Pt> revintgridptvec;
		ofPath path2, path3, path4;
		Seg spinehorseg, spineverseg;

		//global variables
		string MSG, title;
		

		int global_image_counter = 0;
		vector<Tri> trivec;
		vector<Seg>straightSeg;
		vector<vector<Pt>>crvpts; //used
		vector<Seg>intStraightSeg; //used
		vector<Pt>diagpts; //used
		ofPolyline intpolyline; //internal polyline to derive spine and internal configs
		vector<Pt> spineptvec; //from these points extract 2-loaded corridor
		vector<Quad> subdivquads; //subdivision of quad internal
		vector<Quad> intquads; //peripheral internal quads
		vector<Pt> inismoothspinept;// initial points of smooth spine
		vector<Pt> fsmoothspinept;

		int controlspine = 0;
		int generatesubdivsystem = 0;
		int generatetreesystem = 0;
		vector<Quad> intsubdivgeneratequads;
		vector<Quad> intperipgeneratequads;
		

		float L, W, Corridor, Curvature;
		//vector<vector<Quad>>subdivVec; 
		vector<Quad>subdivQuadVec;


		/*	gui parameters and objects	*/
		
		ofParameter<string>boundaryconfigblank;
		ofParameterGroup parameters;
		ofParameter<bool>showCurveSeg;
		ofParameter<string>generalperpparamsblank;
		ofParameter<float>PCurvature;
		ofParameter<int>CurveSegP0;
		
		ofParameter<float>PeripheralCellDepth;
		ofParameter<int>PeripheralCellLength;
		ofParameter<int>Corridor0;
		ofParameter<float>DoorDepth;
		ofParameter<bool>controlpts;

		ofParameter<string>crossconfigblank;
		ofParameter<bool>crossspinecontrolpts;
		ofParameter<bool>smoothspinecontrolpts;
		ofParameter<bool>showintregion;
		ofParameter<float>ICurvature;

		ofParameter<string>generalintparamsblank;
		
		ofParameter<int>intsubdiv; 
		ofParameter<int>smoothspinedist;
		ofParameter<float>spinecorrde;
		ofParameter<float>spinequadle;
		ofParameter<float>spinequadde;
		

		ofxPanel gui;
		// camera
		ofEasyCam cam;
};
