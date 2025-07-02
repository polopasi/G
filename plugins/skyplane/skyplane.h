#ifndef _SKYPLANE_H
#define _SKYPLANE_H

#include "plugin.h" 

class Skyplane: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 void onObjectAdd();
	 bool drawScene();
	 bool drawObject(int);

	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
	 void mouseMoveEvent(QMouseEvent *);
  private:
	// add private methods and attributes here
    QOpenGLShaderProgram* programSky;
    QOpenGLShaderProgram* programMirror;
    QOpenGLShader* vsSky;
    QOpenGLShader* fsSky;
    QOpenGLShader* vsMirror;
    QOpenGLShader* fsMirror;
    GLuint textureId0;    
    
    GLuint VAO_sky_quad;
};

#endif
