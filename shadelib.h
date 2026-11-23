#ifndef SHADELIB_H
#define SHADELIB_H

#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef _WIN32
#  define GLAPI_CALL __stdcall
#else
#  define GLAPI_CALL
#endif

//--++==defines==++--

typedef GLuint (GLAPI_CALL *PFN_glCreateShader)(GLenum);
typedef void   (GLAPI_CALL *PFN_glShaderSource)(GLuint, GLsizei, const GLchar *const *, const GLint *);
typedef void   (GLAPI_CALL *PFN_glCompileShader)(GLuint);
typedef void   (GLAPI_CALL *PFN_glGetShaderiv)(GLuint, GLenum, GLint *);
typedef void   (GLAPI_CALL *PFN_glGetShaderInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
typedef void   (GLAPI_CALL *PFN_glDeleteShader)(GLuint);

typedef GLuint (GLAPI_CALL *PFN_glCreateProgram)(void);
typedef void   (GLAPI_CALL *PFN_glAttachShader)(GLuint, GLuint);
typedef void   (GLAPI_CALL *PFN_glDetachShader)(GLuint, GLuint);
typedef void   (GLAPI_CALL *PFN_glBindAttribLocation)(GLuint, GLuint, const GLchar *);
typedef void   (GLAPI_CALL *PFN_glLinkProgram)(GLuint);
typedef void   (GLAPI_CALL *PFN_glGetProgramiv)(GLuint, GLenum, GLint *);
typedef void   (GLAPI_CALL *PFN_glGetProgramInfoLog)(GLuint, GLsizei, GLsizei *, GLchar *);
typedef void   (GLAPI_CALL *PFN_glUseProgram)(GLuint);
typedef void   (GLAPI_CALL *PFN_glDeleteProgram)(GLuint);

typedef GLint  (GLAPI_CALL *PFN_glGetUniformLocation)(GLuint, const GLchar *);
typedef void   (GLAPI_CALL *PFN_glUniform1i)(GLint, GLint);
typedef void   (GLAPI_CALL *PFN_glUniform1f)(GLint, GLfloat);
typedef void   (GLAPI_CALL *PFN_glUniform2f)(GLint, GLfloat, GLfloat);
typedef void   (GLAPI_CALL *PFN_glUniform3f)(GLint, GLfloat, GLfloat, GLfloat);
typedef void   (GLAPI_CALL *PFN_glUniform4f)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void   (GLAPI_CALL *PFN_glUniformMatrix4fv)(GLint, GLsizei, GLboolean, const GLfloat *);

typedef GLint  (GLAPI_CALL *PFN_glGetAttribLocation)(GLuint, const GLchar *);

static PFN_glCreateShader          x_glCreateShader          = NULL;
static PFN_glShaderSource          x_glShaderSource          = NULL;
static PFN_glCompileShader         x_glCompileShader         = NULL;
static PFN_glGetShaderiv           x_glGetShaderiv           = NULL;
static PFN_glGetShaderInfoLog      x_glGetShaderInfoLog      = NULL;
static PFN_glDeleteShader          x_glDeleteShader          = NULL;

static PFN_glCreateProgram         x_glCreateProgram         = NULL;
static PFN_glAttachShader          x_glAttachShader          = NULL;
static PFN_glDetachShader          x_glDetachShader          = NULL;
static PFN_glBindAttribLocation    x_glBindAttribLocation    = NULL;
static PFN_glLinkProgram           x_glLinkProgram           = NULL;
static PFN_glGetProgramiv          x_glGetProgramiv          = NULL;
static PFN_glGetProgramInfoLog     x_glGetProgramInfoLog     = NULL;
static PFN_glUseProgram            x_glUseProgram            = NULL;
static PFN_glDeleteProgram         x_glDeleteProgram         = NULL;

static PFN_glGetUniformLocation    x_glGetUniformLocation    = NULL;
static PFN_glUniform1i             x_glUniform1i             = NULL;
static PFN_glUniform1f             x_glUniform1f             = NULL;
static PFN_glUniform2f             x_glUniform2f             = NULL;
static PFN_glUniform3f             x_glUniform3f             = NULL;
static PFN_glUniform4f             x_glUniform4f             = NULL;
static PFN_glUniformMatrix4fv      x_glUniformMatrix4fv      = NULL;

static PFN_glGetAttribLocation     x_glGetAttribLocation     = NULL;

#define glCreateShader        x_glCreateShader
#define glShaderSource        x_glShaderSource
#define glCompileShader       x_glCompileShader
#define glGetShaderiv         x_glGetShaderiv
#define glGetShaderInfoLog    x_glGetShaderInfoLog
#define glDeleteShader        x_glDeleteShader

#define glCreateProgram       x_glCreateProgram
#define glAttachShader        x_glAttachShader
#define glDetachShader        x_glDetachShader
#define glBindAttribLocation  x_glBindAttribLocation
#define glLinkProgram         x_glLinkProgram
#define glGetProgramiv        x_glGetProgramiv
#define glGetProgramInfoLog   x_glGetProgramInfoLog
#define glUseProgram          x_glUseProgram
#define glDeleteProgram       x_glDeleteProgram

#define glGetUniformLocation  x_glGetUniformLocation
#define glUniform1i           x_glUniform1i
#define glUniform1f           x_glUniform1f
#define glUniform2f           x_glUniform2f
#define glUniform3f           x_glUniform3f
#define glUniform4f           x_glUniform4f
#define glUniformMatrix4fv    x_glUniformMatrix4fv

#define glGetAttribLocation   x_glGetAttribLocation

//--++==load==++--

static inline void *shadelib_get_proc(const char *name)
{
#ifdef _WIN32
    void *p = (void*)wglGetProcAddress(name);
    if (p == NULL || p == (void*)0x1 || p == (void*)0x2 ||
        p == (void*)0x3 || p == (void*)-1) {
        static HMODULE gl = NULL;
        if (!gl) gl = LoadLibraryA("opengl32.dll");
        p = gl ? (void*)GetProcAddress(gl, name) : NULL;
    }
    return p;
#else
    return (void*)glXGetProcAddressARB((const GLubyte*)name);
#endif
}

#define SHADELIB_LOAD(field, name) \
    do { \
        field = (void*)shadelib_get_proc(name); \
        if (!field) { \
            fprintf(stderr, "ShadeLib: missing %s\n", name); \
            return 0; \
        } \
    } while (0)

static inline int gl_load_shader_api(void)
{
    SHADELIB_LOAD(x_glCreateShader,          "glCreateShader");
    SHADELIB_LOAD(x_glShaderSource,          "glShaderSource");
    SHADELIB_LOAD(x_glCompileShader,         "glCompileShader");
    SHADELIB_LOAD(x_glGetShaderiv,           "glGetShaderiv");
    SHADELIB_LOAD(x_glGetShaderInfoLog,      "glGetShaderInfoLog");
    SHADELIB_LOAD(x_glDeleteShader,          "glDeleteShader");

    SHADELIB_LOAD(x_glCreateProgram,         "glCreateProgram");
    SHADELIB_LOAD(x_glAttachShader,          "glAttachShader");
    SHADELIB_LOAD(x_glDetachShader,          "glDetachShader");
    SHADELIB_LOAD(x_glBindAttribLocation,    "glBindAttribLocation");
    SHADELIB_LOAD(x_glLinkProgram,           "glLinkProgram");
    SHADELIB_LOAD(x_glGetProgramiv,          "glGetProgramiv");
    SHADELIB_LOAD(x_glGetProgramInfoLog,     "glGetProgramInfoLog");
    SHADELIB_LOAD(x_glUseProgram,            "glUseProgram");
    SHADELIB_LOAD(x_glDeleteProgram,         "glDeleteProgram");

    SHADELIB_LOAD(x_glGetUniformLocation,    "glGetUniformLocation");
    SHADELIB_LOAD(x_glUniform1i,             "glUniform1i");
    SHADELIB_LOAD(x_glUniform1f,             "glUniform1f");
    SHADELIB_LOAD(x_glUniform2f,             "glUniform2f");
    SHADELIB_LOAD(x_glUniform3f,             "glUniform3f");
    SHADELIB_LOAD(x_glUniform4f,             "glUniform4f");
    SHADELIB_LOAD(x_glUniformMatrix4fv,      "glUniformMatrix4fv");

    SHADELIB_LOAD(x_glGetAttribLocation,     "glGetAttribLocation");

    return 1;
}

//--++==functions==++--

//--++==Read/Close==++--

static inline char *ShadeLibReadStream(FILE *f, size_t *size)
{
    if (size) *size = 0;
    if (!f) {
        fprintf(stderr, "ShadeLibReadStream: NULL FILE*\n");
        return NULL;
    }

    size_t cap = 4096, len = 0;
    char *buf = malloc(cap + 1);
    if (!buf) {
        fprintf(stderr, "ShadeLibReadStream: malloc(%zu) failed\n", cap + 1);
        return NULL;
    }

    for (;;) {
        if (len == cap) {
            size_t ncap = cap * 2;
            if (ncap <= cap) {
                fprintf(stderr, "ShadeLibReadStream: size_t overflow (cap=%zu)\n", cap);
                free(buf);
                return NULL;
            }
            char *nb = realloc(buf, ncap + 1);
            if (!nb) {
                fprintf(stderr, "ShadeLibReadStream: realloc(%zu) failed\n", ncap + 1);
                free(buf);
                return NULL;
            }
            buf = nb;
            cap = ncap;
        }
        size_t n = fread(buf + len, 1, cap - len, f);
        len += n;
        if (n == 0) {
            if (ferror(f)) {
                fprintf(stderr, "ShadeLibReadStream: fread error after %zu bytes\n", len);
                free(buf);
                return NULL;
            }
            break;
        }
    }
    buf[len] = '\0';
    if (size) *size = len;
    return buf;
}

static inline char *ShadeLibReadFile(FILE *f, size_t *size)
{
    if (size) *size = 0;
    if (!f) {
        fprintf(stderr, "ShadeLibReadFile: NULL FILE*\n");
        return NULL;
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        fprintf(stderr, "ShadeLibReadFile: fseek(END) failed (not seekable?)\n");
        return NULL;
    }
    long sz = ftell(f);
    if (sz < 0) {
        fprintf(stderr, "ShadeLibReadFile: ftell failed\n");
        return NULL;
    }
    if (sz == 0) {
        fprintf(stderr, "ShadeLibReadFile: empty file\n");
        return NULL;
    }
    rewind(f);

    size_t len = (size_t)sz;
    char *buf = malloc(len + 1);
    if (!buf) {
        fprintf(stderr, "ShadeLibReadFile: malloc(%zu) failed\n", len + 1);
        return NULL;
    }
    size_t got = fread(buf, 1, len, f);
    if (got != len) {
        if (ferror(f)) {
            fprintf(stderr, "ShadeLibReadFile: fread error: %s\n", strerror(errno));
            free(buf);
            return NULL;
        }
        fprintf(stderr, "ShadeLibReadFile: short read (%zu of %zu)\n", got, len);
    }
    buf[got] = '\0';
    if (size) *size = got;
    return buf;
}

static inline FILE *ShadeLibOpenFile(const char *filename)
{
    if (!filename) {
        fprintf(stderr, "ShadeLibOpenFile: NULL filename\n");
        return NULL;
    }
    FILE *f = fopen(filename, "rb");
    if (!f) {
        fprintf(stderr, "ShadeLibOpenFile: cant open '%s': %s\n",
                filename, strerror(errno));
        return NULL;
    }
    return f;
}

static inline int ShadeLibCloseFile(FILE *f)
{
    return f ? fclose(f) : EOF;
}

static inline char *ShadeLibReadShader(const char *path, size_t *size)
{
    if (size) *size = 0;
    FILE *f = ShadeLibOpenFile(path);
    if (!f) return NULL;
    char *buf = ShadeLibReadFile(f, size);
    ShadeLibCloseFile(f);
    return buf;
}

//--++==Compile and Link==++--

static inline GLuint ShadeLibCompileShader(GLenum type, const char *src,
                                           size_t len, const char *name)
{
    if (!src || len == 0) {
        fprintf(stderr, "ShadeLibCompileShader: empty source '%s'\n",
                name ? name : "(null)");
        return 0;
    }

    GLuint shader = glCreateShader(type);
    if (!shader) {
        fprintf(stderr, "ShadeLibCompileShader: glCreateShader failed '%s'\n",
                name ? name : "(null)");
        return 0;
    }

    const GLchar *src_ptr = (const GLchar *)src;
    GLint gl_len = (GLint)len;
    glShaderSource(shader, 1, &src_ptr, &gl_len);
    glCompileShader(shader);

    GLint ok = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        GLint log_len = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 1) {
            char *log = malloc((size_t)log_len);
            if (log) {
                glGetShaderInfoLog(shader, log_len, NULL, log);
                log[log_len - 1] = '\0';
                fprintf(stderr, "ShadeLibCompileShader: error in '%s':\n%s\n",
                        name ? name : "(source)", log);
                free(log);
            } else {
                fprintf(stderr, "ShadeLibCompileShader: error in '%s' (log alloc failed)\n",
                        name ? name : "(source)");
            }
        } else {
            fprintf(stderr, "ShadeLibCompileShader: error in '%s' (no info log)\n",
                    name ? name : "(source)");
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

static inline GLuint ShadeLibCompileShaderFile(GLenum type, const char *path)
{
    if (!path) {
        fprintf(stderr, "ShadeLibCompileShaderFile: NULL path\n");
        return 0;
    }
    size_t len = 0;
    char *src = ShadeLibReadShader(path, &len);
    if (!src) return 0;
    GLuint shader = ShadeLibCompileShader(type, src, len, path);
    free(src);
    return shader;
}

static inline GLuint ShadeLibLinkProgram(const GLuint *shaders, int count,
                                         const char *const *attrs, const char *name)
{
    if (!shaders || count <= 0) {
        fprintf(stderr, "ShadeLibLinkProgram: invalid args '%s'\n",
                name ? name : "(null)");
        return 0;
    }

    GLuint prog = glCreateProgram();
    if (!prog) {
        fprintf(stderr, "ShadeLibLinkProgram: glCreateProgram failed '%s'\n",
                name ? name : "(null)");
        return 0;
    }

    for (int i = 0; i < count; ++i) {
        if (shaders[i]) glAttachShader(prog, shaders[i]);
    }

    if (attrs) {
        for (GLuint i = 0; attrs[i]; ++i)
            glBindAttribLocation(prog, i, attrs[i]);
    }

    glLinkProgram(prog);

    GLint ok = 0;
    glGetProgramiv(prog, GL_LINK_STATUS, &ok);
    if (!ok) {
        GLint log_len = 0;
        glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &log_len);
        if (log_len > 1) {
            char *log = malloc((size_t)log_len);
            if (log) {
                glGetProgramInfoLog(prog, log_len, NULL, log);
                log[log_len - 1] = '\0';
                fprintf(stderr, "ShadeLibLinkProgram: error in '%s':\n%s\n",
                        name ? name : "(program)", log);
                free(log);
            } else {
                fprintf(stderr, "ShadeLibLinkProgram: error in '%s' (log alloc failed)\n",
                        name ? name : "(program)");
            }
        } else {
            fprintf(stderr, "ShadeLibLinkProgram: error in '%s' (no info log)\n",
                    name ? name : "(program)");
        }
        glDeleteProgram(prog);
        return 0;
    }

    for (int i = 0; i < count; ++i) {
        if (shaders[i]) glDetachShader(prog, shaders[i]);
    }
    return prog;
}

//--++==utils==++--

static inline GLuint ShadeLibBuildProgram(const char *vert_path, const char *frag_path,
                                          const char *const *attrs, const char *name)
{
    GLuint vs = ShadeLibCompileShaderFile(GL_VERTEX_SHADER, vert_path);
    if (!vs) return 0;

    GLuint fs = ShadeLibCompileShaderFile(GL_FRAGMENT_SHADER, frag_path);
    if (!fs) {
        glDeleteShader(vs);
        return 0;
    }

    GLuint shaders[2] = { vs, fs };
    GLuint prog = ShadeLibLinkProgram(shaders, 2, attrs, name);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

static inline void ShadeLibFreeShader(GLuint *shader)
{
    if (shader && *shader) {
        glDeleteShader(*shader);
        *shader = 0;
    }
}

static inline void ShadeLibFreeProgram(GLuint *program)
{
    if (program && *program) {
        glDeleteProgram(*program);
        *program = 0;
    }
}

static inline void ShaderLibUse(GLuint program)
{
    glUseProgram(program);
}

static inline void ShaderLibDel(GLuint program)
{
    glDeleteProgram(program);
}

static inline void ShaderLibSetInteger(GLuint program, const char *name, int value)
{
    GLint loc = glGetUniformLocation(program, name);
    if (loc >= 0) glUniform1i(loc, value);
    else fprintf(stderr, "ShaderLibSetInteger: '%s' not found\n",
                 name ? name : "(null)");
}

static inline void ShaderLibSetFloat(GLuint program, const char *name, float value)
{
    GLint loc = glGetUniformLocation(program, name);
    if (loc >= 0) glUniform1f(loc, value);
    else fprintf(stderr, "ShaderLibSetFloat: '%s' not found\n",
                 name ? name : "(null)");
}

#endif
