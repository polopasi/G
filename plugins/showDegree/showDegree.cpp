#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
    // sum all the adjacent of all vertex, then divide by the number
    // for each objects in scene()
	if (scene()->objects().size() > 0) {
	    int numVertex = scene()->objects()[0].vertices().size();
	    int degreeSum = 0;
	    vector <bool> vertex(numVertex, false);
	    //for each faces
	    for (int i = 0; i < scene()->objects()[0].faces().size(); ++i) {
	        degreeSum = degreeSum + scene()->objects()[0].faces()[i].numVertices();
	    }
        degreeToShow = float(degreeSum)/float(numVertex);
    }
    
	
}

void ShowDegree::preFrame()
{
	
}

void ShowDegree::postFrame()
{
    // prints the degree numbers in the view
    QFont font;
    font.setPixelSize(15);
    painter.begin(glwidget());
    painter.setFont(font);
    painter.drawText(10, 20, QString(QString::number(degreeToShow)));
    painter.end();	
	
}

void ShowDegree::onObjectAdd()
{
	
}

bool ShowDegree::drawScene()
{
	return false; // return true only if implemented
}

bool ShowDegree::drawObject(int)
{
	return false; // return true only if implemented
}

bool ShowDegree::paintGL()
{
	return false; // return true only if implemented
}

void ShowDegree::keyPressEvent(QKeyEvent *)
{
	
}

void ShowDegree::mouseMoveEvent(QMouseEvent *)
{
	
}

