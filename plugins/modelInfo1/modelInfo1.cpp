#include "modelInfo1.h"
#include "glwidget.h"

void ModelInfo1::onPluginLoad()
{
	
}

void ModelInfo1::preFrame()
{
	
}

void ModelInfo1::postFrame()
{
	// escriu #objectes-carregats #poligons #vertex y %poligons-triangles
	cout << "====================" << endl;
	cout <<	"#objectes carregats: " << scene()->objects().size() << endl;
	
	int nPoligons = 0;
	int nVertex = 0;
	int triangles = 0;
	for(unsigned int i=0; i<scene()->objects().size(); i++) {	
		const Object& obj = scene()->objects()[i];
		nPoligons += obj.faces().size();
		nVertex += obj.vertices().size();
		
		// por cada face del modelo obj
		for (unsigned int j= 0; j < obj.faces().size(); ++j) {
			if(obj.faces()[j].numVertices() == 3) ++triangles;
		}	
	}
	cout <<	"#poligons: " << nPoligons << endl;
	cout << "#vertex: " << nVertex << endl;
	if (nPoligons > 0) cout << "triangles: " << 100*float(triangles/nPoligons) << '%' << endl;
	else cout << "triangles: " << 0 << endl;
}

void ModelInfo1::onObjectAdd()
{
	
}

bool ModelInfo1::drawScene()
{
	return false; // return true only if implemented
}

bool ModelInfo1::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo1::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo1::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo1::mouseMoveEvent(QMouseEvent *)
{
	
}
