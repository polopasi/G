#include "modelInfo2.h"
#include "glwidget.h"

void ModelInfo2::onPluginLoad()
{
	
}

void ModelInfo2::preFrame()
{
	
}

void ModelInfo2::postFrame()
{
    if (scene()->objects().size() > 0) {
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
	    
	    QFont font;
        font.setPixelSize(15);
        painter.begin(glwidget());
        painter.setFont(font);
        painter.drawText(10, 20, QString("Objectes: " + QString::number(scene()->objects().size()))); 
        painter.drawText(10, 40, QString("Poligons: " + QString::number(nPoligons))); 
        painter.drawText(10, 60, QString("Vertexs: " + QString::number(nVertex)));
        painter.drawText(10, 80, QString("Percentatge de triangles: " + QString::number(100*float(triangles/nPoligons)) + "%"));              
        painter.end();
    }
}

void ModelInfo2::onObjectAdd()
{
	
}

bool ModelInfo2::drawScene()
{
	return false; // return true only if implemented
}

bool ModelInfo2::drawObject(int)
{
	return false; // return true only if implemented
}

bool ModelInfo2::paintGL()
{
	return false; // return true only if implemented
}

void ModelInfo2::keyPressEvent(QKeyEvent *)
{
	
}

void ModelInfo2::mouseMoveEvent(QMouseEvent *)
{
	
}

