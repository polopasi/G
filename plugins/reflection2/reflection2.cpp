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

#include "reflection2.h"
#include <QCoreApplication>
#include <QVector3D>

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Reflection2::onPluginLoad()
{
    GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../reflection2/reflection.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../reflection2/reflection.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    
    
    // Carregar shader, compile & link 
    vsMirror = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vsMirror->compileSourceFile(g.getPluginPath()+"/../reflection2/mirror.vert");

    fsMirror = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsMirror->compileSourceFile(g.getPluginPath()+"/../reflection2/mirror.frag");

    programMirror = new QOpenGLShaderProgram(this);
    programMirror->addShader(vsMirror);
    programMirror->addShader(fsMirror);
    programMirror->link();
    
    // Setup texture
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &textureOfReflection2);
    g.glBindTexture(GL_TEXTURE_2D, textureOfReflection2);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, IMAGE_WIDTH, IMAGE_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    // Resize to power-of-two viewport
    g.resize(IMAGE_WIDTH,IMAGE_HEIGHT);
}


void drawRect(GLWidget &g)
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        Point soil = g.scene()->boundingBox().min();
        
        // Create VBO with (x,y,z) coordinates
        float coords[] = { -soil.x(), soil.y(), -soil.z(), 
                            soil.x(), soil.y(), -soil.z(), 
                           -soil.x(), soil.y(),  soil.z(),
                            soil.x(), soil.y(),  soil.z()}; 

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}


void drawRect2(GLWidget &g)
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        Point soil = g.scene()->boundingBox().min();
        
        // Create VBO with (x,y,z) coordinates
        float coords[] = { -soil.x(), -soil.y(), soil.z(), 
                            soil.x(), -soil.y(), soil.z(), 
                           -soil.x(),  soil.y(), soil.z(),
                            soil.x(),  soil.y(), soil.z()}; 

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}



void drawRect3(GLWidget &g)
{
    static bool created = false;
    static GLuint VAO_rect;

    // 1. Create VBO Buffers
    if (!created)
    {
        created = true;
        

        // Create & bind empty VAO
        g.glGenVertexArrays(1, &VAO_rect);
        g.glBindVertexArray(VAO_rect);

        Point soil = g.scene()->boundingBox().min();
        
        // Create VBO with (x,y,z) coordinates
        float coords[] = { soil.x(), -soil.y(), -soil.z(), 
                           soil.x(), -soil.y(),  soil.z(), 
                           soil.x(),  soil.y(), -soil.z(),
                           soil.x(),  soil.y(),  soil.z()}; 

        GLuint VBO_coords;
        g.glGenBuffers(1, &VBO_coords);
        g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
        g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
        g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        g.glEnableVertexAttribArray(0);
        g.glBindVertexArray(0);
    }

    // 2. Draw
    g.glBindVertexArray (VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);
}



bool Reflection2::paintGL()
{
    GLWidget & g = *glwidget();
    g.glClearColor(0,0,0,0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    // Pass 1. Draw scene respect the mirror plane, an inverted version of the model
    
    program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());  
    QVector3D mirrorPosition = QVector3D(scene()->boundingBox().min().x(), 
                                         scene()->boundingBox().min().y(),
                                         scene()->boundingBox().min().z());
    program->setUniformValue("plane", mirrorPosition);
    program->setUniformValue("whereMirrorIs", QVector3D(0, 1.0, 0.0));
    if (drawPlugin()) drawPlugin()->drawScene();
    
    program->setUniformValue("whereMirrorIs", QVector3D(1.0, 0.0, 0.0));
    if (drawPlugin()) drawPlugin()->drawScene();
    
    program->setUniformValue("whereMirrorIs", QVector3D(0.0, 0.0, 1.0));
    if (drawPlugin()) drawPlugin()->drawScene();
    
    
    // save the image in a texture and delete the framebuffer
    g.glBindTexture(GL_TEXTURE_2D, textureOfReflection2);
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, IMAGE_WIDTH, IMAGE_HEIGHT);
    g.glGenerateMipmap(GL_TEXTURE_2D);
    g.glBindTexture(GL_TEXTURE_2D, 0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    
    
    // Step 2: draw the scene in the real position
    
    g.defaultProgram()->bind();
    if (drawPlugin()) drawPlugin()->drawScene();
    
    // Step 3: draw the mirror quad with the saved texture
    
    g.glActiveTexture(GL_TEXTURE0);
    g.glBindTexture(GL_TEXTURE_2D, textureOfReflection2); 
    programMirror->bind();
    programMirror->setUniformValue("mirror0", 0);
    programMirror->setUniformValue("SIZE", (float(IMAGE_WIDTH))); 
    programMirror->setUniformValue("modelViewProjectionMatrix", MVP);
    drawRect(g);
    drawRect2(g);
    drawRect3(g);

    g.defaultProgram()->bind();
    g.glBindTexture(GL_TEXTURE_2D, 0);
    return true;
}

