#include "qframebufferobject.h"

QFrameBufferObject::QFrameBufferObject()
{

}

bool QFrameBufferObject::setOnlyDepthFBO(int width, int height)
{
    _wFbo = width;  _hFbo = height;
    glGenBuffers(1,&_fbo);
    glEnable(GL_FRAMEBUFFER);
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);

    glActiveTexture(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_2D);
    glGenTextures(1,&_texDepth);
    glBindTexture(GL_TEXTURE_2D,_texDepth);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT16,_wFbo,_hFbo,0,GL_DEPTH_COMPONENT16,GL_UNSIGNED_BYTE,0);
    glBindTexture(GL_TEXTURE_2D,0);

    glBindFramebuffer(GL_FRAMEBUFFER,0);
    return true;
}

void QFrameBufferObject::begin()
{
    glBindFramebuffer(GL_FRAMEBUFFER,_fbo);
//    glDrawBuffers(0, NULL);
//    glReadBuffer(GL_NONE);

    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_ATTACHMENT,GL_TEXTURE_2D,_texDepth,0);
    glClear(GL_DEPTH_BUFFER_BIT);
}

void QFrameBufferObject::end()
{
    glBindFramebuffer(GL_FRAMEBUFFER,0);
}

void QFrameBufferObject::destroy()
{
    glDeleteFramebuffers(1, &_fbo);
    glDeleteTextures(1,&_texDepth);
    _texDepth  =   0;
    _fbo  =   0;
}

