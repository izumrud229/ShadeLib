#  **ShadeLib**

OpenGL shader API designed for convenience on C99

##  What inside?

- **Loader** `glCreateShader`, `glCompileShader`, `glLinkProgram`, `glUniform*` and so on through wglGetProcAddress / glXGetProcAddressARB
- **File Reader** `ShadeLibReadStream`(any thread, socket or FILE*),  `ShadeLibReadFile`(seekable), `ShadeLibReadShader`(open + read + close)
- **Compile** `ShadeLibCompileShader`, `ShadeLibCompileShaderFile` with full info log
- **Link** `ShadeLibLinkProgram`(N shaders, attrib bind), `ShadeLibBuildProgram`(vert + frag -> program)
- **utilities** `ShadeLibFreeShader` and `ShadeLibFreeProgram`(reset to zero ID), `ShaderLibSetInteger` and `ShaderLibSetFloat`(with an inspection location


##  Requirements

*C99 or newer*  
*An OpenGL context (created by you using GLFW, SDL, Win32, X11, or any other method).*  
*Link with systemic OpenGL:*  
*Windows: opengl32.lib*  
*Linux: -lGL*  

##  Install

just install ShadeLib.h and put it into any folder  
and include like
`#include "shadelib.h"`

##  API at a glance


| function | description |
|---|---|
| `gl_load_shader_api()` | Load Address GL-functions, call once after the context has been created |
| `ShadeLibBuildProgram(v, f, attrs, name)` | vert + frag + attrs -> program |
| `ShadeLibCompileShaderFile(type, path)` | compile shader from file |
| `ShadeLibCompileShader(type, src, len, name)` | Compile from memory (with explicit length) |
| `ShadeLibLinkProgram(shaders, count, attrs, name)` | Link N shaders |
| `ShadeLibFreeProgram(&prog)` | Remove the program, reset the ID |
| `ShadeLibFreeShader(&sh)` | Remove the shader, reset the ID |

## Utilities

| function | description |
|---|---|
| `ShaderLibUse(prog)` | glUseProgram |
| `ShaderLibSetInteger(prog, name, v)` | glUniform1i with an inspection location |
| `ShaderLibSetFloat(prog, name, v)` | glUniform1f with an inspection location |
| `ShadeLibReadShader(path, &len)` | open + read + close, return malloc buffer with `'\0'` |

##  Warnings

***Do not include <GL/glext.h>***  
***Call *gl_load_shader_api()* after creating the context***  
***Header-only and static***  
***This is a header-only library, but due to the use of static pointers, you should either include it in only one `.c` file or call `gl_load_shader_api()` in every module***  


##  Step-by-step version
If you need access to every step, do not use ShadeLibBuildProgram  
handle it manually instead.


```c
GLuint vs = ShadeLibCompileShaderFile(GL_VERTEX_SHADER,   "basic.vert");
if (!vs) return 1;

GLuint fs = ShadeLibCompileShaderFile(GL_FRAGMENT_SHADER, "basic.frag");
if (!fs) { ShadeLibFreeShader(&vs); return 1; }

GLuint shaders[2] = { vs, fs };
static const char *const attrs[] = { "aPos", "aUV", NULL };
GLuint prog = ShadeLibLinkProgram(shaders, 2, attrs, "basic");

ShadeLibFreeShader(&vs);
ShadeLibFreeShader(&fs);

if (!prog) return 1;


