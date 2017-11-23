#ifndef QFRAMEBUFFEROBJECT_H
#define QFRAMEBUFFEROBJECT_H
#include <GLES2/gl2.h>

class QFrameBufferObject
{
public:
    QFrameBufferObject();

    unsigned int    _fbo;
    unsigned int    _texDepth;
    unsigned int    _wFbo;
    unsigned int    _hFbo;
    bool setOnlyDepthFBO(int width,int height);
    void begin();
    void end();
    void destroy();
};

#endif // QFRAMEBUFFEROBJECT_H
