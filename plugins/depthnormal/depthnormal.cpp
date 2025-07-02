#include "depthnormal.h"
#include "glwidget.h"

void Depthnormal::onPluginLoad()
{
	GLWidget &g = *glwidget();
    g.makeCurrent();

    // Carregar shader, compile & link
    vsDepth = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsDepth->compileSourceFile(g.getPluginPath() + "/../depthnormal/depth.vert");

    fsDepth = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsDepth->compileSourceFile(g.getPluginPath() + "/../depthnormal/depth.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vsDepth);
    program->addShader(fsDepth);
    program->link();
    if (!program->isLinked())
        std::cout << "Shader link error" <<  program->log().toUtf8().constData() << std::endl;
        
    vsNormal = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsNormal->compileSourceFile(g.getPluginPath()+"/../depthnormal/normal.vert");

    fsNormal = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsNormal->compileSourceFile(g.getPluginPath()+"/../depthnormal/normal.frag");

    programNormal = new QOpenGLShaderProgram(this);
    programNormal->addShader(vsNormal);
    programNormal->addShader(fsNormal);
    programNormal->link();
    
    if (!programNormal->link()) {
        qWarning() << "Shader link failed:" << program->log();
    }
}

void Depthnormal::preFrame()
{
	
}

void Depthnormal::postFrame()
{
	
}

void Depthnormal::onObjectAdd()
{
	
}

bool Depthnormal::drawScene()
{
	return false; // return true only if implemented
}

bool Depthnormal::drawObject(int)
{
	return false; // return true only if implemented
}

bool Depthnormal::paintGL()
{

    GLWidget & g = *glwidget();
    float ar = (g.width() / g.height());
    glViewport(0, g.height()/4, g.width()/2, g.height()/2);
    camera()->setAspectRatio(ar);
    
    program->bind();
    QMatrix4x4 PVM = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", PVM);

    if (drawPlugin()) drawPlugin()->drawScene();
    
    
    glViewport(g.width()/2, g.height()/4, g.width()/2, g.height()/2);
    
    programNormal->bind();
    program->setUniformValue("modelViewProjectionMatrix", PVM);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());

    if (drawPlugin()) drawPlugin()->drawScene();
    g.glBindVertexArray(0); 
    return true;
}

void Depthnormal::keyPressEvent(QKeyEvent *)
{
	
}

void Depthnormal::mouseMoveEvent(QMouseEvent *)
{
	
}

