// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
//
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "objectSelect.h"
#include <QCoreApplication>


void ObjectSelect::encodeID(const unsigned int i, GLubyte * color) {
	// complete this method to encode the object index (i) as a color
    GLubyte R = i*255; // complete
    GLubyte G = (i + 1)*(i + 1)*1000; // complete
    GLubyte B = (i + 1)*(i + 1)*(i + 1)*1000; // complete
    color[0] = R;
    color[1] = G;
    color[2] = B;
    color[3] = 255;
}

void ObjectSelect::decodeID(const GLubyte *color, unsigned int &i) {
	// complete this method to decode the object index from the color 
    unsigned int R = (unsigned int) color[0];
    unsigned int G = (unsigned int) color[1];
    unsigned int B = (unsigned int) color[2];
	// compute i from R, G, B
    i = R/255.; 
}

void ObjectSelect::postFrame() {
    GLWidget &g = *glwidget();
    g.makeCurrent();
    if (scene()->selectedObject() != -1) {
        bindCubeShaders();
        g.glBindVertexArray (VAO_box);
        g.glDrawArrays(GL_LINE_STRIP, 0, 36);
        g.glBindVertexArray(0);	
    }
}

void ObjectSelect::onPluginLoad() {
    std::cout << "[ObjectSelect plugin] Ctrl + Right Click - Select object" << std::endl;

    GLWidget &g = *glwidget();
    g.makeCurrent();

    // Carregar shader, compile & link
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath() + "/../objectSelect/objectSelect.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    if (!program->isLinked())
        std::cout << "Shader link error" << std::endl;
        
    // first we load all shaders in program. We will need one vertex and fragment shader for the bounding box
    // the shaders boundingBox paints the box of the scene with the Phong illumination, then scales and translates
    // the box so it fits the whole scene defined by scene()->boundingBox()
    // Carregar shader, compile & link 
    vsBox = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsBox->compileSourceFile(g.getPluginPath()+"/../objectSelect/boundingBox.vert");

    fsBox = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsBox->compileSourceFile(g.getPluginPath()+"/../objectSelect/boundingBox.frag");

    programBox = new QOpenGLShaderProgram(this);
    programBox->addShader(vsBox);
    programBox->addShader(fsBox);
    programBox->link();
    
    if (!programBox->link()) {
        qWarning() << "Shader link failed:" << program->log();
    }
    

    

    // Create & bind empty VAO
    g.glGenVertexArrays(1, &VAO_box);
    // we bind every call we will do to VAO_box
    g.glBindVertexArray(VAO_box);

    // now we create VBO for coordinates, normals and color
    // it's important to keep in mind the layouts of the vertex shader:
    /*
     * layout (location = 0) in vec3 vertex;
     * layout (location = 1) in vec3 normal;
     * layout (location = 2) in vec3 color;
     * layout (location = 3) in vec2 texCoord;
    */

    // Create VBO with (x,y,z) coordinates
    float coords[] = { 
	      // cara inferior
	      0, 0, 0,      1, 0, 0,     0, 0, 1,
	      1, 0, 1,      1, 0, 0,     0, 0, 1,
	      
	      // cara superior
	      0, 1, 0,      1, 1, 0,     0, 1, 1,  		      
	      1, 1, 1,      1, 1, 0, 	 0, 1, 1,
	      
	      // cara frente
	      0, 0, 0,      1, 0, 0,     0, 1, 0,
	      1, 1, 0,      0, 1, 0,     1, 0, 0,
	 
	      // cara trasera
	      0, 0, 1,      1, 0, 1,     0, 1, 1,
	      1, 0, 1,      1, 1, 1,     0, 1, 1,
	      
	      // cara izquierda
	      0, 0, 0,      0, 1, 0,     0, 0, 1,
	      0, 0, 1,      0, 1, 0,     0, 1, 1,
	       
	      // cara derecha
	      1, 0, 0,      1, 0, 1,     1, 1, 0,
	      1, 1, 1,      1, 0, 1,     1, 1, 0
                       };

    GLuint VBO_coords;
    g.glGenBuffers(1, &VBO_coords);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);
    
    float normals[] = { 
          0, -1, 0,      0, -1, 0,     0, -1, 0,
	      0, -1, 0,      0, -1, 0,     0, -1, 0,
	      
	      // cara superior
	      0, 1, 0,      0, 1, 0,     0, 1, 0,  		      
	      0, 1, 0,      0, 1, 0, 	 0, 1, 0,
	      
	      // cara frente
	      0, 0, -1,      0, 0, -1,     0, 0, -1,
	      0, 0, -1,      0, 0, -1,     0, 0, -1,
	 
	      // cara trasera
	      0, 0, 1,      0, 0, 1,     0, 0, 1,
	      0, 0, 1,      0, 0, 1,     0, 0, 1,
	      
	      // cara izquierda
	      1, 0, 0,       1, 0, 0,     1, 0, 0,
	      1, 0, 0,       1, 0, 0,     1, 0, 0,
	       
	      // cara derecha
	      -1, 0, 0,      -1, 0, 0,     -1, 0, 0,
	      -1, 0, 0,      -1, 0, 0,     -1, 0, 0
      };

    GLuint VBO_normals;
    g.glGenBuffers(1, &VBO_normals);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_normals);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);
    g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(1);
    
    float color[] = { 
          1, 0, 0,      1, 0, 0,     1, 0, 0,
	      1, 0, 0,      1, 0, 0,     1, 0, 0,
	      
	      // cara superior
	      1, 0, 0,      1, 0, 0,     1, 0, 0,  		      
	      1, 0, 0,      1, 0, 0, 	 1, 0, 0,
	      
	      // cara frente
	      1, 0, 0,      1, 0, 0,     1, 0, 0,
	      1, 0, 0,      1, 0, 0,     1, 0, 0,
	 
	      // cara trasera
	      1, 0, 0,      1, 0, 0,     1, 0, 0,
	      1, 0, 0,      1, 0, 0,     1, 0, 0,
	      
	      // cara izquierda
	      1, 0, 0,      1, 0, 0,     1, 0, 0,
	      1, 0, 0,      1, 0, 0,     1, 0, 0,
	       
	      // cara derecha
	      1, 0, 0,      1, 0, 0,     1, 0, 0,
	      1, 0, 0,      1, 0, 0,     1, 0, 0
      };

    GLuint VBO_color;
    g.glGenBuffers(1, &VBO_color);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_color);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);
    g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(1);
    
    // this call is only needed to stop binding to the VAO
    g.glBindVertexArray(0);
}


// pre: program must be linked
// post: binds the program and sets all its uniforms that the shader lighting2 needs
void ObjectSelect::bindCubeShaders()
{
	
    programBox->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programBox->setUniformValue("modelViewProjectionMatrix", MVP);
    programBox->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
    programBox->setUniformValue("modelViewMatrix", camera()->viewMatrix());  
    
	
	int seleccionat = scene()->selectedObject();
	Object obj = scene()->objects()[seleccionat];
	Box b = obj.boundingBox();
	programBox->setUniformValue("boundingBoxMin", QVector3D(b.min()));
	programBox->setUniformValue("boundingBoxMax", QVector3D(b.max()));
	
}

void ObjectSelect::selectDraw(GLWidget & g) {
    // (b)
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    // (c)
    program->bind();



    // (d)
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);

    // (e)
    for (unsigned int i=0; i<scene()->objects().size(); ++i){
        GLubyte color[4];
        encodeID(i,color);
        program->setUniformValue("color", QVector4D(color[0]/255.0, color[1]/255., color[2]/255., 1.0));
        drawPlugin()->drawObject(i);
    }
    
}

void ObjectSelect::mouseReleaseEvent(QMouseEvent* e) {
    // (a)
    if (!(e->button() & Qt::RightButton)) return;
    if (e->modifiers() & (Qt::ShiftModifier)) return;
    if (!(e->modifiers() & Qt::ControlModifier)) return;

    GLWidget &g = *glwidget();
    g.makeCurrent();

    // (b) through (e)
    selectDraw(g);

    // (f)
    int x = e->x();
    int y = g.height() - e->y();
    GLubyte read[4];
    glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);

    // (g)
    if(read[3] == 255){
        // Not the background, thus an object has been selected
        unsigned int tmp;
        decodeID(read, tmp);
        scene()->setSelectedObject((int) tmp);
        std::cout << tmp << std::endl;
    } else {
        scene()->setSelectedObject(-1);
        std::cout << -1 << std::endl;
    }
    
    // (h)
    g.update();
}
