#include "program_p2_c4.h"

PROGRAM_P2_C4::PROGRAM_P2_C4()
{
    _position   =   -1;
    _normal     =   -1;
    _color      =   -1;
    _MVP        =   -1;
    _lightDir   =   -1;

}

bool PROGRAM_P2_C4::initialize()
{
    //!1\使用（varying），是表示需要在（vs）和（ps）之间进行传递的变量，
    //!  把需要传递的变量在（vs）中赋值，并在（ps）中重复使用（varying）语句即可
    //!2\知识点，光线和法线的点积产生的值与光线的颜色相乘就是打在屏幕上的亮度，
    //! 一般选择光线的颜色是白色的，而光源由eye发出
    //! 颜色是顶点shader的特征，在顶点shader中定义并传递(顶点shader三大特征：顶点坐标，uv和颜色)
    const char* vs  =
    {
        "uniform    mat4    _MVP;"
        "uniform    vec3    _lightDir;"
        "attribute  vec3    _position;"
        "attribute  vec3    _normal;"
        "varying    vec4    _outColor;"
        "void main()"
        "{"
        "   float NDotL =   max(dot(_normal, _lightDir), 0.3);"
        "   _outColor   =   vec4(NDotL,NDotL,NDotL,1.0);"
        "   gl_Position =   _MVP * vec4(_position,1.0);"
        "}"
    };
    const char* ps  =
    {
        "precision  lowp    float; "
        "uniform    vec4    _color;"
        "varying    vec4    _outColor;"
        "void main()"
        "{"
        "   gl_FragColor    =   _outColor * _color ;"
        "}"
    };
    bool    res =   createProgram(vs,ps);
    if(res)
    {
        _position   =   glGetAttribLocation(_programId,"_position");
        _normal     =   glGetAttribLocation(_programId,"_normal");
        _color      =   glGetUniformLocation(_programId,"_color");
        _MVP        =   glGetUniformLocation(_programId,"_MVP");
        _lightDir   =   glGetUniformLocation(_programId,"_lightDir");
    }
    return  res;
}

void PROGRAM_P2_C4::begin()
{
    glUseProgram(_programId);
    //!在显卡里面使用的局部变量，在使用时是需要进行使能和关闭的
    glEnableVertexAttribArray(_position);       
    glEnableVertexAttribArray(_normal);
}

void PROGRAM_P2_C4::end()
{
    glDisableVertexAttribArray(_position);
    glDisableVertexAttribArray(_normal);
    glUseProgram(0);
}
