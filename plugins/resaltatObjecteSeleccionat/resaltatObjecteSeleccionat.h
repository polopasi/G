#ifndef _RESALTATOBJECTESELECCIONAT_H
#define _RESALTATOBJECTESELECCIONAT_H

#include "plugin.h" 

class ResaltatObjecteSeleccionat: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

	 bool drawScene();
	 bool drawObject(int);
	 bool paintGL();

	 void keyPressEvent(QKeyEvent *);
  private:
	// add private methods and attributes here
	void bindCubeShaders();
    GLuint VAO_box;
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* fs;  
    int seleccionat = 0;
};

#endif
