#include "skyplane.h"
#include "glwidget.h"
#include <iostream>

void Skyplane::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vsMirror = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsMirror->compileSourceFile(g.getPluginPath()+"/../skyplane/mirror.vert");

    fsMirror = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsMirror->compileSourceFile(g.getPluginPath()+"/../skyplane/mirror.frag");

    programMirror = new QOpenGLShaderProgram(this);
    programMirror->addShader(vsMirror);
    programMirror->addShader(fsMirror);
    programMirror->link();
    
    vsSky = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsSky->compileSourceFile(g.getPluginPath()+"/../skyplane/sky.vert");

    fsSky = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsSky->compileSourceFile(g.getPluginPath()+"/../skyplane/sky.frag");

    programSky = new QOpenGLShaderProgram(this);
    programSky->addShader(vsSky);
    programSky->addShader(fsSky);
    programSky->link();
    
    // Load Texture 1
	QString filename = QFileDialog::getOpenFileName(0, "Open Image", g.getPluginPath()+"/../skyplane", "Image file (*.png *.jpg)");	
	QImage img0(filename);	
	QImage im0 = img0.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.glActiveTexture(GL_TEXTURE0);
	g.glGenTextures( 1, &textureId0);
	g.glBindTexture(GL_TEXTURE_2D, textureId0);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glBindTexture(GL_TEXTURE_2D, 0);
	
	// defining VAO and VBO
	g.glGenVertexArrays(1, &VAO_sky_quad);
    // we bind every call we will do to VAO_sky_quad
    g.glBindVertexArray(VAO_sky_quad);
    // now we create VBO only for coordinates, because sky.vert only has one layout (location = 0)
    // the exercise tells us to create a quad in clip space that covers all screen, and it's close
    // to the far plane. Due to clip coordinate going from [-1, 1]:
    float coordinates[] = { -1, -1, .999, 
                        1, -1, .999, 
                       -1,  1, .999, 
                        1,  1, .999};
    GLuint VBO_coords;
    g.glGenBuffers(1, &VBO_coords);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(coordinates), coordinates, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);
    g.glBindVertexArray(0);
}

void Skyplane::preFrame()
{
	
}

void Skyplane::postFrame()
{
	
}

void Skyplane::onObjectAdd()
{
	
}

bool Skyplane::drawScene()
{
	return false; // return true only if implemented
}

bool Skyplane::drawObject(int)
{
	return false; // return true only if implemented
}

bool Skyplane::paintGL()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    
    
    // bind textures
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureId0);
    

    programMirror->bind();
    QMatrix4x4 PVM = camera()->projectionMatrix() * camera()->viewMatrix();
    programMirror->setUniformValue("modelViewProjectionMatrix", PVM);
    programMirror->setUniformValue("modelViewMatrix", camera()->viewMatrix());
    programMirror->setUniformValue("sampler0", 0);
	if (drawPlugin()) drawPlugin()->drawScene();
	
	
    programSky->bind();
    programSky->setUniformValue("modelViewProjectionMatrix", PVM);
    programSky->setUniformValue("modelViewMatrix", camera()->viewMatrix());
    programSky->setUniformValue("sampler0", 0);
    g.glBindVertexArray (VAO_sky_quad);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);	
	
    return true;
}

void Skyplane::keyPressEvent(QKeyEvent *)
{
	
}

void Skyplane::mouseMoveEvent(QMouseEvent *)
{
	
}

