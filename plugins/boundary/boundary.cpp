#include "boundary.h"
#include "glwidget.h"

void Boundary::onPluginLoad()
{
	calculateInformation();
}

void Boundary::preFrame()
{
	
}

void Boundary::postFrame()
{
	
}

void Boundary::calculateInformation() {
	for(unsigned int i=0; i<scene()->objects().size(); i++) {	
		const Object& obj = scene()->objects()[i];
		int nVertex = obj.vertices().size();
		int noBorderAresta = 0;
        /*
         * To calculate the number of arists in the model, we will create an adjacencyMatrix
         * that stores if given two vertex v_0 and v_1, they have been counted. We iterate for
         * each Face face (with index f) in the model; we know that each Face stores 3 or more
         * vertex, for example v_0-v_1-v_2 such that v_0 is adjacent with v_1 and v_1 is adjacent
         * with v_2 and v_2 is adjacent with v_0. This way, we check if adjacencyMatrix[v_i][v_i+1]
         * is set to false or true.
        */
        int nArestes = 0;
        vector <vector<int>> adjacencyMatrix(nVertex, vector<int>(nVertex, false));
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
                if (adjacencyMatrix[v0][v1] == 0) {            
                    adjacencyMatrix[v0][v1] = 1;
                    adjacencyMatrix[v1][v0] = 1;
                    ++nArestes;
                } else if (adjacencyMatrix[v0][v1] == 1) {            
                    adjacencyMatrix[v0][v1] = 2;
                    adjacencyMatrix[v1][v0] = 2;
                    ++noBorderAresta;
                }
            }
        }
        cout << "E=" << nArestes << endl;
        cout << "Border=" << nArestes - noBorderAresta << endl;
	}

}

void Boundary::onObjectAdd()
{
	calculateInformation();
}

bool Boundary::drawScene()
{
	return false; // return true only if implemented
}

bool Boundary::drawObject(int)
{
	return false; // return true only if implemented
}

bool Boundary::paintGL()
{
	return false; // return true only if implemented
}

void Boundary::keyPressEvent(QKeyEvent *)
{
	
}

void Boundary::mouseMoveEvent(QMouseEvent *)
{
	
}

