## New Shader System

```cpp
//BASE
//"virtual" 
class Shader {

protected:
    enum class ShaderType {
        NONE        = -1,
        VERTEX      =  0,
        FRAGMENT    =  1,
        GEOMETRY    =  2,
        TESSELATION =  3,
        COMPUTE     =  4
    };

    ShaderType type;
    std::string source;
    unsigned int shaderID;

    Shader();
    virtual ~Shader();

};

//DERIVED
class VertexShader : public Shader {
    VertexShader();
    ~VertexShader();

    CompileShader();
}

```