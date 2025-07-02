#include "wire.h"
#include "glwidget.h"

void Wire::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../wire/basicIlumination.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../wire/basicIlumination.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
	
}

void Wire::preFrame()
{
	
}

void Wire::postFrame()
{
	
}

void Wire::onObjectAdd()
{
	
}

bool Wire::drawScene()
{
	return false; // return true only if implemented
}

bool Wire::drawObject(int)
{
	return false; // return true only if implemented
}

bool Wire::paintGL()
{
    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());  
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix());  
    program->setUniformValue("paintBlack", 0.0f);      

    GLWidget & g = *glwidget();
    // draw default scene
    g.glClearColor(1,1,1,0);
    if (drawPlugin()) drawPlugin()->drawScene();   
    
    program->setUniformValue("paintBlack", 1.0f);  
    g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // random number, I have no idea what float to use
    g.glPolygonOffset(20.0, 20.0);
    if (drawPlugin()) drawPlugin()->drawScene();    
    g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    g.glPolygonOffset(0.0, 0.0);
    
    
    
    return true;
}

void Wire::keyPressEvent(QKeyEvent *)
{
	
}

void Wire::mouseMoveEvent(QMouseEvent *)
{
	
}

