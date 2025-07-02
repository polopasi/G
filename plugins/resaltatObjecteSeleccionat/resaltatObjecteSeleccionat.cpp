#include "resaltatObjecteSeleccionat.h"
#include "glwidget.h"
#include <QCoreApplication>
#include <QVector4D>
#include <QVector3D>

void ResaltatObjecteSeleccionat::onPluginLoad()
{
    seleccionat = 0;
    scene()->setSelectedObject(seleccionat);    

    // first we load all shaders in program. We will need one vertex and fragment shader for the bounding box
    // the shaders boundingBox paints the box of the scene with the Phong illumination, then scales and translates
    // the box so it fits the whole scene defined by scene()->boundingBox()
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../resaltatObjecteSeleccionat/boundingBox.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../resaltatObjecteSeleccionat/boundingBox.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    
    if (!program->link()) {
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

void ResaltatObjecteSeleccionat::preFrame()
{
}

void ResaltatObjecteSeleccionat::postFrame()
{

    //seleccionat = seleccionat%(scene()->objects().size());
    //scene()->setSelectedObject(seleccionat);
    
    GLWidget &g = *glwidget();
    g.makeCurrent();
    if (scene()->objects().size() > 0) {
        bindCubeShaders();
        g.glBindVertexArray (VAO_box);
        g.glDrawArrays(GL_LINE_STRIP, 0, 36);
        g.glBindVertexArray(0);	
    }
}


bool ResaltatObjecteSeleccionat::drawScene()
{
	return false; // return true only if implemented
}

bool ResaltatObjecteSeleccionat::drawObject(int)
{
	return false; // return true only if implemented
}

bool ResaltatObjecteSeleccionat::paintGL()
{
    return false;
}

void ResaltatObjecteSeleccionat::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Left) --seleccionat;
    if (event->key() == Qt::Key_Right) ++seleccionat;
    // this if is neccessary to prevent a Floating Point Exception
    if (scene()->objects().size() != 0) seleccionat = seleccionat%(scene()->objects().size());
    scene()->setSelectedObject(seleccionat);
    cout << seleccionat << endl;
}

// pre: program must be linked
// post: binds the program and sets all its uniforms that the shader lighting2 needs
void ResaltatObjecteSeleccionat::bindCubeShaders()
{
	
    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());  
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix());  
    
	
	int sel = scene()->selectedObject();
	Object obj = scene()->objects()[sel];
	Box b = obj.boundingBox();
	program->setUniformValue("boundingBoxMin", QVector3D(b.min()));
	program->setUniformValue("boundingBoxMax", QVector3D(b.max()));
	
}


