#include "iluminationFragment.h"
#include "glwidget.h"
#include <QCoreApplication>
#include <QVector4D>

void IluminationFragment::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../iluminationFragment/lighting4.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../iluminationFragment/lighting4.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
}

void IluminationFragment::preFrame()
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
	
}

void IluminationFragment::postFrame()
{
	
}

void IluminationFragment::onObjectAdd()
{
	
}

bool IluminationFragment::drawScene()
{
	return false; // return true only if implemented
}

bool IluminationFragment::drawObject(int)
{
	return false; // return true only if implemented
}

bool IluminationFragment::paintGL()
{
	return false; // return true only if implemented
}

void IluminationFragment::keyPressEvent(QKeyEvent *)
{
	
}

void IluminationFragment::mouseMoveEvent(QMouseEvent *)
{
	
}

