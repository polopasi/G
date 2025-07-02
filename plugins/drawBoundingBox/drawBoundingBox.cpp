#include "drawBoundingBox.h"
#include "glwidget.h"
#include <QCoreApplication>
#include <QVector4D>
#include <QVector3D>

void DrawBoundingBox::onPluginLoad()
{

    // first we load all shaders in program. We will need one vertex and fragment shader for the bounding box
    // the shaders boundingBox paints the box of the scene with the Phong illumination, then scales and translates
    // the box so it fits the whole scene defined by scene()->boundingBox()

    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../drawBoundingBox/boundingBox.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../drawBoundingBox/boundingBox.frag");

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

void DrawBoundingBox::preFrame()
{
}

void DrawBoundingBox::postFrame()
{
	
}

void DrawBoundingBox::onObjectAdd()
{
	
}

bool DrawBoundingBox::drawScene()
{
	return false; // return true only if implemented
}

bool DrawBoundingBox::drawObject(int)
{
	return false; // return true only if implemented
}

bool DrawBoundingBox::paintGL()
{

    GLWidget & g = *glwidget();

    // draw default scene
    g.glClearColor(1,1,1,0);
    if (drawPlugin()) drawPlugin()->drawScene();    
    
    // draw cube and execute the custom function bindCubeShaders
    bindCubeShaders();
    g.glBindVertexArray (VAO_box);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 36);
    g.glBindVertexArray(0);	
    return true;
}

void DrawBoundingBox::keyPressEvent(QKeyEvent *)
{
	
}

// pre: program must be linked
// post: binds the program and sets all its uniforms that the shader lighting2 needs
void DrawBoundingBox::bindCubeShaders()
{
	
    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());  
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix());  
    
	program->setUniformValue("matAmbient", QVector4D(0.8, 0.8, 0.6,1));
	program->setUniformValue("matDiffuse", QVector4D(0.8, 0.8, 0.6,1));
	program->setUniformValue("matSpecular", QVector4D(1.0, 1.0, 1.0,1));
	program->setUniformValue("matShininess", float(64.0));
	program->setUniformValue("lightAmbient", QVector4D(0.1,0.1,0.1,1));
	program->setUniformValue("lightDiffuse", QVector4D(1,1,1,1));
	program->setUniformValue("lightSpecular", QVector4D(1,1,1,1));
	program->setUniformValue("lightPosition", QVector4D(0,0,0,1));
	
	Box b = scene()->boundingBox();
	
	program->setUniformValue("boundingBoxMin", QVector3D(b.min()));
	program->setUniformValue("boundingBoxMax", QVector3D(b.max()));
	
}

void DrawBoundingBox::mouseMoveEvent(QMouseEvent *)
{
	
}

