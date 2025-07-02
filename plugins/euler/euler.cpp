#include "euler.h"
#include "glwidget.h"

void Euler::onPluginLoad()
{
	calculateInformation();
}

void Euler::preFrame()
{
	
}

void Euler::postFrame()
{
	
}

void Euler::calculateInformation() {
	int nPoligons = 0;
	int nVertex = 0;
	for(unsigned int i=0; i<scene()->objects().size(); i++) {	
		const Object& obj = scene()->objects()[i];
		nPoligons = obj.faces().size();
		nVertex = obj.vertices().size();
        cout <<	"F=" << nPoligons << endl;
        cout << "V=" << nVertex << endl;
        /*
         * To calculate the number of arists in the model, we will create an adjacencyMatrix
         * that stores if given two vertex v_0 and v_1, they have been counted. We iterate for
         * each Face face (with index f) in the model; we know that each Face stores 3 or more
         * vertex, for example v_0-v_1-v_2 such that v_0 is adjacent with v_1 and v_1 is adjacent
         * with v_2 and v_2 is adjacent with v_0. This way, we check if adjacencyMatrix[v_i][v_i+1]
         * is set to false or true.
        */
        int nArestes = 0;
        vector <vector<bool>> adjacencyMatrix(nVertex, vector<bool>(nVertex, false));
        // for each face in model
        for(int f = 0; f < obj.faces().size(); ++f) {
            Face face = obj.faces()[f];
            int vertexInFace = face.numVertices();
            // for each vertex inside the range of vertex the face stores
            for (int v = 0; v < vertexInFace; ++v) {
                // we get two vertex v_i and v_i+1, 
                // such that if v_i+1 > vertexInFace, then v_0
                // otherwise, we would have an erroneous access in the array
                int v0 = face.vertexIndex(v);
                int v1 = face.vertexIndex((v + 1)%vertexInFace);
                if (!adjacencyMatrix[v0][v1]) {            
                    adjacencyMatrix[v0][v1] = true;
                    adjacencyMatrix[v1][v0] = true;
                    ++nArestes;
                }
            }
        }
        cout << "E=" << nArestes << endl;
        cout << "X=" << nPoligons + nVertex - nArestes << endl;
	}

}

void Euler::onObjectAdd()
{
	calculateInformation();
}

bool Euler::drawScene()
{
	return false; // return true only if implemented
}

bool Euler::drawObject(int)
{
	return false; // return true only if implemented
}

bool Euler::paintGL()
{
	return false; // return true only if implemented
}

void Euler::keyPressEvent(QKeyEvent *)
{
	
}

void Euler::mouseMoveEvent(QMouseEvent *)
{
	
}

