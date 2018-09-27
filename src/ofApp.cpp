#include "ofApp.h"


/*	NS METHODS	*/

vector<Seg> ofApp::getsegvec(vector<Pt>ptvec) {
	vector<Seg> newptvec; newptvec.clear();
	for (int i = 0; i < ptvec.size() - 1; i++) {
		Pt A, B, C; Pt a, b, c;
		if (i == 0) {
			a = ptvec[7]; b = ptvec[0]; c = ptvec[1];
			A.setup(a.x + (b.x - a.x)*Curvature, a.y + (b.y - a.y)*Curvature);
			C.setup(c.x + (b.x - c.x)*Curvature, c.y + (b.y - c.y)*Curvature);
			B = b;
		}
		else {
			a = ptvec[i - 1]; b = ptvec[i]; c = ptvec[i + 1];
			A.setup(a.x + (b.x - a.x)*Curvature, a.y + (b.y - a.y)*Curvature);
			C.setup(c.x + (b.x - c.x)*Curvature, c.y + (b.y - c.y)*Curvature);
			B = b;
		}
		newptvec.push_back(Seg(A, C));
	}	
	return newptvec;
}

vector<vector<Pt>> ofApp::getcrvpts(vector<Pt>ptvec) {
	vector<vector<Pt>>nestptvec;
	for (int i = 0; i < ptvec.size() - 1; i++) {
		vector<Pt> newptvec; newptvec.clear();
		Pt A, B, C; Pt a, b, c;
		if (i == 0) {
			a = ptvec[7]; b = ptvec[0]; c = ptvec[1];
			A.setup(a.x + (b.x - a.x)*Curvature, a.y + (b.y - a.y)*Curvature);
			C.setup(c.x + (b.x - c.x)*Curvature, c.y + (b.y - c.y)*Curvature);
			B = b;
		}
		else {
			a = ptvec[i - 1]; b = ptvec[i]; c = ptvec[i + 1];
			A.setup(a.x + (b.x - a.x)*Curvature, a.y + (b.y - a.y)*Curvature);
			C.setup(c.x + (b.x - c.x)*Curvature, c.y + (b.y - c.y)*Curvature);
			B = b;
		}
		//bezier
		newptvec.push_back(A); vector<Pt> pts = Lerp(A, B, C);
		for (int j = 1; j < pts.size(); j++) {
			newptvec.push_back(pts[j]);
		}
		newptvec.push_back(C);
		nestptvec.push_back(newptvec);
	}
	return nestptvec;
}

vector<Pt>ofApp::Lerp(Pt a, Pt b, Pt c) {
	Pt ab[20]; Pt bc[20]; vector<Pt> pts;
	int k = 0;
	float n = 1.f / 20.f;
	for (float i = 0.f; i < 1.f; i += n) {
		ab[k].setup(a.x + (b.x - a.x)*i, a.y + (b.y - a.y)*i);
		bc[k].setup(b.x + (c.x - b.x)*i, b.y + (c.y - b.y)*i);
		k++;
	}
	k = 0;
	for (float i = 0.f; i < 1.f; i += n) {
		float x = ab[k].x + (bc[k].x - ab[k].x)*i;
		float y = ab[k].y + (bc[k].y - ab[k].y)*i;
		Pt e(x, y);
		pts.push_back(e);
		k++;
	}
	return pts;
}

vector<Pt> ofApp::gensmoothboundary(vector<Pt>ptvec) {
	vector<Pt> newptvec; newptvec.clear();
	for (int i = 0; i < ptvec.size() - 1; i++) {
		Pt A, B, C; Pt a, b, c;
		if (i == 0) {
			a = ptvec[7]; b = ptvec[0]; c = ptvec[1];
			A.setup(a.x + (b.x - a.x)*Curvature, a.y + (b.y - a.y)*Curvature);
			C.setup(c.x + (b.x - c.x)*Curvature, c.y + (b.y - c.y)*Curvature);
			B = b;
		}
		else {
			a = ptvec[i - 1]; b = ptvec[i]; c = ptvec[i + 1];
			A.setup(a.x + (b.x - a.x)*Curvature, a.y + (b.y - a.y)*Curvature);
			C.setup(c.x + (b.x - c.x)*Curvature, c.y + (b.y - c.y)*Curvature);
			B = b;
		}
		//bezier
		newptvec.push_back(A); vector<Pt> pts = Lerp(A, B, C);
		for (int j = 1; j < pts.size(); j++) {
			newptvec.push_back(pts[j]);
		}
		newptvec.push_back(C);
	}
	newptvec.push_back(newptvec[0]);
	return newptvec;
}

vector<Pt> ofApp::genintsmoothspine(vector<Pt>ptvec) {
	vector<Pt> newpts;
	for (int i = 0; i < ptvec.size()-2; i++) {
		Pt a = ptvec[i];
		Pt b = ptvec[i + 1];
		Pt c = ptvec[i+2];

		Pt a_(a.x + (b.x - a.x)*ICurvature, a.y + (b.y - a.y)*ICurvature);
		Pt c_(c.x + (b.x - c.x)*ICurvature, c.y + (b.y - c.y)*ICurvature);
		Pt ba(b.x + (a.x - b.x)*ICurvature, b.y + (a.y - b.y)*ICurvature);
		Pt bc(b.x + (c.x - b.x)*ICurvature, b.y + (c.y - b.y)*ICurvature);
		vector<Pt> pt0;
		for (float j = 0; j < 1.0; j += 0.01) {
			Pt p(ba.x + (a_.x - ba.x)*j, ba.y + (a_.y - ba.y)*j);
			newpts.push_back(p);
		}
		vector<Pt> pts=Lerp(a_, b, c_);
		for (int j = 0; j < pts.size(); j++) {
			newpts.push_back(pts[j]);
		}
	}
	return newpts;
}

vector<Pt> ofApp::genintsmoothspine3pt(vector<Pt>ptvec) {
	vector<Pt> newpts;
	Pt a = ptvec[0];
	Pt b = ptvec[1];
	Pt c = ptvec[2];

	Pt a_(a.x + (b.x - a.x)*ICurvature, a.y + (b.y - a.y)*ICurvature);
	Pt c_(c.x + (b.x - c.x)*ICurvature, c.y + (b.y - c.y)*ICurvature);
	Pt ba(b.x + (a.x - b.x)*ICurvature, b.y + (a.y - b.y)*ICurvature);
	Pt bc(b.x + (c.x - b.x)*ICurvature, b.y + (c.y - b.y)*ICurvature);

	//construct the first set of points
	for (float j = 0; j < 1.0; j += 0.01) {
		Pt p(a.x + (a_.x - a.x)*j, a.y + (a_.y - a.y)*j);
		newpts.push_back(p);
	}

	//construct the bezier curve
	vector<Pt> pts_a_b;
	for (float j = 0; j < 1.0; j+=0.01) {
		Pt p(a_.x + (b.x - a_.x)*j, a_.y + (b.y - a_.y)*j);
		pts_a_b.push_back(p);
	}
	vector<Pt> pts_b_c;
	for (float j = 0; j < 1.0; j += 0.01) {
		Pt p(b.x + (c_.x - b.x)*j, b.y + (c_.y - b.y)*j);
		pts_b_c.push_back(p);
	}
	int k = 0;
	for (float j = 0; j < 1.0; j += 0.01) {
		Pt m = pts_a_b[k]; Pt n = pts_b_c[k];
		Pt p(m.x + (n.x - m.x)*j, m.y + (n.y - m.y)*j);
		newpts.push_back(p);
		k++;
	}
	
	//construct the last set of points
	for (float j = 0; j < 1.0; j += 0.01) {
		Pt p(c_.x + (c.x - c_.x)*j, c_.y + (c.y - c_.y)*j);
		newpts.push_back(p);
	}

	return newpts;
}

vector<Pt> ofApp::gensmoothboundary(Pt a, Pt b, Pt c, Pt d) {
	vector<Pt> abc = Lerp(a, b, c);
	return abc;
}

vector<Pt> ofApp::geninternalboundary(vector<Pt> ptvec, float g) {
	vector<Pt>newptvec; newptvec.clear();
	for (int i = 0; i < ptvec.size() - 1; i++) {
		Pt A, B, C;
		if (i == 0) {
			A = ptvec[7];
			B = ptvec[0];
			C = ptvec[1];
		}
		else if (i < ptvec.size() - 2) {
			A = ptvec[i - 1];
			B = ptvec[i];
			C = ptvec[i + 1];
		}
		else {
			A = ptvec[i - 1];
			B = ptvec[i];
			C = ptvec[0];
		}
		Pt q = initPeripheralSys(A, B, C, g);
		newptvec.push_back(q);
	}
	newptvec.push_back(newptvec[0]);
	return newptvec;
}

void ofApp::initSpineBBSubdiv() {
	vector <Pt> bbpt;
	for (int i = 1; i < revintgridptvec.size(); i++) {
		Pt a = revintgridptvec[i - 1]; Pt b = revintgridptvec[i];
		Pt c = spinehorseg.A; Pt d = spinehorseg.B;
		Pt I = intxPt4(a, b, c, d);
		if (I.x > 0 && I.y > 0) {
			bbpt.push_back(Pt(I.x, I.y));
		}
	}

	for (int i = 1; i < revintgridptvec.size(); i++) {
		Pt a = revintgridptvec[i - 1]; Pt b = revintgridptvec[i];
		Pt c = spineverseg.A; Pt d = spineverseg.B;
		Pt I = intxPt4(a, b, c, d);
		if (I.x > 0 && I.y > 0) {
			bbpt.push_back(Pt(I.x, I.y));
		}
	}

	function<bool(Pt, Pt)> sortPtX = sortPtXAsc();
	sort(bbpt.begin(), bbpt.end(), sortPtX);
	float minx = bbpt[0].x; float maxx = bbpt[bbpt.size() - 1].x;
	function<bool(Pt, Pt)> sortPtY = sortPtYAsc();
	sort(bbpt.begin(), bbpt.end(), sortPtY);
	float miny = bbpt[0].y; float maxy = bbpt[bbpt.size() - 1].y;
	Quad bbquad(Pt(minx, miny), Pt(maxx, miny), Pt(maxx, maxy), Pt(minx, maxy));

	subdivquads.clear();
	subdivquads = initSubdiv(Pt(minx, miny), Pt(maxx, miny), Pt(maxx, maxy), Pt(minx, maxy), intsubdiv, subdivquads);
	generatesubdivsystem = 0;
}




/*	OF METHODS	*/


void ofApp::setup(){
	parameters.setName("Controls");
	parameters.add(boundaryconfigblank.set("BOUNDARY CONFIG"));
	parameters.add(showCurveSeg.set("Place Curve Seg", true));
	parameters.add(controlpts.set("Control Pts", false));
	
	parameters.add(generalperpparamsblank.set("PERIPHERAL PARAMETERS"));
	parameters.add(PCurvature.set("Curvature", 0.6972, 0.51, 0.99f));
	parameters.add(CurveSegP0.set("Crv Seg P-0", 6.1, 1, 10));
	parameters.add(PeripheralCellDepth.set("P. Depth", 50, 5, 125));
	parameters.add(PeripheralCellLength.set("P. Length", 50, 5, 75));	
	parameters.add(Corridor0.set("P. Cor Depth ", 25, 1, 75));
	parameters.add(DoorDepth.set("Door Depth ", 15, 5, 25));
	
	parameters.add(crossconfigblank.set("CROSS SPINE CONFIG"));
	parameters.add(crossspinecontrolpts.set("Show Cross Spine", false));
	parameters.add(smoothspinecontrolpts.set("Show Smooth Spine", false));
	parameters.add(ICurvature.set("Curvature", 0.6972, 0.51, 0.99f));
	parameters.add(intsubdiv.set("Number of subdiv", 1, 0, 3));
	parameters.add(showintregion.set("Show I region", false));

	parameters.add(generalintparamsblank.set("INTERNAL PARAMETERS"));
	parameters.add(smoothspinedist.set("Smooth Spine Di", 40, 5, 50));
	parameters.add(spinecorrde.set("I. Corr", 15, 0, 25));
	parameters.add(spinequadle.set("I. Length", 40, 5, 125));
	parameters.add(spinequadde.set("I. Depth", 30, 5, 125));

	gui.setup(parameters);
	gui.setBackgroundColor(ofColor(255,150,255));

	//points for the initial outer boundary 
	iniptvec.push_back(Pt(550, 100)); iniptvec.push_back(Pt(950, 250)); iniptvec.push_back(Pt(1350, 100));
	iniptvec.push_back(Pt(1200, 450)); iniptvec.push_back(Pt(1350, 850)); iniptvec.push_back(Pt(950, 700));
	iniptvec.push_back(Pt(550, 850)); iniptvec.push_back(Pt(700, 450)); iniptvec.push_back(Pt(550, 100));
	oriptvec = iniptvec;

	L = PeripheralCellLength; W = PeripheralCellLength; Corridor = Corridor0;
	
	Pt p0(500, 450); Pt p1(600, 450); Pt p2(700, 450);
	Pt p3(800, 450); Pt p4(900, 450); Pt p5(1000, 450);
	Pt p6(1100, 450); Pt p7(1175, 450); 
	inismoothspinept.push_back(p0); 
	//inismoothspinept.push_back(p1); 
	//inismoothspinept.push_back(p2);
	//inismoothspinept.push_back(p3); 
	inismoothspinept.push_back(p4); 
	//inismoothspinept.push_back(p5);
	//inismoothspinept.push_back(p6); 
	inismoothspinept.push_back(p7);
	
	// horizontal and vertical cross axes
	spinehorseg.setup(Pt(500, ofGetHeight() / 2), Pt(1400, ofGetHeight() / 2));
	spineverseg.setup(Pt(950, 200), Pt(950, ofGetHeight() - 50));

}

void ofApp::update(){

	MSG = "Keyboard controls:";
	MSG += "\n------------------";
	MSG += "\nPress 'r' 'R' to reset to original drawing";
	MSG += "\nPress 's' 'S' to save image";
	MSG += "\nPress 'e' 'E' to control spine";
	MSG += "\nPress 'f' 'F' to stop control spine";
	MSG += "\nPress 'g' 'G' to subdivide I quads";
	MSG += "\nPress 'h' 'H' to gen peripheral I quads";
	title = "PhD student: Nirvik Saha (G.I.T.) \t\tadvisor: Dennis R Shelden (G.I.T.) \t\tadvisor: John R Haymaker (P + W)";



	L = PeripheralCellLength; W = PeripheralCellDepth; Corridor = Corridor0; Curvature = PCurvature;

	revptvec.clear(); intptvec.clear(); revintptvec.clear(); intgridptvec.clear(); revintgridptvec.clear();
	revptvec = gensmoothboundary(iniptvec);

	straightSeg.clear(); crvpts.clear();
	intptvec = geninternalboundary(iniptvec, W);
	revintptvec= gensmoothboundary(intptvec);
	straightSeg = getsegvec(intptvec); straightSeg.push_back(straightSeg[0]);
	crvpts=getcrvpts(intptvec);
	
	intgridptvec= geninternalboundary(iniptvec, W+Corridor);
	revintgridptvec = gensmoothboundary(intgridptvec);
	intStraightSeg= getsegvec(intgridptvec); intStraightSeg.push_back(intStraightSeg[0]);

	//internal region -- polyline
	intpolyline.clear();
	vector<ofVec3f> intpolypts;
	for (int j = 1; j < revintgridptvec.size(); j++) {
		intpolyline.addVertex(ofVec3f(revintgridptvec[j].x, revintgridptvec[j].y));
	}
	intpolyline.close();


	//spine (hor & ver) intersect with internal region
	// construct bounding box internally and subdivide
	if (generatesubdivsystem == 1) {
		initSpineBBSubdiv();
		generatesubdivsystem = 0;
	}
	
	//get the smooth spine
	fsmoothspinept = genintsmoothspine3pt(inismoothspinept);
	
}

void ofApp::draw() {
	ofBackground(255);

	trivec.clear();
	//plot smooth boundaries	
	float sW = 2; ofColor colr = (ofColor(255, 0, 0, 50)); 
	ofColor fill2(colr);
	path2.clear();
	path2.setStrokeColor(ofColor(0,0,0,255));
	path2.setStrokeWidth(sW); path2.setFillColor(fill2);
	path2.moveTo(revptvec[0].x, revptvec[0].y);
	for (int i = 1; i < revptvec.size(); i++) {
		path2.lineTo(revptvec[i].x, revptvec[i].y);
		//ofEllipse(revptvec[i].x,revptvec[i].y,10,10);
	}
	path2.draw();

	path3.clear();
	path3.setStrokeColor(ofColor(150, 150, 0, 155));
	path3.setStrokeWidth(sW); path3.setFillColor(ofColor(250, 250, 250));
	path3.moveTo(revintptvec[0].x, revintptvec[0].y);
	for (int j = 1; j < revintptvec.size(); j++) { path3.lineTo(revintptvec[j].x, revintptvec[j].y); }
	path3.draw();

	//plot normal segments at points on straight segments
	ofSetColor(ofColor(0,0,0,255)); ofSetLineWidth(sW);
	for (int i = 1; i < straightSeg.size(); i++) {
		Pt a = straightSeg[i - 1].B; Pt b = straightSeg[i].A;
		int n = a.di(b) / L;
		Pt u((b.x - a.x) / a.di(b), (b.y - a.y) / a.di(b));
		vector<Pt> pts;
		for (int j = 1; j < n + 1; j++) {
			Pt e(a.x + (u.x*j*L), a.y + (u.y*j*L));
			pts.push_back(e);
		}
		for (int j = 0; j < pts.size(); j++) {
			Pt e = pts[j]; Pt f(e.x - (u.y), e.y + (u.x));
			for (int k = 1; k < revptvec.size(); k++) {
				Pt g(revptvec[k - 1].x, revptvec[k - 1].y); Pt h(revptvec[k].x, revptvec[k].y);
				Pt I = intxPt2(e, f, g, h);
				if (I.di(e) < W*1.5 && I.di(e) > 0.75*W && I.x > 0) {
					ofLine(e.x, e.y, I.x, I.y);
					trivec.push_back(Tri(I, e, b));
					break;
				}
			}
		}
	}

	if (showCurveSeg == 1) {
		//plot curve points normal segment
		vector<Seg>prevseg; ofSetColor(ofColor(0,0,0,255)); ofSetLineWidth(sW);
		int mod = CurveSegP0;
		//plot point segments of curve & absorb in vector
		for (int i = 0; i < crvpts.size(); i++) {
			for (int j = 1; j < crvpts[i].size() - 1; j++) {
				if (j % mod == 0) {
					Pt p = crvpts[i][j];	Pt MP = crvpts[i][j]; int mpIn = j;
					Pt P = crvpts[i][mpIn - 1]; Pt E = MP; Pt R = crvpts[i][mpIn + 1];
					Pt U((R.x - P.x) / P.di(R), (R.y - P.y) / P.di(R));
					Pt F(E.x - U.y, E.y + U.x);
					for (int k = 1; k < revptvec.size(); k++) {
						Pt g(revptvec[k - 1].x, revptvec[k - 1].y); Pt h(revptvec[k].x, revptvec[k].y);
						Pt I = intxPt2(E, F, g, h);
						if (I.di(E) < W*2.f && I.di(E) > 0.75*W && I.x > 0) {
							ofLine(E.x, E.y, I.x, I.y);
							prevseg.push_back(Seg(E, I));
							trivec.push_back(Tri(I, E, R));
							break;
						}
					}
				}
			}
		}
		//plot mid point of crv 
		if (prevseg.size() == 0) {
			for (int i = 0; i < crvpts.size(); i++) {
				Pt p = crvpts[i][10];	Pt MP = crvpts[i][10]; int mpIn = 10;
				Pt P = crvpts[i][mpIn - 1]; Pt E = MP; Pt R = crvpts[i][mpIn + 1];
				Pt U((R.x - P.x) / P.di(R), (R.y - P.y) / P.di(R));
				Pt F(E.x - U.y, E.y + U.x);
				for (int k = 1; k < revptvec.size(); k++) {
					Pt g(revptvec[k - 1].x, revptvec[k - 1].y); Pt h(revptvec[k].x, revptvec[k].y);
					Pt I = intxPt2(E, F, g, h);
					if (I.di(E) < W*2.f && I.di(E) > 0.75*W && I.x > 0) {
						ofLine(E.x, E.y, I.x, I.y);
						prevseg.push_back(Seg(E, I));
						trivec.push_back(Tri(I, E, R));
						break;
					}
				}
			}
		}

	}
	
	//plot door swings - Peripheral Quads
	float dw = DoorDepth; ofSetColor(ofColor(0, 0, 0, 255));	
	for (int i = 0; i < trivec.size(); i++) {
		Pt n = trivec[i].A; Pt e = trivec[i].B; Pt f = trivec[i].C;
		Pt u((f.x - e.x) / e.di(f), (f.y - e.y) / e.di(f));
		Pt v((n.x - e.x) / e.di(n), (n.y - e.y) / e.di(n));
		vector<Pt> doorpts;
		for (float j = 0.f; j < (PI / 2); j += PI / 20) {
			float A = 2 * PI - j;
			float x = u.x*cos(A)*dw - u.y*sin(A)*dw;
			float y = u.x*sin(A)*dw + u.y*cos(A)*dw;
			Pt r(e.x + x, e.y + y);
			doorpts.push_back(r);
		}
		Pt p0 = doorpts[0];
		doorpts.push_back(e);

	ofPath door; ofColor dcolr(255, 255, 255, 255); door.setStrokeWidth(1); door.setFillColor(dcolr); door.setStrokeColor(dcolr);
	door.moveTo(doorpts[0].x, doorpts[0].y);
	for (int j = 0; j < doorpts.size(); j++) {
		door.lineTo(doorpts[j].x, doorpts[j].y);
	}
	door.close();
	door.draw();

	ofPath doorswing; ; doorswing.setStrokeWidth(2); doorswing.setStrokeColor(ofColor(0, 0, 0));
	door.moveTo(doorpts[0].x, doorpts[0].y);
	for (int j = 0; j < doorpts.size(); j++) {
		doorswing.lineTo(doorpts[j].x, doorpts[j].y);
	}
	doorswing.draw();
	}

	if (controlpts == true) {
		//control lines - initial polygon
		for (int i = 0; i < iniptvec.size(); i++) {
			if (iniptvec[i].locked == 1) {
				ofSetColor(255, 0, 0, 100); ofFill();
				ofEllipse(iniptvec[i].x, iniptvec[i].y, 25, 25);
				ofNoFill(); ofSetColor(255, 0, 0, 100);
				ofEllipse(iniptvec[i].x, iniptvec[i].y, 35, 35);
			}
			ofSetColor(100, 100, 100); ofEllipse(iniptvec[i].x, iniptvec[i].y, 10, 10);
			if (i > 0) {
				ofSetColor(225, 225, 225); ofSetLineWidth(1); ofLine(iniptvec[i - 1].x, iniptvec[i - 1].y, iniptvec[i].x, iniptvec[i].y);
				ofNoFill(); ofSetColor(50, 50, 50);	ofEllipse(iniptvec[i].x, iniptvec[i].y, 35, 35);
			}
		}
	}

	ofFill(); ofSetColor(ofColor(0, 0, 0, 50)); ofDrawRectangle(15, 675, 350, 150);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString(MSG, 20, 700);
	ofSetColor(0, 0, 0, 255); ofDrawBitmapString(title, 100, ofGetHeight() - 30);
	gui.draw();

	//show internal regions
	if (showintregion == true) {
		path4.clear();
		path4.setStrokeColor(ofColor(0, 0, 0, 155)); path4.setFillColor(ofColor(255, 255, 255));
		path4.setStrokeWidth(sW);
		path4.moveTo(revintgridptvec[0].x, revintgridptvec[0].y);
		for (int j = 1; j < revintgridptvec.size(); j++) {
			path4.lineTo(revintgridptvec[j].x, revintgridptvec[j].y);
		}
		path4.draw();
	}

	if (showintregion == 1) { 
		intpolyline.draw(); 
		if (subdivquads.size() > 0) {
			for (int i = 0; i < subdivquads.size(); i++) {
				Quad Q = subdivquads[i]; Q.display2();
			}
		}
	}

	//for peripheral system: this is a boundary with a hole such that the boundary gets filled on one side 
	if (subdivquads.size() > 0) {
		plotsubdivquad.clear(); subdivdoorswingpath.clear();
		intquads.clear(); float Le = spinequadle; float De = spinequadde; float De1 = (De / cos(PI / 4));
		for (int i = 0; i < subdivquads.size(); i++) {
			Quad Q = subdivquads[i];
			Pt a = Q.A; Pt b = Q.B; Pt c = Q.C; Pt d = Q.D;

			Pt t((b.x - a.x)*De1 / a.di(b), (b.y - a.y)*De1 / a.di(b));
			Pt u((c.x - b.x)*De1 / b.di(c), (c.y - b.y)*De1 / b.di(c));
			Pt v((d.x - c.x)*De1 / c.di(d), (d.y - c.y)*De1 / c.di(d));
			Pt w((a.x - d.x)*De1 / a.di(d), (a.y - d.y)*De1 / a.di(d));
			
			Pt m(a.x + t.x*cos(PI / 4) - t.y*sin(PI / 4), a.y + t.x*sin(PI / 4) + t.y*cos(PI / 4));
			Pt n(b.x + u.x*cos(PI / 4) - u.y*sin(PI / 4), b.y + u.x*sin(PI / 4) + u.y*cos(PI / 4));
			Pt o(c.x + v.x*cos(PI / 4) - v.y*sin(PI / 4), c.y + v.x*sin(PI / 4) + v.y*cos(PI / 4));
			Pt p(d.x + w.x*cos(PI / 4) - w.y*sin(PI / 4), d.y + w.x*sin(PI / 4) + w.y*cos(PI / 4));
			
			//these are the quads with angle bisector
			Quad Q0(a, m, n, b); Quad Q1(b, n, o, c); Quad Q2(c, o, p, d); Quad Q3(d, p, m, a);

			//for 1st quad : a->m_, n->n_
			//for 2nd quad : b->n_, o->o_
			//for 3rd quad : c->o_, p->p_
			//for 4th quad : d->p_, m->m_
			//Pt m_(m.x, a.y); Pt n_(b.x, n.y); Pt o_(o.x, c.y); Pt p_(d.x, p.y);
			//Quad Q0(m_, m, n_, b); Quad Q1(n_, n, o_, c); Quad Q2(o_, o, p_, d); Quad Q3(p_, p, m_, a);			
			//Q0.display(); Q1.display(); Q2.display(); Q3.display();
			
			vector<Quad> quad0 = periIntQuad(Q0, Le, De);
			for (int j = 0; j < quad0.size(); j++) {
				//quad0[j].display(); 
				plotsubdivquad.push_back(quad0[j]);
				vector<ofPath> drpaths = genDoorSwing(quad0[j], j);
				for (int k = 0; k < drpaths.size(); k++) {
					ofPath dpath = drpaths[k]; subdivdoorswingpath.push_back(dpath);
					//dpath.setStrokeWidth(1); dpath.setStrokeColor(0); dpath.setFillColor(ofColor(255, 255, 255)); dpath.draw();
				}
			}
			vector<Quad> quad1 = periIntQuad(Q1, Le, De);
			for (int j = 0; j < quad1.size(); j++) {
				//quad1[j].display();
				plotsubdivquad.push_back(quad1[j]);
				vector<ofPath> drpaths = genDoorSwing(quad1[j], j);
				for (int k = 0; k < drpaths.size(); k++) {
					ofPath dpath = drpaths[k]; subdivdoorswingpath.push_back(dpath);
					//dpath.setStrokeWidth(1); dpath.setStrokeColor(0); dpath.setFillColor(ofColor(255, 255, 255)); dpath.draw();
				}
			}
			vector<Quad> quad2 = periIntQuad(Q2, Le, De);
			for (int j = 0; j < quad2.size(); j++) {
				//quad2[j].display();
				plotsubdivquad.push_back(quad2[j]);
				vector<ofPath> drpaths = genDoorSwing(quad2[j], j);
				for (int k = 0; k < drpaths.size(); k++) {
					ofPath dpath = drpaths[k]; subdivdoorswingpath.push_back(dpath);
					//dpath.setStrokeWidth(1); dpath.setStrokeColor(0); dpath.setFillColor(ofColor(255, 255, 255)); dpath.draw();
				}
			}
			vector<Quad> quad3 = periIntQuad(Q3, Le, De);
			for (int j = 0; j < quad3.size(); j++) {
				//quad3[j].display(); 
				plotsubdivquad.push_back(quad3[j]);
				vector<ofPath> drpaths = genDoorSwing(quad3[j], j);
				for (int k = 0; k < drpaths.size(); k++) {
					ofPath dpath = drpaths[k]; subdivdoorswingpath.push_back(dpath);
					//dpath.setStrokeWidth(1); dpath.setStrokeColor(0); dpath.setFillColor(ofColor(255, 255, 255)); dpath.draw();
				}
			}
		}
	}
	
	//plot the elements of the subdiv system
	if (plotsubdivquad.size()>0 && generatetreesystem ==0) {
		for (int i = 0; i < plotsubdivquad.size(); i++) {
			plotsubdivquad[i].display();
		}
		for (int i = 0; i < subdivdoorswingpath.size(); i++) {
			ofPath dpath = subdivdoorswingpath[i];
			dpath.setStrokeWidth(1); dpath.setStrokeColor(0);
			dpath.setFillColor(ofColor(255, 255, 255)); dpath.draw();
		}
	}

	//spineseg plot
	if (crossspinecontrolpts == 1) {
		if (spinehorseg.A.locked == 1) { ofFill(); ofSetColor(255, 0, 0, 150); ofDrawEllipse(spinehorseg.A.x, spinehorseg.A.y, 15, 15); }
		if (spinehorseg.B.locked == 1) { ofFill(); ofSetColor(255, 0, 0, 150); ofDrawEllipse(spinehorseg.B.x, spinehorseg.B.y, 15, 15); }
		ofSetColor(0, 0, 255, 50); ofSetLineWidth(7); ofDrawLine(spinehorseg.A.x, spinehorseg.A.y, spinehorseg.B.x, spinehorseg.B.y);
		ofSetColor(0, 0, 0, 150); ofSetLineWidth(1); ofNoFill(); ofDrawEllipse(spinehorseg.A.x, spinehorseg.A.y, 25, 25);
		ofSetColor(0, 0, 0, 150); ofSetLineWidth(1); ofNoFill(); ofDrawEllipse(spinehorseg.B.x, spinehorseg.B.y, 25, 25);
		if (spineverseg.A.locked == 1) { ofFill(); ofSetColor(255, 0, 0, 150); ofDrawEllipse(spineverseg.A.x, spineverseg.A.y, 15, 15); }
		if (spineverseg.B.locked == 1) { ofFill(); ofSetColor(255, 0, 0, 150); ofDrawEllipse(spineverseg.B.x, spineverseg.B.y, 15, 15); }
		ofSetColor(0, 0, 255, 50); ofSetLineWidth(7); ofDrawLine(spineverseg.A.x, spineverseg.A.y, spineverseg.B.x, spineverseg.B.y);
		ofSetColor(0, 0, 0, 150); ofSetLineWidth(1); ofNoFill(); ofDrawEllipse(spineverseg.A.x, spineverseg.A.y, 25, 25);
		ofSetColor(0, 0, 0, 150); ofSetLineWidth(1); ofNoFill(); ofDrawEllipse(spineverseg.B.x, spineverseg.B.y, 25, 25);
	}
	
	//points inside the interior polygon
	vector<Pt> intspinepts;
	for (int i = 1; i < fsmoothspinept.size(); i++) {
		Pt a = fsmoothspinept[i]; ofVec3f p(a.x, a.y, 0);
		bool t = intpolyline.inside(p);
		if (t == true) {
			intspinepts.push_back(Pt(a.x, a.y));
			//ofDrawEllipse(a.x, a.y, 10, 10);
		}
	}

	if (generatetreesystem == 1) {
		treedoorswingpath.clear(); plottreequad.clear();
		//get spaced-out points - using spine corr distance
		vector<Pt> reqspinepts; Pt prev(intspinepts[0]);
		for (int i = 0; i < intspinepts.size(); i++) {
			float d = intspinepts[i].di(prev);
			if (i%smoothspinedist == 0 && i > 0 && d > spinequadle) {
				Pt a = intspinepts[i];
				//ofSetColor(0); ofSetLineWidth(1); ofEllipse(a.x, a.y, 10, 10);
				reqspinepts.push_back(intspinepts[i]);
				prev.setup(intspinepts[i].x, intspinepts[i].y);
			}
		}

		//normals from interior spine points  + intersection of normals from spine wrt interior
		vector<Seg> segup; vector<Seg> segdn;
		for (int i = 1; i < reqspinepts.size(); i++) {
			Pt a = reqspinepts[i - 1]; Pt b = reqspinepts[i];
			Pt u((b.x - a.x) * 500 / a.di(b), (b.y - a.y) * 500 / a.di(b));
			Pt v(-u.y, u.x); Pt v_(u.y, -u.x);
			Pt e(a.x + v.x, a.y + v.y); Pt f(a.x + v_.x, a.y + v_.y);
			for (int j = 1; j < revintgridptvec.size(); j++) {
				Pt m = revintgridptvec[j - 1]; Pt n = revintgridptvec[j];
				Pt I = intxPt4(e, a, m, n);
				if (I.x > 0 && I.y > 0) {
					segdn.push_back(Seg(a, I));
				}
				Pt J = intxPt4(f, a, m, n);
				if (J.x > 0 && J.y > 0) {
					segup.push_back(Seg(a, J));
				}
			}
		}
		vector<Seg> unitseg;
		for (int i = 0; i < segup.size(); i++) {
			Pt a_ = segup[i].A;//this is point on spine
			Pt b = segup[i].B;//this is intx point on int region
			Pt u((b.x - a_.x) / a_.di(b), (b.y - a_.y) / a_.di(b));
			// move a off spine to account for internal corridor along spine
			Pt a(a_.x + u.x*spinecorrde, a_.y + u.y*spinecorrde);
			float j = 0;
			while (j*spinequadle < a.di(b) - spinequadle) {
				Pt e(a.x + u.x*j*spinequadle, a.y + u.y*j*spinequadle);
				Pt f(a.x + u.x*(j + 1)*spinequadle, a.y + u.y*(j + 1)*spinequadle);
				if (intpolyline.inside(ofVec3f(e.x, e.y, 0))) { // && intpolyline.inside(ofVec3f(f.x, f.y, 0))) {
					unitseg.push_back(Seg(e, f));
				}
				else {
					break;
				}
				j++;
			}
		}
		for (int i = 0; i < segdn.size(); i++) {
			Pt a_ = segdn[i].A;//this is point on spine
			Pt b = segdn[i].B;//this is intx point on int region
			Pt u((b.x - a_.x) / a_.di(b), (b.y - a_.y) / a_.di(b));
			// move a off spine to account for internal corridor along spine
			Pt a(a_.x + u.x*spinecorrde, a_.y + u.y*spinecorrde);
			float j = 0;
			while (j*spinequadle < a.di(b) - spinequadle) {
				Pt e(a.x + u.x*j*spinequadle, a.y + u.y*j*spinequadle);
				Pt f(a.x + u.x*(j + 1)*spinequadle, a.y + u.y*(j + 1)*spinequadle);
				if (intpolyline.inside(ofVec3f(e.x, e.y, 0))) {// && intpolyline.inside(ofVec3f(f.x, f.y, 0))) { 
					unitseg.push_back(Seg(e, f));
				}
				else {
					break;
				}
				j++;
			}
		}
		//generate unit quads and display + plot door swings
		//vector<ofPath> dpathX;
		for (int i = 0; i < unitseg.size(); i++) {
			Pt a = unitseg[i].A; Pt b = unitseg[i].B;
			float d = spinequadde; float d_ = DoorDepth;
			Pt u((b.x - a.x)*d / a.di(b), (b.y - a.y)*d / a.di(b));//for the unit quad
			Pt u_((b.x - a.x) / a.di(b), (b.y - a.y) / a.di(b));//for door swing

			Pt p(a.x - u.y, a.y + u.x); Pt p_(a.x + u.y, a.y - u.x);
			Pt q(b.x - u.y, b.y + u.x); Pt q_(b.x + u.y, b.y - u.x);
			Quad q0(a, p, q, b); Quad q1(a, p_, q_, b);
			//q0.display(); q1.display();
			Pt g(p.x + u_.y, p.y - u_.x); Pt g_(p.x + u_.x, p.y + u_.y);
			Pt h(p_.x - u_.y, p_.y + u_.x); Pt h_(p_.x + u_.x, p_.y + u_.y);

			int sum0 = 0; //check for containment quad q0
			int sum1 = 0; //check for containment quad q1
			for (int j = 0; j < plottreequad.size(); j++) {
				ofPolyline poly = plottreequad[j].getPoly();
				Quad qt = plottreequad[j];
				
				//first quad
				ofPolyline poly0 = q0.getPoly();
				if (poly.inside(q0.A.x, q0.A.y) == true) { sum0++; }
				if (poly.inside(q0.B.x, q0.B.y) == true) { sum0++; }
				if (poly.inside(q0.C.x, q0.C.y) == true) { sum0++; }
				if (poly.inside(q0.D.x, q0.D.y) == true) { sum0++; }
				if (poly0.inside(qt.A.x, qt.A.y) == true) { sum0++; }
				if (poly0.inside(qt.B.x, qt.B.y) == true) { sum0++; }
				if (poly0.inside(qt.C.x, qt.C.y) == true) { sum0++; }
				if (poly0.inside(qt.D.x, qt.D.y) == true) { sum0++; }
				
				//the second quad
				ofPolyline poly1 = q1.getPoly();
				if (poly.inside(q1.A.x, q0.A.y) == true) { sum1++; }
				if (poly.inside(q1.B.x, q0.B.y) == true) { sum1++; }
				if (poly.inside(q1.C.x, q0.C.y) == true) { sum1++; }
				if (poly.inside(q1.D.x, q0.D.y) == true) { sum1++; }
				if (poly1.inside(qt.A.x, qt.A.y) == true) { sum1++; }
				if (poly1.inside(qt.B.x, qt.B.y) == true) { sum1++; }
				if (poly1.inside(qt.C.x, qt.C.y) == true) { sum1++; }
				if (poly1.inside(qt.D.x, qt.D.y) == true) { sum1++; }
				
			}
			if (sum0 == 0) {
				plottreequad.push_back(q0); 
				ofPath dpath0;
				for (float k = 0; k < PI / 2; k += PI / 20) {
					float ang = 2 * PI - k;
					float x = u_.x*cos(ang)*DoorDepth - u_.y*sin(ang)*DoorDepth;
					float y = u_.x*sin(ang)*DoorDepth + u_.y*cos(ang)*DoorDepth;
					Pt P(p.x + x, p.y + y);
					if (k == 0) { dpath0.moveTo(P.x, P.y); }
					else { dpath0.lineTo(P.x, P.y); }
				}
				treedoorswingpath.push_back(dpath0);
			}
			if(sum1==0){
				plottreequad.push_back(q1);
				ofPath dpath1;
				for (float k = 0; k < PI / 2; k += PI / 20) {
					float ang = k;
					float x = u_.x*cos(ang)*DoorDepth - u_.y*sin(ang)*DoorDepth;
					float y = u_.x*sin(ang)*DoorDepth + u_.y*cos(ang)*DoorDepth;
					Pt P(p_.x + x, p_.y + y);
					if (k == 0) { dpath1.moveTo(P.x, P.y); }
					else { dpath1.lineTo(P.x, P.y); }
				}
				treedoorswingpath.push_back(dpath1);
			}			
		}		
	}
	
	//plot quads & door swing of smooth spine 
	if (generatetreesystem == 1) {
		for (int i = 0; i < treedoorswingpath.size(); i++) {
			treedoorswingpath[i].setFilled(true); treedoorswingpath[i].setFillColor(ofColor(255, 255, 255));
			treedoorswingpath[i].setStrokeColor(ofColor(0, 0, 0)); treedoorswingpath[i].setStrokeWidth(1);
			treedoorswingpath[i].draw();
		}
		for (int i = 0; i < plottreequad.size(); i++) {
			plottreequad[i].display();
		}
	}
	

	//plot smooth spine + spine curve
	if (smoothspinecontrolpts == true) {
		for (int i = 0; i < inismoothspinept.size(); i++) {
			ofSetLineWidth(1);
			if (inismoothspinept[i].locked == 1) {
				ofFill(); ofSetColor(255, 0, 0, 150);
				ofDrawEllipse(inismoothspinept[i].x, inismoothspinept[i].y, 10, 10);
			}
			else {
				ofDrawEllipse(inismoothspinept[i].x, inismoothspinept[i].y, 10, 10);
			}
			ofNoFill(); ofSetColor(0); ofDrawEllipse(inismoothspinept[i].x, inismoothspinept[i].y, 25, 25);
		}
		for (int i = 1; i < inismoothspinept.size(); i++) {
			Pt a = inismoothspinept[i - 1]; Pt b = inismoothspinept[i];
			ofSetLineWidth(1); ofSetColor(150); ofDrawLine(a.x, a.y, b.x, b.y);
		}
		//draw the smooth spine
		ofPath smooothspinepath;
		for (int i = 0; i < intspinepts.size(); i++) {
			Pt a = intspinepts[i];
			if (i == 0) { smooothspinepath.moveTo(a.x, a.y); }
			else { smooothspinepath.lineTo(a.x, a.y); }
		}
		smooothspinepath.setStrokeWidth(10); smooothspinepath.setFilled(false);
		smooothspinepath.setStrokeColor(ofColor(150, 255, 150, 50));
		smooothspinepath.draw();
	}
}

vector<ofPath> ofApp::genDoorSwing(Quad quad, int T) {
	//here the path returned is a globally defined variable & updated asap
	vector<ofPath> pathvec;
	ofPath dpath;
	Quad q0 = quad;
	Pt a, b, c, d;
	if (T == 0) {
		a = q0.A; b = q0.B; c = q0.C; d = q0.D;
	}
	else {
		a = q0.A; b = q0.B; c = q0.C; d = q0.D;
	}
	Pt u((d.x - a.x) / a.di(d), (d.y - a.y) / a.di(d));
	Pt v((b.x - a.x) / a.di(b), (b.y - a.y) / a.di(b));
	float th = acos((u.x*v.x + u.y*v.y) / (a.di(b)*a.di(d)));
	//door swings from d-a-b				
	for (float k = 0; k < PI / 2; k += PI / 20) {
		float ang = 2 * PI - k;
		float x = u.x*cos(ang)*DoorDepth - u.y*sin(ang)*DoorDepth;
		float y = u.x*sin(ang)*DoorDepth + u.y*cos(ang)*DoorDepth;
		Pt p(a.x + x, a.y + y);
		if (k == 0) {
			dpath.moveTo(p.x, p.y);
		}
		else {
			dpath.lineTo(p.x, p.y);
		}
	}
	dpath.lineTo(a.x, a.y); dpath.close();
	pathvec.push_back(dpath);
	return pathvec;
}

vector<Quad> ofApp::periIntQuad(Quad Q, float Le, float De) {
	vector<Pt> pt1;
	Pt a = Q.A; Pt b = Q.B; Pt c = Q.C; Pt d = Q.D;
	Pt u((c.x - b.x) / (c.di(b)), (c.y - b.y) / (c.di(b))); 
	float i = DoorDepth+20;
	while (i < b.di(c)-DoorDepth) {
		Pt m(b.x + u.x*i, b.y + u.y*i); 
		pt1.push_back(m); 
		i += Le;
	}
	vector<Seg> seg;
	seg.push_back(Seg(b, a));
	for (int i = 0; i < pt1.size(); i++) {
		Pt p = pt1[i];
		Pt U((c.x - b.x)*De / b.di(c), (c.y - b.y)*De / b.di(c));
		Pt q(p.x + U.y, p.y - U.x);
		Seg s(p, q); seg.push_back(s);
	} 
	seg.push_back(Seg(c, d));	

	vector<Quad> quads;
	for (int i = 1; i < seg.size(); i++) {
		Pt p = seg[i - 1].A; Pt q = seg[i - 1].B; Pt r = seg[i].A; Pt s = seg[i].B;
		Quad q_(p, q, s, r); quads.push_back(q_);
	}
	return quads;
}



/*	OF GUI METHODS	*/


void ofApp::keyPressed(int key){
	if (key == 'r' || key == 'R') {
		//original figure
		iniptvec = oriptvec;

		//cross spine
		spinehorseg.setup(Pt(500, ofGetHeight() / 2), Pt(1400, ofGetHeight() / 2));
		spineverseg.setup(Pt(950, 200), Pt(950, ofGetHeight() - 200));

		//smooth spine 
		Pt p0(500, 450); Pt p1(600, 450); Pt p2(700, 450);
		Pt p3(800, 450); Pt p4(900, 450); Pt p5(1000, 450);
		Pt p6(1100, 450); Pt p7(1200, 450); inismoothspinept.clear();
		inismoothspinept.push_back(p0); inismoothspinept.push_back(p1); inismoothspinept.push_back(p2);
		inismoothspinept.push_back(p3); inismoothspinept.push_back(p4); inismoothspinept.push_back(p5);
		inismoothspinept.push_back(p6); inismoothspinept.push_back(p7);
	}
	if (key == 's' || key == 'S') {
		global_image_counter++;
		ofImage screenshot;
		screenshot.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		screenshot.saveImage("screenshot" + to_string(global_image_counter) + ".png");
	}
	if (key == 'g' || key == 'G') { 
		intsubdivgeneratequads.clear();
		generatetreesystem = 0;
		generatesubdivsystem = 1; 		
	}
	if (key == 'h' || key == 'H') {
		plotsubdivquad.clear();
		intsubdivgeneratequads.clear();
		generatesubdivsystem = 0;
		generatetreesystem = 1;
	}
	
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y ){
	float S = 35;
	if (controlpts == true) {
		for (int i = 0; i < iniptvec.size(); i++) {
			Pt m(x, y);	if (m.di(iniptvec[i]) < S) { iniptvec[i].locked = 1; }
		}
		for (int i = 0; i < iniptvec.size(); i++) {
			if (iniptvec[i].di(Pt(x, y)) > S) {
				iniptvec[i].locked = 0;
			}
		}
	}
	
	if (spinehorseg.A.di(Pt(x, y)) < S) { spinehorseg.A.locked = 1; }	else { spinehorseg.A.locked = 0; }
	if (spinehorseg.B.di(Pt(x, y)) < S) { spinehorseg.B.locked = 1; }	else { spinehorseg.B.locked = 0; }
	if (spineverseg.A.di(Pt(x, y)) < S) { spineverseg.A.locked = 1; }	else { spineverseg.A.locked = 0; }
	if (spineverseg.B.di(Pt(x, y)) < S) { spineverseg.B.locked = 1; }	else { spineverseg.B.locked = 0; }

	for (int i = 0; i < inismoothspinept.size(); i++) {
		if (inismoothspinept[i].di(Pt(x, y)) < 30) { (inismoothspinept[i].locked = 1); }
		else { inismoothspinept[i].locked = 0; }
	}
}

void ofApp::mouseDragged(int x, int y, int button){
	for (int i = 0; i < iniptvec.size(); i++) { 
		if (iniptvec[i].locked==1) { iniptvec[i].setup(x, y); }
	}

	if (spinehorseg.A.locked == 1) { spinehorseg.A.setup(x, y); }
	if (spinehorseg.B.locked == 1) { spinehorseg.B.setup(x, y); }

	if (spineverseg.A.locked == 1) { spineverseg.A.setup(x, y); }
	if (spineverseg.B.locked == 1) { spineverseg.B.setup(x, y); }

	for (int i = 0; i < inismoothspinept.size(); i++) {
		if (inismoothspinept[i].locked == 1) { inismoothspinept[i].setup(x, y); }
	}

}

void ofApp::mousePressed(int x, int y, int button){
	for (int i = 0; i < iniptvec.size(); i++) {
		if (iniptvec[i].locked == 1) { iniptvec[i].setup(x, y); }
	}
}

void ofApp::mouseReleased(int x, int y, int button){
	for (int i = 0; i < iniptvec.size(); i++) {
		if (iniptvec[i].locked == 1) { 
			iniptvec[i].setup(x, y); 
			iniptvec[i].locked = 0; 
		}
	}
	for (int i = 0; i < iniptvec.size(); i++) {
		iniptvec[i].locked = 0;
	}
}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){ 

}




/*	NS METHODS	*/

Pt ofApp::intxPt(Pt p, Pt q, Pt r, Pt s) {
	float a1 = q.y - p.y; float b1 = p.x - q.x;	float c1 = a1*q.x + b1*q.y;
	float a2 = s.y - r.y; float b2 = r.x - s.x; float c2 = a2*s.x + b2*s.y;
	float det = a1*b2 - a2*b1; if (det == 0) { return Pt(-100, -100); }
	float mx = (c1*b2 - c2*b1) / det; float my = (c2*a1 - c1*a2) / det;
	return Pt(mx, my);
}

Pt ofApp::intxPt2(Pt p, Pt q, Pt r, Pt s) {
	float a1 = q.y - p.y; float b1 = p.x - q.x;	float c1 = a1*q.x + b1*q.y;
	float a2 = s.y - r.y; float b2 = r.x - s.x; float c2 = a2*s.x + b2*s.y;
	float det = a1*b2 - a2*b1; if (det == 0) { return Pt(-100, -100); }
	float mx = (c1*b2 - c2*b1) / det; float my = (c2*a1 - c1*a2) / det;
	Pt I(mx, my);
	if (abs(I.di(r) + I.di(s) - r.di(s)) < 1) { return Pt(mx, my); }
	else { return Pt(-100, -100); }
}

Pt ofApp::intxPt4(Pt p, Pt q, Pt r, Pt s) {
	float a1 = q.y - p.y; float b1 = p.x - q.x;	float c1 = a1*q.x + b1*q.y;
	float a2 = s.y - r.y; float b2 = r.x - s.x; float c2 = a2*s.x + b2*s.y;
	float det = a1*b2 - a2*b1; if (det == 0) { return Pt(-100, -100); }
	float mx = (c1*b2 - c2*b1) / det; float my = (c2*a1 - c1*a2) / det;
	Pt I(mx, my);
	if ((abs(I.di(r) + I.di(s) - r.di(s)) < 1) && (abs(I.di(p) + I.di(q) - p.di(q)) < 1)) {
		return Pt(mx, my); 
	}
	else { return Pt(-100, -100); }
}

int ofApp::doesintx(Pt p, Pt q, Pt r, Pt s) {
	float a1 = q.y - p.y; float b1 = p.x - q.x;	float c1 = a1*q.x + b1*q.y;
	float a2 = s.y - r.y; float b2 = r.x - s.x; float c2 = a2*s.x + b2*s.y;
	float det = a1*b2 - a2*b1; if (det == 0) { return 0; }
	float mx = (c1*b2 - c2*b1) / det; float my = (c2*a1 - c1*a2) / det;
	Pt I(mx, my);
	if (abs(I.di(r) + I.di(s) - r.di(s)) < 1) { return 1; }
	else { return 0; }
}

/*	angular bisector at B for triangle ABC	*/
Pt ofApp::initPeripheralSys(Pt p, Pt q, Pt r, float g) {
	Pt u_((q.x - p.x) / p.di(q), (q.y - p.y) / p.di(q)); Pt u(-u_.y, u_.x);
	Pt v_((r.x - q.x) / r.di(q), (r.y - q.y) / r.di(q)); Pt v(-v_.y, v_.x);
	Pt pq((p.x + q.x) / 2, (p.y + q.y) / 2);
	Pt qr((q.x + r.x) / 2, (q.y + r.y) / 2);
	Pt P1(p.x + u.x*g, p.y + u.y*g); Pt Q(q.x + u.x*g, q.y + u.y*g);
	Pt P2(q.x + v.x*g, q.y + v.y*g); Pt R(r.x + v.x*g, r.y + v.y*g);
	Pt I=intxPt(P1, Q, P2, R);
	return I;
}

float ofApp::heron(Pt a, Pt b, Pt c) {
	float l = a.di(b);
	float m = a.di(c);
	float n = c.di(b);
	float s = (l + m + n) / 2;
	float ar = sqrt(s*(s - l)*(s - m)*(s - n));
	return ar;
}

int ofApp::heronContains(Pt p, Pt a, Pt b, Pt c) {
	float ar = heron(a, b, c);
	float ar0 = heron(a, p, b);
	float ar1 = heron(b, p, c);
	float ar2 = heron(c, p, a);
	float diff = abs(ar - (ar0 + ar1 + ar2));
	if (diff < 10) {
		return 1;
	}
	else {
		return 0;
	}
}

Pt ofApp::proj(Pt a, Pt b, Pt c) {
	//proj b on ac
	Pt u(a.x - c.x, a.y - c.y); Pt v(b.x - c.x, b.y - c.y);
	float e = (u.x*v.x + u.y*v.y) / (c.di(a)*c.di(a));	
	Pt r(c.x + (e*u.x), c.y + (e*u.y));
	return r;
}

/* init subdiv process  */
vector<Quad> ofApp::initSubdiv(Pt a, Pt b, Pt c, Pt d, int t, vector<Quad> quad) {
	subdivQuadVec.clear(); 
	Quad q(a,b,c,d);
	subdiv(q, 0, t);
	//subdivVec.push_back(subdivQuadVec);
	//quad.push_back(subdivQuadVec);
	for (int i = 0; i < subdivQuadVec.size(); i++) {
		quad.push_back(subdivQuadVec[i]);
	}
	subdivQuadVec.clear();

	vector<Quad> fquad;
	for (int i = 0; i < quad.size(); i++) {
		Quad Q = quad[i];
		Pt a = Q.A; Pt b = Q.B; Pt c = Q.C; Pt d = Q.D;

		Pt t((b.x - a.x)*spinecorrde / a.di(b), (b.y - a.y)*spinecorrde / a.di(b));
		Pt u((c.x - b.x)*spinecorrde / b.di(c), (c.y - b.y)*spinecorrde / b.di(c));
		Pt v((d.x - c.x)*spinecorrde / c.di(d), (d.y - c.y)*spinecorrde / c.di(d));
		Pt w((a.x - d.x)*spinecorrde / a.di(d), (a.y - d.y)*spinecorrde / a.di(d));

		Pt m(a.x + t.x*cos(PI / 4) - t.y*sin(PI / 4), a.y + t.x*sin(PI / 4) + t.y*cos(PI / 4));
		Pt n(b.x + u.x*cos(PI / 4) - u.y*sin(PI / 4), b.y + u.x*sin(PI / 4) + u.y*cos(PI / 4));
		Pt o(c.x + v.x*cos(PI / 4) - v.y*sin(PI / 4), c.y + v.x*sin(PI / 4) + v.y*cos(PI / 4));
		Pt p(d.x + w.x*cos(PI / 4) - w.y*sin(PI / 4), d.y + w.x*sin(PI / 4) + w.y*cos(PI / 4));

		fquad.push_back(Quad(m, n, o, p));
	}
	return fquad;
}

/*	recursive function for subdividion process	*/
void ofApp::subdiv(Quad Q, int t, int w) {
	Pt a, b, c, d;
	a.setup(Q.pts[0].x, Q.pts[0].y);
	b.setup(Q.pts[1].x, Q.pts[1].y);
	c.setup(Q.pts[2].x, Q.pts[2].y);
	d.setup(Q.pts[3].x, Q.pts[3].y);
	int g = (int)ofRandom(0, 2);
	Quad R, S; Pt m, n;
	if (g == 0) {
		m.setup((a.x + b.x) / 2, (a.y + b.y) / 2);
		n.setup((c.x + d.x) / 2, (c.y + d.y) / 2);
		R.setupPreservePts(a, m, n, d);
		S.setupPreservePts(m, b, c, n);
	}
	else {
		m.setup((b.x + c.x) / 2, (b.y + c.y) / 2);
		n.setup((a.x + d.x) / 2, (a.y + d.y) / 2);
		R.setupPreservePts(a, b, m, n);
		S.setupPreservePts(n, m, c, d);
	}
	if (t < w) {
		t++;
		subdiv(R, t, w);
		subdiv(S, t, w);
	}
	else {
		subdivQuadVec.push_back(R);
		subdivQuadVec.push_back(S);
	}
}



