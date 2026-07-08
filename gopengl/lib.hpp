namespace gopengl {
    using namespace gnumeric::types;
    using gsp::gsp;
    using ggeometry::Transform2D;
    using gdecoded_rgba_texture::DecodedRGBATexture;

    #define NO_COPY(ClassName) \
        ClassName(const ClassName&) = delete; \
        ClassName& operator=(const ClassName&) = delete;
    
    #define NO_MOVE(ClassName) \
        ClassName(ClassName&&) = delete; \
        ClassName& operator=(ClassName&&) = delete;

    namespace GL {
        using GLboolean = unsigned char;
        using GLbitfield = unsigned int;
        using GLbyte = signed char;
        using GLubyte = unsigned char;
        using GLshort = short;
        using GLushort = unsigned short;
        using GLint = int;
        using GLuint = unsigned int;
        using GLsizei = int;
        using GLfloat = float;
        using GLclampf = float;
        using GLdouble = double;
        using GLvoid = void;
        using GLenum = unsigned int;
        using GLsizeiptr = long long;
        using GLintptr = long long;
        using GLuint64 = uint64_t;
        using GLchar = signed char;
        using GLsync = struct __GLsync*;

        constexpr GLenum GL_NO_ERROR = 0;
        constexpr GLenum GL_INVALID_ENUM = 0x0500;
        constexpr GLenum GL_INVALID_VALUE = 0x0501;
        constexpr GLenum GL_INVALID_OPERATION = 0x0502;
        constexpr GLenum GL_OUT_OF_MEMORY = 0x0505;
        constexpr GLenum GL_VENDOR = 0x1F00;
        constexpr GLenum GL_RENDERER = 0x1F01;
        constexpr GLenum GL_VERSION = 0x1F02;
        constexpr GLenum GL_EXTENSIONS = 0x1F03;
        constexpr GLenum GL_MAJOR_VERSION = 0x821B;
        constexpr GLenum GL_MINOR_VERSION = 0x821C;
        constexpr GLenum GL_MAX_TEXTURE_SIZE = 0x0D33;
        constexpr GLenum GL_MAX_VERTEX_ATTRIBS = 0x8869;
        constexpr GLenum GL_MAX_TEXTURE_IMAGE_UNITS = 0x8872;
        constexpr GLenum GL_MAX_DRAW_BUFFERS = 0x8824;
        constexpr GLenum GL_MAX_UNIFORM_BLOCK_SIZE = 0x8A30;
        constexpr GLenum GL_MAX_VERTEX_UNIFORM_BLOCKS = 0x8A2B;
        constexpr GLenum GL_MAX_FRAGMENT_UNIFORM_BLOCKS = 0x8A2D;
        constexpr GLenum GL_VIEWPORT = 0x0BA2;
        constexpr GLenum GL_SCISSOR_BOX = 0x0C10;
        constexpr GLenum GL_SCISSOR_TEST = 0x0C11;
        constexpr GLenum GL_BLEND = 0x0BE2;
        constexpr GLenum GL_DEPTH_TEST = 0x0B71;
        constexpr GLenum GL_STENCIL_TEST = 0x0B90;
        constexpr GLenum GL_CULL_FACE = 0x0B44;
        constexpr GLenum GL_DITHER = 0x0BD0;
        constexpr GLenum GL_COLOR_CLEAR_VALUE = 0x0C22;
        constexpr GLenum GL_UNPACK_ALIGNMENT = 0x0CF5;
        constexpr GLenum GL_PACK_ALIGNMENT = 0x0D05;
        constexpr GLenum GL_FRAMEBUFFER_BINDING = 0x8CA6;
        constexpr GLenum GL_READ_FRAMEBUFFER_BINDING = 0x8CAA;
        constexpr GLenum GL_DRAW_FRAMEBUFFER_BINDING = 0x8CA6;
        constexpr GLenum GL_ARRAY_BUFFER_BINDING = 0x8894;
        constexpr GLenum GL_RENDERBUFFER_BINDING = 0x8CA7;
        constexpr GLenum GL_VERTEX_ARRAY_BINDING = 0x85B5;
        constexpr GLenum GL_CURRENT_PROGRAM = 0x8B8D;
        constexpr GLenum GL_TEXTURE_BINDING_2D = 0x8069;
        constexpr GLenum GL_COLOR_WRITEMASK = 0x0C23;
        constexpr GLenum GL_DEPTH_WRITEMASK = 0x0B72;
        constexpr GLenum GL_SAMPLES = 0x80A9;

        constexpr GLenum GL_ARRAY_BUFFER = 0x8892;
        constexpr GLenum GL_ELEMENT_ARRAY_BUFFER = 0x8893;
        constexpr GLenum GL_UNIFORM_BUFFER = 0x8A11;
        constexpr GLenum GL_PIXEL_PACK_BUFFER = 0x88EB;
        constexpr GLenum GL_PIXEL_UNPACK_BUFFER = 0x88EC;

        constexpr GLenum GL_STREAM_DRAW = 0x88E0;
        constexpr GLenum GL_STREAM_READ = 0x88E1;
        constexpr GLenum GL_STREAM_COPY = 0x88E2;
        constexpr GLenum GL_STATIC_DRAW = 0x88E4;
        constexpr GLenum GL_STATIC_READ = 0x88E5;
        constexpr GLenum GL_STATIC_COPY = 0x88E6;
        constexpr GLenum GL_DYNAMIC_DRAW = 0x88E8;
        constexpr GLenum GL_DYNAMIC_READ = 0x88E9;
        constexpr GLenum GL_DYNAMIC_COPY = 0x88EA;

        constexpr GLenum GL_READ_ONLY = 0x88B8;
        constexpr GLenum GL_WRITE_ONLY = 0x88B9;
        constexpr GLenum GL_READ_WRITE = 0x88BA;

        constexpr GLbitfield GL_MAP_READ_BIT = 0x0001;
        constexpr GLbitfield GL_MAP_WRITE_BIT = 0x0002;
        constexpr GLbitfield GL_MAP_INVALIDATE_RANGE_BIT = 0x0004;
        constexpr GLbitfield GL_MAP_INVALIDATE_BUFFER_BIT = 0x0008;
        constexpr GLbitfield GL_MAP_FLUSH_EXPLICIT_BIT = 0x0010;
        constexpr GLbitfield GL_MAP_UNSYNCHRONIZED_BIT = 0x0020;

        constexpr GLenum GL_BYTE = 0x1400;
        constexpr GLenum GL_SHORT = 0x1402;
        constexpr GLenum GL_INT = 0x1404;
        constexpr GLenum GL_HALF_FLOAT = 0x140B;
        constexpr GLenum GL_FIXED = 0x140C;

        constexpr GLenum GL_VERTEX_SHADER = 0x8B31;
        constexpr GLenum GL_FRAGMENT_SHADER = 0x8B30;

        constexpr GLenum GL_COMPILE_STATUS = 0x8B81;
        constexpr GLenum GL_LINK_STATUS = 0x8B82;
        constexpr GLenum GL_INFO_LOG_LENGTH = 0x8B84;
        constexpr GLenum GL_DELETE_STATUS = 0x8B80;
        constexpr GLenum GL_SHADER_TYPE = 0x8B4F;

        constexpr GLenum GL_ACTIVE_ATTRIBUTES = 0x8B89;
        constexpr GLenum GL_ACTIVE_UNIFORMS = 0x8B86;
        constexpr GLenum GL_ACTIVE_ATTRIBUTE_MAX_LENGTH = 0x8B8A;
        constexpr GLenum GL_ACTIVE_UNIFORM_MAX_LENGTH = 0x8B87;

        constexpr GLenum GL_TEXTURE_2D = 0x0DE1;
        constexpr GLenum GL_TEXTURE_CUBE_MAP = 0x8513;
        constexpr GLenum GL_TEXTURE_CUBE_MAP_POSITIVE_X = 0x8515;
        constexpr GLenum GL_TEXTURE_CUBE_MAP_NEGATIVE_X = 0x8516;
        constexpr GLenum GL_TEXTURE_CUBE_MAP_POSITIVE_Y = 0x8517;
        constexpr GLenum GL_TEXTURE_CUBE_MAP_NEGATIVE_Y = 0x8518;
        constexpr GLenum GL_TEXTURE_CUBE_MAP_POSITIVE_Z = 0x8519;
        constexpr GLenum GL_TEXTURE_CUBE_MAP_NEGATIVE_Z = 0x851A;
        constexpr GLenum GL_TEXTURE_2D_MULTISAMPLE = 0x9100;

        constexpr GLenum GL_TEXTURE_MIN_FILTER = 0x2801;
        constexpr GLenum GL_TEXTURE_MAG_FILTER = 0x2800;
        constexpr GLenum GL_TEXTURE_WRAP_S = 0x2802;
        constexpr GLenum GL_TEXTURE_WRAP_T = 0x2803;
        constexpr GLenum GL_NEAREST = 0x2600;
        constexpr GLenum GL_LINEAR = 0x2601;
        constexpr GLenum GL_NEAREST_MIPMAP_NEAREST = 0x2700;
        constexpr GLenum GL_LINEAR_MIPMAP_NEAREST = 0x2701;
        constexpr GLenum GL_NEAREST_MIPMAP_LINEAR = 0x2702;
        constexpr GLenum GL_LINEAR_MIPMAP_LINEAR = 0x2703;
        constexpr GLenum GL_CLAMP_TO_EDGE = 0x812F;
        constexpr GLenum GL_REPEAT = 0x2901;
        constexpr GLenum GL_MIRRORED_REPEAT = 0x8370;

        constexpr GLenum GL_TEXTURE0 = 0x84C0;

        constexpr GLenum GL_RED = 0x1903;
        constexpr GLenum GL_RG = 0x8227;
        constexpr GLenum GL_RGB = 0x1907;
        constexpr GLenum GL_RGBA = 0x1908;
        constexpr GLenum GL_BGR = 0x80E0;
        constexpr GLenum GL_BGRA = 0x80E1;
        constexpr GLenum GL_R8 = 0x8229;
        constexpr GLenum GL_RG8 = 0x822B;
        constexpr GLenum GL_RGB8 = 0x8051;
        constexpr GLenum GL_RGBA8 = 0x8058;
        constexpr GLenum GL_R16F = 0x822D;
        constexpr GLenum GL_RG16F = 0x822F;
        constexpr GLenum GL_RGB16F = 0x881B;
        constexpr GLenum GL_RGBA16F = 0x881A;
        constexpr GLenum GL_R32F = 0x822E;
        constexpr GLenum GL_RG32F = 0x8230;
        constexpr GLenum GL_RGB32F = 0x8815;
        constexpr GLenum GL_RGBA32F = 0x8814;
        constexpr GLenum GL_RGB10_A2 = 0x8059;
        constexpr GLenum GL_DEPTH_COMPONENT = 0x1902;
        constexpr GLenum GL_DEPTH_COMPONENT16 = 0x81A5;
        constexpr GLenum GL_DEPTH_COMPONENT24 = 0x81A6;
        constexpr GLenum GL_DEPTH_COMPONENT32F = 0x8CAC;
        constexpr GLenum GL_DEPTH24_STENCIL8 = 0x88F0;
        constexpr GLenum GL_FLOAT = 0x1406;
        constexpr GLenum GL_UNSIGNED_INT_24_8 = 0x84FA;

        constexpr GLenum GL_FRAMEBUFFER = 0x8D40;
        constexpr GLenum GL_READ_FRAMEBUFFER = 0x8CA8;
        constexpr GLenum GL_DRAW_FRAMEBUFFER = 0x8CA9;
        constexpr GLenum GL_FRAMEBUFFER_COMPLETE = 0x8CD5;
        constexpr GLenum GL_COLOR_ATTACHMENT0 = 0x8CE0;
        constexpr GLenum GL_COLOR_ATTACHMENT1 = 0x8CE1;
        constexpr GLenum GL_COLOR_ATTACHMENT2 = 0x8CE2;
        constexpr GLenum GL_COLOR_ATTACHMENT3 = 0x8CE3;
        constexpr GLenum GL_DEPTH_ATTACHMENT = 0x8D00;
        constexpr GLenum GL_STENCIL_ATTACHMENT = 0x8D20;
        constexpr GLenum GL_DEPTH_STENCIL_ATTACHMENT = 0x821A;

        constexpr GLenum GL_RENDERBUFFER = 0x8D41;

        constexpr GLenum GL_POINTS = 0x0000;
        constexpr GLenum GL_LINES = 0x0001;
        constexpr GLenum GL_LINE_LOOP = 0x0002;
        constexpr GLenum GL_LINE_STRIP = 0x0003;
        constexpr GLenum GL_TRIANGLES = 0x0004;
        constexpr GLenum GL_TRIANGLE_STRIP = 0x0005;
        constexpr GLenum GL_TRIANGLE_FAN = 0x0006;

        constexpr GLenum GL_UNSIGNED_BYTE = 0x1401;
        constexpr GLenum GL_UNSIGNED_SHORT = 0x1403;
        constexpr GLenum GL_UNSIGNED_INT = 0x1405;

        constexpr GLenum GL_COLOR_BUFFER_BIT = 0x00004000;
        constexpr GLenum GL_DEPTH_BUFFER_BIT = 0x00000100;
        constexpr GLenum GL_STENCIL_BUFFER_BIT = 0x00000400;

        constexpr GLenum GL_ZERO = 0;
        constexpr GLenum GL_ONE = 1;
        constexpr GLenum GL_SRC_COLOR = 0x0300;
        constexpr GLenum GL_ONE_MINUS_SRC_COLOR = 0x0301;
        constexpr GLenum GL_SRC_ALPHA = 0x0302;
        constexpr GLenum GL_ONE_MINUS_SRC_ALPHA = 0x0303;
        constexpr GLenum GL_DST_ALPHA = 0x0304;
        constexpr GLenum GL_ONE_MINUS_DST_ALPHA = 0x0305;
        constexpr GLenum GL_DST_COLOR = 0x0306;
        constexpr GLenum GL_ONE_MINUS_DST_COLOR = 0x0307;

        constexpr GLenum GL_FUNC_ADD = 0x8006;
        constexpr GLenum GL_FUNC_SUBTRACT = 0x800A;
        constexpr GLenum GL_FUNC_REVERSE_SUBTRACT = 0x800B;
        constexpr GLenum GL_MIN = 0x8007;
        constexpr GLenum GL_MAX = 0x8008;

        constexpr GLenum GL_NEVER = 0x0200;
        constexpr GLenum GL_LESS = 0x0201;
        constexpr GLenum GL_EQUAL = 0x0202;
        constexpr GLenum GL_LEQUAL = 0x0203;
        constexpr GLenum GL_GREATER = 0x0204;
        constexpr GLenum GL_NOTEQUAL = 0x0205;
        constexpr GLenum GL_GEQUAL = 0x0206;
        constexpr GLenum GL_ALWAYS = 0x0207;

        constexpr GLenum GL_KEEP = 0x1E00;
        constexpr GLenum GL_REPLACE = 0x1E01;
        constexpr GLenum GL_INCR = 0x1E02;
        constexpr GLenum GL_DECR = 0x1E03;
        constexpr GLenum GL_INVERT = 0x150A;
        constexpr GLenum GL_INCR_WRAP = 0x8507;
        constexpr GLenum GL_DECR_WRAP = 0x8508;

        constexpr GLenum GL_TIME_ELAPSED = 0x88BF;
        constexpr GLenum GL_QUERY_RESULT = 0x8866;
        constexpr GLenum GL_QUERY_RESULT_AVAILABLE = 0x8867;

        constexpr GLenum GL_SYNC_GPU_COMMANDS_COMPLETE = 0x9117;
        constexpr GLenum GL_ALREADY_SIGNALED = 0x911A;
        constexpr GLenum GL_TIMEOUT_EXPIRED = 0x911B;
        constexpr GLenum GL_CONDITION_SATISFIED = 0x911C;
        constexpr GLenum GL_WAIT_FAILED = 0x911D;
        constexpr GLenum GL_SYNC_FLUSH_COMMANDS_BIT = 0x00000001;
        constexpr GLuint64 GL_TIMEOUT_IGNORED = 0xFFFFFFFFFFFFFFFFull;
        constexpr GLenum GL_SYNC_STATUS = 0x9114;
        constexpr GLenum GL_SIGNALED = 0x9119;

        constexpr GLint GL_TRUE = 1;
        constexpr GLint GL_FALSE = 0;

        constexpr GLenum GL_TEXTURE_MAX_ANISOTROPY_EXT = 0x84FE;
        constexpr GLenum GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT = 0x84FF;
        constexpr GLenum GL_TEXTURE_REDUCTION_MODE_EXT = 0x9366;
        constexpr GLenum GL_NUM_EXTENSIONS = 0x821D;

        struct GL33CoreInterface {
            GLenum (*glGetError)();
            void (*glGetIntegerv)(GLenum pname, GLint* data);
            void (*glGetFloatv)(GLenum pname, GLfloat* data);
            void (*glGetBooleanv)(GLenum pname, GLboolean* data);
            const GLubyte* (*glGetString)(GLenum name);
            const GLubyte* (*glGetStringi)(GLenum name, GLuint index);
            void (*glEnable)(GLenum cap);
            void (*glDisable)(GLenum cap);
            GLboolean (*glIsEnabled)(GLenum cap);
            void (*glViewport)(GLint x, GLint y, GLsizei width, GLsizei height);
            void (*glScissor)(GLint x, GLint y, GLsizei width, GLsizei height);
            void (*glClearColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
            void (*glClear)(GLbitfield mask);
            void (*glPixelStorei)(GLenum pname, GLint param);
            void (*glFlush)();
            void (*glFinish)();

            void (*glGenBuffers)(GLsizei n, GLuint* buffers);
            void (*glDeleteBuffers)(GLsizei n, const GLuint* buffers);
            void (*glBindBuffer)(GLenum target, GLuint buffer);
            void (*glBufferData)(GLenum target, GLsizeiptr size, const void* data, GLenum usage);
            void (*glBufferSubData)(GLenum target, GLintptr offset, GLsizeiptr size, const void* data);
            void* (*glMapBufferRange)(GLenum target, GLintptr offset, GLsizeiptr length, GLbitfield access);
            GLboolean (*glUnmapBuffer)(GLenum target);
            void (*glBindBufferRange)(GLenum target, GLuint index, GLuint buffer, GLintptr offset, GLsizeiptr size);
            void (*glBindBufferBase)(GLenum target, GLuint index, GLuint buffer);

            void (*glGenVertexArrays)(GLsizei n, GLuint* arrays);
            void (*glDeleteVertexArrays)(GLsizei n, const GLuint* arrays);
            void (*glBindVertexArray)(GLuint array);
            void (*glEnableVertexAttribArray)(GLuint index);
            void (*glDisableVertexAttribArray)(GLuint index);
            void (*glVertexAttribPointer)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);
            void (*glVertexAttribIPointer)(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer);
            void (*glVertexAttribDivisor)(GLuint index, GLuint divisor);

            GLuint (*glCreateShader)(GLenum type);
            void (*glShaderSource)(GLuint shader, GLsizei count, const GLchar* const* string, const GLint* length);
            void (*glCompileShader)(GLuint shader);
            void (*glGetShaderiv)(GLuint shader, GLenum pname, GLint* params);
            void (*glGetShaderInfoLog)(GLuint shader, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
            void (*glDeleteShader)(GLuint shader);
            GLuint (*glCreateProgram)();
            void (*glAttachShader)(GLuint program, GLuint shader);
            void (*glDetachShader)(GLuint program, GLuint shader);
            void (*glLinkProgram)(GLuint program);
            void (*glUseProgram)(GLuint program);
            void (*glGetProgramiv)(GLuint program, GLenum pname, GLint* params);
            void (*glGetProgramInfoLog)(GLuint program, GLsizei bufSize, GLsizei* length, GLchar* infoLog);
            void (*glDeleteProgram)(GLuint program);
            void (*glGetActiveAttrib)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
            void (*glGetActiveUniform)(GLuint program, GLuint index, GLsizei bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
            GLint (*glGetAttribLocation)(GLuint program, const GLchar* name);
            GLint (*glGetUniformLocation)(GLuint program, const GLchar* name);

            void (*glUniform1f)(GLint location, GLfloat v0);
            void (*glUniform2f)(GLint location, GLfloat v0, GLfloat v1);
            void (*glUniform3f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
            void (*glUniform4f)(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
            void (*glUniform1i)(GLint location, GLint v0);
            void (*glUniform2i)(GLint location, GLint v0, GLint v1);
            void (*glUniform3i)(GLint location, GLint v0, GLint v1, GLint v2);
            void (*glUniform4i)(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
            void (*glUniform1fv)(GLint location, GLsizei count, const GLfloat* value);
            void (*glUniform2fv)(GLint location, GLsizei count, const GLfloat* value);
            void (*glUniform3fv)(GLint location, GLsizei count, const GLfloat* value);
            void (*glUniform4fv)(GLint location, GLsizei count, const GLfloat* value);
            void (*glUniform1iv)(GLint location, GLsizei count, const GLint* value);
            void (*glUniform2iv)(GLint location, GLsizei count, const GLint* value);
            void (*glUniform3iv)(GLint location, GLsizei count, const GLint* value);
            void (*glUniform4iv)(GLint location, GLsizei count, const GLint* value);
            void (*glUniformMatrix2fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
            void (*glUniformMatrix3fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
            void (*glUniformMatrix4fv)(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);

            void (*glGenTextures)(GLsizei n, GLuint* textures);
            void (*glDeleteTextures)(GLsizei n, const GLuint* textures);
            void (*glBindTexture)(GLenum target, GLuint texture);
            void (*glTexImage2D)(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
            void (*glTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void* pixels);
            void (*glTexParameteri)(GLenum target, GLenum pname, GLint param);
            void (*glTexParameterf)(GLenum target, GLenum pname, GLfloat param);
            void (*glGenerateMipmap)(GLenum target);
            void (*glActiveTexture)(GLenum texture);
            void (*glTexStorage2D)(GLenum target, GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height);
            void (*glTexStorage2DMultisample)(GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLboolean fixedsamplelocations);

            void (*glGenFramebuffers)(GLsizei n, GLuint* framebuffers);
            void (*glDeleteFramebuffers)(GLsizei n, const GLuint* framebuffers);
            void (*glBindFramebuffer)(GLenum target, GLuint framebuffer);
            GLenum (*glCheckFramebufferStatus)(GLenum target);
            void (*glFramebufferTexture2D)(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
            void (*glBlitFramebuffer)(GLint srcX0, GLint srcY0, GLint srcX1, GLint srcY1, GLint dstX0, GLint dstY0, GLint dstX1, GLint dstY1, GLbitfield mask, GLenum filter);

            void (*glGenRenderbuffers)(GLsizei n, GLuint* renderbuffers);
            void (*glDeleteRenderbuffers)(GLsizei n, const GLuint* renderbuffers);
            void (*glBindRenderbuffer)(GLenum target, GLuint renderbuffer);
            void (*glRenderbufferStorage)(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
            void (*glFramebufferRenderbuffer)(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);

            void (*glDrawArrays)(GLenum mode, GLint first, GLsizei count);
            void (*glDrawElements)(GLenum mode, GLsizei count, GLenum type, const void* indices);
            void (*glDrawArraysInstanced)(GLenum mode, GLint first, GLsizei count, GLsizei instancecount);
            void (*glDrawElementsInstanced)(GLenum mode, GLsizei count, GLenum type, const void* indices, GLsizei instancecount);

            void (*glBlendFunc)(GLenum sfactor, GLenum dfactor);
            void (*glBlendFuncSeparate)(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
            void (*glBlendEquation)(GLenum mode);
            void (*glBlendEquationSeparate)(GLenum modeRGB, GLenum modeAlpha);
            void (*glBlendColor)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
            void (*glDepthFunc)(GLenum func);
            void (*glDepthMask)(GLboolean flag);
            void (*glStencilFunc)(GLenum func, GLint ref, GLuint mask);
            void (*glStencilOp)(GLenum sfail, GLenum dpfail, GLenum dppass);
            void (*glStencilMask)(GLuint mask);
            void (*glColorMask)(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);

            void (*glReadPixels)(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void* pixels);
            void (*glCopyTexSubImage2D)(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);

            GLsync (*glFenceSync)(GLenum condition, GLbitfield flags);
            void (*glDeleteSync)(GLsync sync);
            GLenum (*glClientWaitSync)(GLsync sync, GLbitfield flags, GLuint64 timeout);
            void (*glGetSynciv)(GLsync sync, GLenum pname, GLsizei bufSize, GLsizei* length, GLint* values);

            bool isGles = false;

            struct {
                GLuint vertexArrayBinding;
                GLuint currentProgram;
                GLuint renderbufferBinding;
                std::unordered_map<GLenum, GLuint> currentBuffers;
                std::unordered_map<GLenum, GLuint> currentTextures;
                std::unordered_map<GLenum, GLuint> currentFramebuffers;
            } localState;

            bool isExtensionSupported(const char* extension) const noexcept {
                GLint num;
                glGetIntegerv(GL_NUM_EXTENSIONS, &num);

                for (GLint i = 0; i < num; i++) {
                    auto* ext = (const char*)glGetStringi(GL_EXTENSIONS, i);
                    if (strcmp(ext, extension) == 0) {
                        return true;
                    }
                }

                return false;
            }

            GLuint glBindBufferProxy(GLenum target, GLuint buffer) {
                auto it = localState.currentBuffers.find(target);

                if (it == localState.currentBuffers.end()) {
                    glBindBuffer(target, buffer);
                    localState.currentBuffers.emplace(target, buffer);
                    return 0;
                } else if (it->second != buffer) {
                    glBindBuffer(target, buffer);
                    return std::exchange(it->second, buffer);
                } else return buffer;
            }

            GLuint glBindVertexArrayProxy(GLuint array) {
                if (localState.vertexArrayBinding != array) {
                    glBindVertexArray(array);
                    return std::exchange(localState.vertexArrayBinding, array);
                } else return array;
            }

            GLuint glBindTextureProxy(GLenum target, GLuint texture) {
                auto it = localState.currentTextures.find(target);

                if (it == localState.currentTextures.end()) {
                    glBindTexture(target, texture);
                    localState.currentTextures.emplace(target, texture);
                    return 0;
                } else if (it->second != texture) {
                    glBindTexture(target, texture);
                    return std::exchange(it->second, texture);
                } else return texture;
            }

            GLuint glBindFramebufferProxy(GLenum target, GLuint framebuffer) {
                auto it = localState.currentFramebuffers.find(target);

                if (it == localState.currentFramebuffers.end()) {
                    glBindFramebuffer(target, framebuffer);
                    localState.currentFramebuffers.emplace(target, framebuffer);
                    return 0;
                } else if (it->second != framebuffer) {
                    glBindFramebuffer(target, framebuffer);
                    return std::exchange(it->second, framebuffer);
                } else return framebuffer;
            }

            GLuint glBindRenderbufferProxy(GLuint renderbuffer) {
                if (localState.renderbufferBinding != renderbuffer) {
                    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
                    return std::exchange(localState.renderbufferBinding, renderbuffer);
                } else return renderbuffer;
            }

            GLuint glUseProgramProxy(GLuint program) {
                if (localState.currentProgram != program) {
                    glUseProgram(program);
                    return std::exchange(localState.currentProgram, program);
                } else return program;
            }
        };
        
        using GLProcLoader = std::function<void*(const char*)>;
        
        static GL33CoreInterface MakeGL33CoreInterface(GLProcLoader loader) {
            #ifdef interface // fuck microsoft
            #undef interface
            #endif

            GL33CoreInterface interface {};

            #define load(proc) { \
                auto ptr = loader(#proc); \
                if (!ptr) { \
                    throw std::runtime_error("failed to load " #proc); \
                } \
                using F = decltype(interface.proc); \
                interface.proc = (F)ptr; \
            }

            load(glGetError)
            load(glGetIntegerv)
            load(glGetFloatv)
            load(glGetBooleanv)
            load(glGetString)
            load(glGetStringi)
            load(glEnable)
            load(glDisable)
            load(glIsEnabled)
            load(glViewport)
            load(glScissor)
            load(glClearColor)
            load(glClear)
            load(glPixelStorei)
            load(glFlush)
            load(glFinish)

            load(glGenBuffers)
            load(glDeleteBuffers)
            load(glBindBuffer)
            load(glBufferData)
            load(glBufferSubData)
            load(glMapBufferRange)
            load(glUnmapBuffer)
            load(glBindBufferRange)
            load(glBindBufferBase)

            load(glGenVertexArrays)
            load(glDeleteVertexArrays)
            load(glBindVertexArray)
            load(glEnableVertexAttribArray)
            load(glDisableVertexAttribArray)
            load(glVertexAttribPointer)
            load(glVertexAttribIPointer)
            load(glVertexAttribDivisor)

            load(glCreateShader)
            load(glShaderSource)
            load(glCompileShader)
            load(glGetShaderiv)
            load(glGetShaderInfoLog)
            load(glDeleteShader)
            load(glCreateProgram)
            load(glAttachShader)
            load(glDetachShader)
            load(glLinkProgram)
            load(glUseProgram)
            load(glGetProgramiv)
            load(glGetProgramInfoLog)
            load(glDeleteProgram)
            load(glGetActiveAttrib)
            load(glGetActiveUniform)
            load(glGetAttribLocation)
            load(glGetUniformLocation)

            load(glUniform1f)
            load(glUniform2f)
            load(glUniform3f)
            load(glUniform4f)
            load(glUniform1i)
            load(glUniform2i)
            load(glUniform3i)
            load(glUniform4i)
            load(glUniform1fv)
            load(glUniform2fv)
            load(glUniform3fv)
            load(glUniform4fv)
            load(glUniform1iv)
            load(glUniform2iv)
            load(glUniform3iv)
            load(glUniform4iv)
            load(glUniformMatrix2fv)
            load(glUniformMatrix3fv)
            load(glUniformMatrix4fv)

            load(glGenTextures)
            load(glDeleteTextures)
            load(glBindTexture)
            load(glTexImage2D)
            load(glTexSubImage2D)
            load(glTexParameteri)
            load(glTexParameterf)
            load(glGenerateMipmap)
            load(glActiveTexture)
            load(glTexStorage2D)
            load(glTexStorage2DMultisample)

            load(glGenFramebuffers)
            load(glDeleteFramebuffers)
            load(glBindFramebuffer)
            load(glCheckFramebufferStatus)
            load(glFramebufferTexture2D)
            load(glBlitFramebuffer)

            load(glGenRenderbuffers)
            load(glDeleteRenderbuffers)
            load(glBindRenderbuffer)
            load(glRenderbufferStorage)
            load(glFramebufferRenderbuffer)

            load(glDrawArrays)
            load(glDrawElements)
            load(glDrawArraysInstanced)
            load(glDrawElementsInstanced)

            load(glBlendFunc)
            load(glBlendFuncSeparate)
            load(glBlendEquation)
            load(glBlendEquationSeparate)
            load(glBlendColor)
            load(glDepthFunc)
            load(glDepthMask)
            load(glStencilFunc)
            load(glStencilOp)
            load(glStencilMask)
            load(glColorMask)

            load(glReadPixels)
            load(glCopyTexSubImage2D)

            load(glFenceSync)
            load(glDeleteSync)
            load(glClientWaitSync)
            load(glGetSynciv)

            #undef load

            return interface;
        }
        
        struct GLvec2 {
            GLfloat x, y;
            
            GLvec2() : x(0), y(0) {}
            GLvec2(const ggeometry::Vec2& o) : x(o.x), y(o.y) {}
            template <typename A, typename B> constexpr GLvec2(A a, B b) : x((GLfloat)a), y((GLfloat)b) {}
            template <typename T> constexpr GLvec2(const T& o) : x((GLfloat)o), y((GLfloat)o) {}

            GLvec2 operator+(const GLvec2& o) const noexcept { return {x + o.x, y + o.y}; }
            GLvec2 operator-(const GLvec2& o) const noexcept { return {x - o.x, y - o.y}; }
            GLvec2 operator*(const GLvec2& o) const noexcept { return {x * o.x, y * o.y}; }
            GLvec2 operator/(const GLvec2& o) const noexcept { return {x / o.x, y / o.y}; }
            GLvec2 operator+(GLfloat o) const noexcept { return {x + o, y + o}; }
            GLvec2 operator-(GLfloat o) const noexcept { return {x - o, y - o}; }
            GLvec2 operator*(GLfloat o) const noexcept { return {x * o, y * o}; }
            GLvec2 operator/(GLfloat o) const noexcept { return {x / o, y / o}; }
            GLvec2 operator-() const noexcept { return {-x, -y}; }
            GLvec2& operator+=(const GLvec2& o) noexcept { x += o.x; y += o.y; return *this; }
            GLvec2& operator-=(const GLvec2& o) noexcept { x -= o.x; y -= o.y; return *this; }
            GLvec2& operator*=(const GLvec2& o) noexcept { x *= o.x; y *= o.y; return *this; }
            GLvec2& operator/=(const GLvec2& o) noexcept { x /= o.x; y /= o.y; return *this; }
            GLvec2& operator+=(GLfloat o) noexcept { x += o; y += o; return *this; }
            GLvec2& operator-=(GLfloat o) noexcept { x -= o; y -= o; return *this; }
            GLvec2& operator*=(GLfloat o) noexcept { x *= o; y *= o; return *this; }
            GLvec2& operator/=(GLfloat o) noexcept { x /= o; y /= o; return *this; }
            bool operator==(const GLvec2& o) const noexcept { return x == o.x && y == o.y; }
            bool operator!=(const GLvec2& o) const noexcept { return x != o.x || y != o.y; }
        };
        static_assert(offsetof(GLvec2, x) == 0, "GLvec2.x must be at offset 0");
        static_assert(offsetof(GLvec2, y) == sizeof(GLfloat), "GLvec2.y must be at offset 1");

        struct GLvec3 {
            GLfloat x, y, z;
            
            GLvec3() : x(0), y(0), z(0) {}
            template <typename A, typename B, typename C> constexpr GLvec3(A a, B b, C c) : x((GLfloat)a), y((GLfloat)b), z((GLfloat)c) {}
            template <typename T> constexpr GLvec3(const T& o) : x((GLfloat)o), y((GLfloat)o), z((GLfloat)o) {}

            GLvec3 operator+(const GLvec3& o) const noexcept { return {x + o.x, y + o.y, z + o.z}; }
            GLvec3 operator-(const GLvec3& o) const noexcept { return {x - o.x, y - o.y, z - o.z}; }
            GLvec3 operator*(const GLvec3& o) const noexcept { return {x * o.x, y * o.y, z * o.z}; }
            GLvec3 operator/(const GLvec3& o) const noexcept { return {x / o.x, y / o.y, z / o.z}; }
            GLvec3 operator+(GLfloat o) const noexcept { return {x + o, y + o, z + o}; }
            GLvec3 operator-(GLfloat o) const noexcept { return {x - o, y - o, z - o}; }
            GLvec3 operator*(GLfloat o) const noexcept { return {x * o, y * o, z * o}; }
            GLvec3 operator/(GLfloat o) const noexcept { return {x / o, y / o, z / o}; }
            GLvec3 operator-() const noexcept { return {-x, -y, -z}; }
            GLvec3& operator+=(const GLvec3& o) noexcept { x += o.x; y += o.y; z += o.z; return *this; }
            GLvec3& operator-=(const GLvec3& o) noexcept { x -= o.x; y -= o.y; z -= o.z; return *this; }
            GLvec3& operator*=(const GLvec3& o) noexcept { x *= o.x; y *= o.y; z *= o.z; return *this; }
            GLvec3& operator/=(const GLvec3& o) noexcept { x /= o.x; y /= o.y; z /= o.z; return *this; }
            GLvec3& operator+=(GLfloat o) noexcept { x += o; y += o; z += o; return *this; }
            GLvec3& operator-=(GLfloat o) noexcept { x -= o; y -= o; z -= o; return *this; }
            GLvec3& operator*=(GLfloat o) noexcept { x *= o; y *= o; z *= o; return *this; }
            GLvec3& operator/=(GLfloat o) noexcept { x /= o; y /= o; z /= o; return *this; }
            bool operator==(const GLvec3& o) const noexcept { return x == o.x && y == o.y && z == o.z; }
            bool operator!=(const GLvec3& o) const noexcept { return x != o.x || y != o.y || z != o.z; }
        };
        static_assert(offsetof(GLvec3, x) == 0, "GLvec3.x must be at offset 0");
        static_assert(offsetof(GLvec3, y) == sizeof(GLfloat), "GLvec3.y must be at offset 1");
        static_assert(offsetof(GLvec3, z) == sizeof(GLfloat) * 2, "GLvec3.z must be at offset 2");

        struct GLvec4 {
            GLfloat x, y, z, w;
            
            GLvec4() : x(0), y(0), z(0), w(0) {}
            GLvec4(const gcolor::Color& o) : x(o.r), y(o.g), z(o.b), w(o.a) {}
            template <typename A, typename B, typename C, typename D> constexpr GLvec4(A a, B b, C c, D d) : x((GLfloat)a), y((GLfloat)b), z((GLfloat)c), w((GLfloat)d) {}
            template <typename T> constexpr GLvec4(const T& o) : x((GLfloat)o), y((GLfloat)o), z((GLfloat)o), w((GLfloat)o) {}

            GLvec4 operator+(const GLvec4& o) const noexcept { return {x + o.x, y + o.y, z + o.z, w + o.w}; }
            GLvec4 operator-(const GLvec4& o) const noexcept { return {x - o.x, y - o.y, z - o.z, w - o.w}; }
            GLvec4 operator*(const GLvec4& o) const noexcept { return {x * o.x, y * o.y, z * o.z, w * o.w}; }
            GLvec4 operator/(const GLvec4& o) const noexcept { return {x / o.x, y / o.y, z / o.z, w / o.w}; }
            GLvec4 operator+(GLfloat o) const noexcept { return {x + o, y + o, z + o, w + o}; }
            GLvec4 operator-(GLfloat o) const noexcept { return {x - o, y - o, z - o, w - o}; }
            GLvec4 operator*(GLfloat o) const noexcept { return {x * o, y * o, z * o, w * o}; }
            GLvec4 operator/(GLfloat o) const noexcept { return {x / o, y / o, z / o, w / o}; }
            GLvec4 operator-() const noexcept { return {-x, -y, -z, -w}; }
            GLvec4& operator+=(const GLvec4& o) noexcept { x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
            GLvec4& operator-=(const GLvec4& o) noexcept { x -= o.x; y -= o.y; z -= o.z; w -= o.w; return *this; }
            GLvec4& operator*=(const GLvec4& o) noexcept { x *= o.x; y *= o.y; z *= o.z; w *= o.w; return *this; }
            GLvec4& operator/=(const GLvec4& o) noexcept { x /= o.x; y /= o.y; z /= o.z; w /= o.w; return *this; }
            GLvec4& operator+=(GLfloat o) noexcept { x += o; y += o; z += o; w += o; return *this; }
            GLvec4& operator-=(GLfloat o) noexcept { x -= o; y -= o; z -= o; w -= o; return *this; }
            GLvec4& operator*=(GLfloat o) noexcept { x *= o; y *= o; z *= o; w *= o; return *this; }
            GLvec4& operator/=(GLfloat o) noexcept { x /= o; y /= o; z /= o; w /= o; return *this; }
            bool operator==(const GLvec4& o) const noexcept { return x == o.x && y == o.y && z == o.z && w == o.w; }
            bool operator!=(const GLvec4& o) const noexcept { return x != o.x || y != o.y || z != o.z || w != o.w; }

            static GLvec4 White() noexcept { return { 1.0, 1.0, 1.0, 1.0 }; }
            static GLvec4 Black() noexcept { return { 0.0, 0.0, 0.0, 1.0 }; }
            static GLvec4 Red() noexcept { return { 1.0, 0.0, 0.0, 1.0 }; }
            static GLvec4 Green() noexcept { return { 0.0, 1.0, 0.0, 1.0 }; }
            static GLvec4 Blue() noexcept { return { 0.0, 0.0, 1.0, 1.0 }; }
            static GLvec4 Transparent() noexcept { return { 0.0, 0.0, 0.0, 0.0 }; }
            static GLvec4 Gray(GLfloat v = 0.5) noexcept { return { v, v, v, 1.0 }; }

            GLvec2 size() const noexcept { return { z - x, w - y }; }
        };
        static_assert(offsetof(GLvec4, x) == 0, "GLvec4.x must be at offset 0");
        static_assert(offsetof(GLvec4, y) == sizeof(GLfloat), "GLvec4.y must be at offset 1");
        static_assert(offsetof(GLvec4, z) == sizeof(GLfloat) * 2, "GLvec4.z must be at offset 2");
        static_assert(offsetof(GLvec4, w) == sizeof(GLfloat) * 3, "GLvec4.w must be at offset 3");

        struct BufferInfo;
        struct VertexArrayInfo;
        struct ShaderInfo;
        struct ProgramInfo;
        struct TextureInfo;
        struct FramebufferInfo;
        struct RenderbufferInfo;
        struct SyncInfo;
    
        struct Vertex {
            GLvec2 position;
            GLvec2 texCoord;
            GLvec4 color = GLvec4::White();
        };

        struct VertexPool {
            struct Chunk {
                std::vector<Vertex> vertices;
                uint64 offset;

                static gsp<Chunk> Make(uint64 size) {
                    auto* ck = new Chunk();
                    ck->vertices.resize(size);
                    return gsp<Chunk>(ck);
                }

                Vertex* alloc(uint64 count) noexcept {
                    if (offset + count > vertices.size()) return nullptr;
                    auto* ret = &vertices[offset];
                    offset += count;
                    return ret;
                }
            };

            static constexpr uint64 defaultChunkSize = 4096;
            static constexpr uint64 defaultChunkCount = 4;

            std::vector<gsp<Chunk>> chunks;
            uint64 offset;

            static gsp<VertexPool> Make() {
                auto* vp = new VertexPool();
                vp->chunks.resize(defaultChunkCount);
                for (uint64 i = 0; i < defaultChunkCount; i++) {
                    vp->chunks[i] = Chunk::Make(defaultChunkSize);
                }
                return gsp<VertexPool>(vp);
            }

            struct AllocResult {
                Vertex* vertices;
                uint64 count;
                uint64 sig;
                uint64 offset;

                Vertex* next() noexcept {
                    gassert::assert(offset < count, "VertexPool::AllocResult::next() called after end of allocation");
                    return &vertices[offset++];
                }

                void transformBack(const Transform2D& tf, uint64 count) noexcept {
                    count = std::min<uint64>(count, offset);

                    for (uint64 i = 0; i < count; i++) {
                        auto index = offset - 1 - i;
                        auto& vert = vertices[index];
                        auto newPosition = tf.transformPoint(vert.position.x, vert.position.y);
                        vert.position = { newPosition.x, newPosition.y };
                    }
                }

                void reset() noexcept {
                    offset = 0;
                }

                Vertex* begin() noexcept { return vertices; }
                Vertex* end() noexcept { return vertices + count; }
                const Vertex* begin() const noexcept { return vertices; }
                const Vertex* end() const noexcept { return vertices + count; }
            };

            AllocResult alloc(uint64 count) noexcept {
                while (offset < chunks.size()) {
                    auto& chunk = chunks[offset];
                    auto* ptr = chunk->alloc(count);
                    if (ptr) return allocSuccess(ptr, count);
                    offset++;
                }

                chunks.push_back(Chunk::Make(count + defaultChunkSize));
                return allocSuccess(chunks[offset]->alloc(count), count);
            }

            void reset() noexcept {
                offset = 0;
                for (auto& chunk : chunks) chunk->offset = 0;
                sig++;
            }

            bool valid(const AllocResult& result) const noexcept {
                return result.sig == sig;
            }

            private:
            uint64 sig;

            AllocResult allocSuccess(Vertex* ptr, uint64 count) {
                return {
                    .vertices = ptr,
                    .count = count,
                    .sig = sig
                };
            }
        };

        struct Mesh {
            VertexPool::AllocResult vertices;
            TextureInfo* texture;
            ProgramInfo* program;
            GLvec4 color;

            auto* vnext() noexcept { return vertices.next(); }

            void addRect(const GLvec2& position, const GLvec2& size, const GLvec2& uvPosition, const GLvec2& uvSize, const GLvec4& color = GLvec4::White()) noexcept {
                if (size.x <= 0 || size.y <= 0) return;

                *vertices.next() = { position, uvPosition, color };
                *vertices.next() = { position + GLvec2 { size.x, 0 }, uvPosition + GLvec2 { uvSize.x, 0 }, color };
                *vertices.next() = { position + size, uvPosition + uvSize, color };

                *vertices.next() = { position, uvPosition, color };
                *vertices.next() = { position + GLvec2 { 0, size.y }, uvPosition + GLvec2 { 0, uvSize.y }, color };
                *vertices.next() = { position + size, uvPosition + uvSize, color };
            }

            void addFullRect(const GLvec4& color = GLvec4::White()) noexcept {
                addRect({ -1, -1 }, { 2, 2 }, { 0, 0 }, { 1, 1 }, color);
            }

            void addRectCentered(const GLvec2& center, const GLvec2& radius, const GLvec2& uvCenter, const GLvec2& uvRadius, const GLvec4& color = GLvec4::White()) noexcept {
                addRect(center - radius, radius * 2, uvCenter - uvRadius, uvRadius * 2, color);
            }
        };

        template <auto Deleter, typename T = GLuint>
        struct GlResource {
            GL33CoreInterface* glRef;
            T id;

            GlResource() = default;
            NO_COPY(GlResource)

            GlResource(GlResource&& other) noexcept : id(std::exchange(other.id, 0)) {}

            GlResource& operator=(GlResource&& other) noexcept {
                if (this != &other) {
                    reset();
                    id = std::exchange(other.id, 0);
                }

                return *this;
            }

            ~GlResource() noexcept {
                reset();
            }

            private:
            void reset() noexcept {
                if (id) Deleter(glRef, id);
                id = 0;
            }
        };

        struct BufferInfo {
            BufferInfo() = default;
            NO_COPY(BufferInfo)

            GlResource<[](GL33CoreInterface* glRef, GLuint id) { glRef->glDeleteBuffers(1, &id); }> res;
            GLenum target;

            struct UsingGuard {
                BufferInfo* ref;
                GLuint savedId;

                UsingGuard(BufferInfo& buf) : ref(&buf) {
                    savedId = ref->res.glRef->glBindBufferProxy(ref->target, ref->res.id);
                }

                NO_COPY(UsingGuard)
                NO_MOVE(UsingGuard)

                void data(GLsizeiptr size, const void* data, GLenum usage) {
                    ref->res.glRef->glBufferData(ref->target, size, data, usage);
                }

                template <typename T>
                void data(std::span<const T> data, GLenum usage) {
                    data(ref->target, data.size() * sizeof(T), data.data(), usage);
                }

                struct MappingGuard {
                    UsingGuard* ref;
                    void* data;

                    MappingGuard(UsingGuard& buffer, GLsizei offset, GLsizei length, GLbitfield access) : ref(&buffer) {
                        data = ref->ref->res.glRef->glMapBufferRange(ref->ref->target, offset, length, access);
                    }

                    NO_COPY(MappingGuard)
                    NO_MOVE(MappingGuard)

                    ~MappingGuard() {
                        ref->ref->res.glRef->glUnmapBuffer(ref->ref->target);
                    }
                };

                MappingGuard map(GLsizei offset, GLsizei length, GLbitfield access) {
                    return MappingGuard(*this, offset, length, access);
                }

                gsp<MappingGuard> mapSp(GLsizei offset, GLsizei length, GLbitfield access) {
                    auto* guard = new MappingGuard(*this, offset, length, access);
                    return gsp<MappingGuard>(guard);
                }

                ~UsingGuard() {
                    ref->res.glRef->glBindBufferProxy(ref->target, savedId);
                }
            };

            UsingGuard use() {
                return UsingGuard(*this);
            }

            gsp<UsingGuard> useSp() {
                auto* guard = new UsingGuard(*this);
                return gsp<UsingGuard>(guard);
            }
        };

        struct VertexArrayInfo {
            VertexArrayInfo() = default;
            NO_COPY(VertexArrayInfo)

            GlResource<[](GL33CoreInterface* glRef, GLuint id) { glRef->glDeleteVertexArrays(1, &id); }> res;

            struct UsingGuard {
                VertexArrayInfo* ref;
                GLuint savedId;

                UsingGuard(VertexArrayInfo& vao) : ref(&vao) {
                    savedId = ref->res.glRef->glBindVertexArrayProxy(ref->res.id);
                }

                NO_COPY(UsingGuard)
                NO_MOVE(UsingGuard)

                void enable(GLuint index) { ref->res.glRef->glEnableVertexAttribArray(index); }
                void disable(GLuint index) { ref->res.glRef->glDisableVertexAttribArray(index); }

                void pointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) {
                    ref->res.glRef->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
                }

                void iPointer(GLuint index, GLint size, GLenum type, GLsizei stride, const void* pointer) {
                    ref->res.glRef->glVertexAttribIPointer(index, size, type, stride, pointer);
                }

                ~UsingGuard() {
                    ref->res.glRef->glBindVertexArrayProxy(savedId);
                }
            };

            UsingGuard use() {
                return UsingGuard(*this);
            }

            gsp<UsingGuard> useSp() {
                auto* guard = new UsingGuard(*this);
                return gsp<UsingGuard>(guard);
            }
        };

        struct ShaderInfo {
            ShaderInfo() = default;
            NO_COPY(ShaderInfo)

            GlResource<[](GL33CoreInterface* glRef, GLuint id) { glRef->glDeleteShader(id); }> res;
            GLenum type;

            void source(std::string source) {
                if (res.glRef->isGles) {
                    source = gstrutils::replaceStringWith(source, "#version 330 core", "#version 300 es\nprecision highp float;");
                }

                auto pos = source.find("#version");
                if (pos == std::string::npos) throw std::runtime_error("No #version directive found in shader source");
                source = source.substr(pos);

                const GLchar* ptr = (GLchar*)source.c_str();
                GLint len = source.length();
                res.glRef->glShaderSource(res.id, 1, &ptr, &len);
            }

            bool compile(std::string* outLog = nullptr) {
                res.glRef->glCompileShader(res.id);

                GLint status = 0;
                res.glRef->glGetShaderiv(res.id, GL_COMPILE_STATUS, &status);
                if (outLog) {
                    GLint logLen;
                    res.glRef->glGetShaderiv(res.id, GL_INFO_LOG_LENGTH, &logLen);
                    if (logLen > 0) {
                        outLog->resize(logLen);
                        GLsizei written = 0;
                        res.glRef->glGetShaderInfoLog(res.id, logLen, &written, (GLchar*)outLog->data());
                        outLog->resize(written);
                    }
                }
                return status == GL_TRUE;
            }
        };

        struct VertexLayout {
            gsp<VertexArrayInfo> vao;
            gsp<BufferInfo> vbo;
        };

        struct VertexLayoutPool {
            std::vector<VertexLayout> layouts;
            uint64 currentIndex;
            uint64 frameSig;

            using LayoutCreator = std::function<VertexLayout()>;
            void resize(uint64 size,const LayoutCreator& creator) {
                layouts.resize(size);
                for (auto& layout : layouts) layout = creator();
            }

            using ConfigureFunc = std::function<void(VertexArrayInfo*, BufferInfo*)>;
            void configure(const ConfigureFunc& func) {
                for (auto& layout : layouts) {
                    func(layout.vao.get(), layout.vbo.get());
                }
            }

            void checkAndNext(uint64 newFrameSig) noexcept {
                if (frameSig != newFrameSig) {
                    frameSig = newFrameSig;
                    currentIndex = (currentIndex + 1) % layouts.size();
                }
            }

            VertexLayout& current() noexcept {
                return layouts[currentIndex];
            }
        };

        struct ProgramInfo {
            ProgramInfo() = default;
            NO_COPY(ProgramInfo)

            GlResource<[](GL33CoreInterface* glRef, GLuint id) { glRef->glDeleteProgram(id); }> res;
            VertexLayoutPool vertexLayoutPool;

            using BufferFillerFunc = std::function<void(ProgramInfo*, const VertexLayout&, VertexPool::AllocResult&)>;
            BufferFillerFunc bufferFiller;

            struct {
                std::optional<std::string> textureUniformName = "uTexture";
                std::optional<std::string> colorUniformName = "uColor";
            } fragConfig;

            void attachShader(ShaderInfo* shader) {
                res.glRef->glAttachShader(res.id, shader->res.id);
                attribLocations.clear();
                uniformLocations.clear();
            }

            bool link(std::string* outLog = nullptr) {
                res.glRef->glLinkProgram(res.id);

                GLint status = 0;
                res.glRef->glGetProgramiv(res.id, GL_LINK_STATUS, &status);
                if (outLog) {
                    GLint logLen = 0;
                    res.glRef->glGetProgramiv(res.id, GL_INFO_LOG_LENGTH, &logLen);
                    if (logLen > 0) {
                        outLog->resize(logLen);
                        GLsizei written = 0;
                        res.glRef->glGetProgramInfoLog(res.id, logLen, &written, (GLchar*)outLog->data());
                        outLog->resize(written);
                    }
                }
                return status == GL_TRUE;
            }

            struct UsingGuard {
                ProgramInfo* ref;
                GLuint savedId;

                UsingGuard(ProgramInfo& prog) : ref(&prog) {
                    savedId = ref->res.glRef->glUseProgramProxy(ref->res.id);
                }

                NO_COPY(UsingGuard)
                NO_MOVE(UsingGuard)

                ~UsingGuard() {
                    ref->res.glRef->glUseProgramProxy(savedId);
                }
            };

            UsingGuard use() {
                return UsingGuard(*this);
            }

            gsp<UsingGuard> useSp() {
                auto* guard = new UsingGuard(*this);
                return gsp<UsingGuard>(guard);
            }
            
            struct Location {
                ProgramInfo* ref;

                GLint location;

                void setf(GLfloat v0) noexcept { ref->res.glRef->glUniform1f(location, v0); }
                void setf(GLfloat v0, GLfloat v1) noexcept { ref->res.glRef->glUniform2f(location, v0, v1); }
                void setf(GLfloat v0, GLfloat v1, GLfloat v2) noexcept { ref->res.glRef->glUniform3f(location, v0, v1, v2); }
                void setf(GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) noexcept { ref->res.glRef->glUniform4f(location, v0, v1, v2, v3); }
                
                void seti(GLint v0) noexcept { ref->res.glRef->glUniform1i(location, v0); }
                void seti(GLint v0, GLint v1) noexcept { ref->res.glRef->glUniform2i(location, v0, v1); }
                void seti(GLint v0, GLint v1, GLint v2) noexcept { ref->res.glRef->glUniform3i(location, v0, v1, v2); }
                void seti(GLint v0, GLint v1, GLint v2, GLint v3) noexcept { ref->res.glRef->glUniform4i(location, v0, v1, v2, v3); }

                void setv2(const GLvec2& value) noexcept { setf(value.x, value.y); }
                void setv3(const GLvec3& value) noexcept { setf(value.x, value.y, value.z); }
                void setv4(const GLvec4& value) noexcept { setf(value.x, value.y, value.z, value.w); }

                void setMatrix2fv(GLsizei count, GLboolean transpose, const GLfloat* value) noexcept { ref->res.glRef->glUniformMatrix2fv(location, count, transpose, value); }
                void setMatrix3fv(GLsizei count, GLboolean transpose, const GLfloat* value) noexcept { ref->res.glRef->glUniformMatrix3fv(location, count, transpose, value); }
                void setMatrix4fv(GLsizei count, GLboolean transpose, const GLfloat* value) noexcept { ref->res.glRef->glUniformMatrix4fv(location, count, transpose, value); }
            };
            
            GLint getAttribLocationPosition(const std::string& name) noexcept {
                if (attribLocations.find(name) == attribLocations.end()) {
                    attribLocations[name] = res.glRef->glGetAttribLocation(res.id, (GLchar*)name.c_str());
                }

                return attribLocations[name];
            }

            GLint getUniformLocationPosition(const std::string& name) noexcept {
                if (uniformLocations.find(name) == uniformLocations.end()) {
                    uniformLocations[name] = res.glRef->glGetUniformLocation(res.id, (GLchar*)name.c_str());
                }

                return uniformLocations[name];
            }

            Location getAttribLocation(const std::string& name) noexcept {
                Location result;
                result.ref = this;
                result.location = getAttribLocationPosition(name);
                return result;
            }

            Location getUniformLocation(const std::string& name) noexcept {
                Location result;
                result.ref = this;
                result.location = getUniformLocationPosition(name);
                return result;
            }

            void setVertices(VertexPool::AllocResult& vertices) {
                if (!bufferFiller) return;
                auto& vertexLayout = vertexLayoutPool.current();
                bufferFiller(this, vertexLayout, vertices);
            }

            private:
            std::unordered_map<std::string, GLint> attribLocations;
            std::unordered_map<std::string, GLint> uniformLocations;
        };

        struct TextureInfo {
            TextureInfo() = default;
            NO_COPY(TextureInfo)

            GlResource<[](GL33CoreInterface* glRef, GLuint id) { glRef->glDeleteTextures(1, &id); }> res;
            GLenum target;
            
            gsp<TextureInfo> pingPong;
            GLsizei width, height;

            struct UsingGuard {
                TextureInfo* ref;

                GLenum index;
                GLuint savedId;

                UsingGuard(TextureInfo& tex, GLenum index) : ref(&tex), index(index) {
                    ref->res.glRef->glActiveTexture(GL_TEXTURE0 + index);
                    savedId = ref->res.glRef->glBindTextureProxy(ref->target, ref->res.id);
                }

                void image2D(GLsizei width, GLsizei height, const void* pixels, bool enableMipmap = false) {
                    if (width <= 0 || height <= 0) return;

                    ref->res.glRef->glTexImage2D(ref->target, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

                    GLfloat maxAniso = 0.0;
                    ref->res.glRef->glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAniso);

                    if (maxAniso > 0.0) {
                        ref->res.glRef->glTexParameterf(ref->target, GL_TEXTURE_MAX_ANISOTROPY_EXT, maxAniso);
                    }

                    ref->res.glRef->glTexParameteri(ref->target, GL_TEXTURE_MIN_FILTER, enableMipmap ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
                    ref->res.glRef->glTexParameteri(ref->target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    ref->res.glRef->glTexParameteri(ref->target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                    ref->res.glRef->glTexParameteri(ref->target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                    if (enableMipmap) {
                        ref->res.glRef->glGenerateMipmap(ref->target);
                    }

                    ref->width = width;
                    ref->height = height;
                }

                void image2D(const DecodedRGBATexture& decoded, bool enableMipmap = false) {
                    image2D(decoded.width, decoded.height, (void*)decoded.data.data(), enableMipmap);
                }

                void generateMipmap() {
                    ref->res.glRef->glGenerateMipmap(ref->target);
                }

                void image2DMultisample(GLsizei width, GLsizei height, GLsizei samples) {
                    ref->res.glRef->glTexStorage2DMultisample(ref->target, samples, GL_RGBA8, width, height, GL_TRUE);
                    ref->width = width; ref->height = height;
                }

                ~UsingGuard() {
                    ref->res.glRef->glBindTextureProxy(ref->target, savedId);
                }
            };

            UsingGuard use(GLenum index = 0) {
                return UsingGuard(*this, index);
            }

            gsp<UsingGuard> useSp(GLenum index = 0) {
                auto* guard = new UsingGuard(*this, index);
                return gsp<UsingGuard>(guard);
            }

            bool isSameSize(TextureInfo* other) const noexcept {
                return other->width == width && other->height == height;
            }

            bool isSameSize(GLsizei width, GLsizei height) const noexcept {
                return this->width == width && this->height == height;
            }

            GLvec2 size() const noexcept {
                return { width, height };
            }
        };

        struct FramebufferInfo {
            FramebufferInfo() = default;
            NO_COPY(FramebufferInfo)

            GlResource<[](GL33CoreInterface* glRef, GLuint id) { glRef->glDeleteFramebuffers(1, &id); }> res;
            
            struct UsingGuard {
                FramebufferInfo* ref;
                GLenum target;
                GLuint savedId;
                
                UsingGuard(FramebufferInfo& framebuffer, TextureInfo* texture, GLenum target) : ref(&framebuffer), target(target) {
                    gassert::assert(target != GL_FRAMEBUFFER, "FramebufferInfo::UsingGuard: target must not be GL_FRAMEBUFFER");
                    
                    savedId = ref->res.glRef->glBindFramebufferProxy(target, ref->res.id);
                    ref->res.glRef->glFramebufferTexture2D(target, GL_COLOR_ATTACHMENT0, texture->target, texture->res.id, 0);
                }

                ~UsingGuard() {
                    ref->res.glRef->glBindFramebufferProxy(target, savedId);
                }
            };

            UsingGuard use(TextureInfo* texture, GLenum target) {
                return UsingGuard(*this, texture, target);
            }

            gsp<UsingGuard> useSp(TextureInfo* texture, GLenum target) {
                auto* guard = new UsingGuard(*this, texture, target);
                return gsp<UsingGuard>(guard);
            }
        };

        struct RenderbufferInfo {
            RenderbufferInfo() = default;
            NO_COPY(RenderbufferInfo)

            GlResource<[](GL33CoreInterface* glRef, GLuint id) { glRef->glDeleteRenderbuffers(1, &id); }> res;

            struct UsingGuard {
                RenderbufferInfo* ref;
                GLuint savedId;

                UsingGuard(RenderbufferInfo& renderbuffer) : ref(&renderbuffer) {
                    savedId = ref->res.glRef->glBindRenderbufferProxy(ref->res.id);
                }

                void storage(GLenum internalformat, GLsizei width, GLsizei height) {
                    ref->res.glRef->glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
                }

                ~UsingGuard() {
                    ref->res.glRef->glBindRenderbufferProxy(savedId);
                }
            };

            UsingGuard use() {
                return UsingGuard(*this);
            }

            gsp<UsingGuard> useSp() {
                auto* guard = new UsingGuard(*this);
                return gsp<UsingGuard>(guard);
            }
        };

        struct SyncInfo {
            SyncInfo() = default;
            NO_COPY(SyncInfo)

            GlResource<[](GL33CoreInterface* glRef, GLsync sync) { glRef->glDeleteSync(sync); }, GLsync> res;

            GLenum wait(GLbitfield flags, GLuint64 timeout = GL_TIMEOUT_IGNORED) const {
                return res.glRef->glClientWaitSync(res.id, flags, timeout);
            }

            bool isSignaled() const noexcept {
                GLint status;
                res.glRef->glGetSynciv(res.id, GL_SYNC_STATUS, 1, nullptr, &status);
                return status == GL_SIGNALED;
            }
        };

        struct GL33Context {
            GL33Context() = default;
            NO_COPY(GL33Context)
            NO_MOVE(GL33Context)

            GL33CoreInterface gl;

            uint64 drawCallsCount = 0;

            static gsp<GL33Context> Make(const GL33CoreInterface& interface) {
                auto* ctx = new GL33Context();
                ctx->gl = interface;
                ctx->initDefaultResources();
                return gsp<GL33Context>(ctx);
            }

            struct GLFeatureGuard {
                GL33Context* glCtx;
                GLenum cap; bool enable;

                GLFeatureGuard(GL33Context* glCtx, GLenum cap, bool enable) : glCtx(glCtx), cap(cap), enable(enable) {}
                NO_COPY(GLFeatureGuard)
                NO_MOVE(GLFeatureGuard)

                ~GLFeatureGuard() {
                    if (enable && !glCtx->gl.glIsEnabled(cap)) glCtx->gl.glEnable(cap);
                    else if (!enable && glCtx->gl.glIsEnabled(cap)) glCtx->gl.glDisable(cap);
                }
            };

            GLFeatureGuard getFeatureGuard(GLenum cap) noexcept {
                return GLFeatureGuard(this, cap, gl.glIsEnabled(cap));
            }

            gsp<GLFeatureGuard> getFeatureGuardSp(GLenum cap) noexcept {
                auto* guard = new GLFeatureGuard(this, cap, gl.glIsEnabled(cap));
                return gsp<GLFeatureGuard>(guard);
            }

            void setViewport(GLint x, GLint y, GLsizei width, GLsizei height) noexcept {
                currentViewport = { x, y, width, height };
                gl.glViewport(x, y, width, height);
            }

            void setViewport(GLsizei width, GLsizei height) noexcept { setViewport(0, 0, width, height); }
            void setViewport(const GLvec2& xy, const GLvec2& wh) noexcept { setViewport(xy.x, xy.y, wh.x, wh.y); }
            template <typename T> void setViewport(const std::pair<T, T>& xy) noexcept { setViewport(xy.first, xy.second); }
            void setViewport(const GLvec4& rect) noexcept { setViewport(rect.x, rect.y, rect.z, rect.w); }

            gsp<BufferInfo> createBuffer(GLenum target = GL_ARRAY_BUFFER) {
                auto* info = new BufferInfo();
                info->res.glRef = &gl;
                info->target = target;
                gl.glGenBuffers(1, &info->res.id);
                return gsp<BufferInfo>(info);
            }

            gsp<VertexArrayInfo> createVertexArray() {
                auto* info = new VertexArrayInfo();
                info->res.glRef = &gl;
                gl.glGenVertexArrays(1, &info->res.id);
                return gsp<VertexArrayInfo>(info);
            }

            gsp<ShaderInfo> createShader(GLenum type) {
                auto* info = new ShaderInfo();
                info->res.glRef = &gl;
                info->res.id = gl.glCreateShader(type);
                info->type = type;
                return gsp<ShaderInfo>(info);
            }

            gsp<ProgramInfo> createProgram() {
                auto* info = new ProgramInfo();
                info->res.glRef = &gl;
                info->res.id = gl.glCreateProgram();
                return gsp<ProgramInfo>(info);
            }

            gsp<TextureInfo> createTexture(GLenum target = GL_TEXTURE_2D) {
                auto* info = new TextureInfo();
                info->res.glRef = &gl;
                info->target = target;
                gl.glGenTextures(1, &info->res.id);
                return gsp<TextureInfo>(info);
            }

            gsp<FramebufferInfo> createFramebuffer() {
                auto* info = new FramebufferInfo();
                info->res.glRef = &gl;
                gl.glGenFramebuffers(1, &info->res.id);
                return gsp<FramebufferInfo>(info);
            }

            gsp<RenderbufferInfo> createRenderbuffer() {
                auto* info = new RenderbufferInfo();
                info->res.glRef = &gl;
                gl.glGenRenderbuffers(1, &info->res.id);
                return gsp<RenderbufferInfo>(info);
            }

            gsp<SyncInfo> createSync(GLenum condition = GL_SYNC_GPU_COMMANDS_COMPLETE, GLbitfield flags = 0) {
                auto* info = new SyncInfo();
                info->res.glRef = &gl;
                info->res.id = gl.glFenceSync(condition, flags);
                return gsp<SyncInfo>(info);
            }

            struct CreateProgramConfig {
                std::string vertCode;
                std::string fragCode;
                std::function<void(ProgramInfo*, VertexArrayInfo*, BufferInfo*)> vertConfigurer;

                CreateProgramConfig& defaultColorVert() {
                    if (vertCode.empty()) vertCode = R"(
#version 330 core

in vec2 inPosition;
in vec2 inTexCoord;
in vec4 inColor;

out vec2 fragTexCoord;
out vec4 vColor;

void main() {
    gl_Position = vec4(inPosition, 0.0, 1.0);

    fragTexCoord = inTexCoord;
    vColor = inColor;
}
)";
                    vertConfigurer = [](ProgramInfo* prog, VertexArrayInfo* vao, BufferInfo* vbo) {
                        auto vaoGuard = vao->use();
                        auto vboGuard = vbo->use();
                        auto inPosition = prog->getAttribLocationPosition("inPosition");
                        auto inTexCoord = prog->getAttribLocationPosition("inTexCoord");
                        auto inColor = prog->getAttribLocationPosition("inColor");
                        vaoGuard.enable(inPosition);
                        vaoGuard.enable(inTexCoord);
                        vaoGuard.enable(inColor);
                        vaoGuard.pointer(inPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
                        vaoGuard.pointer(inTexCoord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
                        vaoGuard.pointer(inColor, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
                    };

                    return *this;
                }

                CreateProgramConfig& defaultColorFrag() {
                    if (fragCode.empty()) fragCode = R"(
#version 330 core

in vec2 fragTexCoord;
in vec4 vColor;

uniform vec4 uColor;
uniform sampler2D uTexture;

out vec4 outColor;

void main() {
    outColor = vColor * uColor * texture(uTexture, fragTexCoord);
}
)";
                    return *this;
                }

                CreateProgramConfig& defaultStencilVert() {
                    if (vertCode.empty()) vertCode = R"(
#version 330 core

in vec2 inPosition;

void main() {
    gl_Position = vec4(inPosition, 0.0, 1.0);
}
)";
                    vertConfigurer = [](ProgramInfo* prog, VertexArrayInfo* vao, BufferInfo* vbo) {
                        auto vaoGuard = vao->use();
                        auto vboGuard = vbo->use();
                        auto inPosition = prog->getAttribLocationPosition("inPosition");
                        vaoGuard.enable(inPosition);
                        vaoGuard.pointer(inPosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
                    };
                    
                    return *this;
                }

                CreateProgramConfig& defaultStencilFrag() {
                    if (fragCode.empty()) fragCode = R"(
#version 330 core

out vec4 outColor;

void main() {
    outColor = vec4(1.0);
}
)";
                    return *this;
                }
            };

            gsp<ProgramInfo> createConfiguredProgram(const CreateProgramConfig& config) {
                auto vert = createShader(GL_VERTEX_SHADER);
                auto frag = createShader(GL_FRAGMENT_SHADER);
                
                vert->source(config.vertCode);
                frag->source(config.fragCode);

                std::string log;
                if (!vert->compile(&log)) throw std::runtime_error("vertex compile: " + log);
                if (!frag->compile(&log)) throw std::runtime_error("fragment compile: " + log);

                auto prog = createProgram();
                prog->attachShader(vert.get());
                prog->attachShader(frag.get());
                if (!prog->link(&log)) throw std::runtime_error("program link: " + log);

                prog->vertexLayoutPool.resize(8, [&]() { return VertexLayout { .vao = createVertexArray(), .vbo = createBuffer() }; });
                prog->vertexLayoutPool.configure([&](VertexArrayInfo* vao, BufferInfo* vbo) {
                    config.vertConfigurer(prog.get(), vao, vbo);
                });

                prog->bufferFiller = [](ProgramInfo* prog, const VertexLayout& vertexLayout, VertexPool::AllocResult& vertices) {
                    auto vaoGuard = vertexLayout.vao->use();
                    auto vboGuard = vertexLayout.vbo->use();
                    vboGuard.data(
                        vertices.count * sizeof(Vertex),
                        vertices.vertices,
                        GL_DYNAMIC_DRAW
                    );
                };

                return prog;
            }
            
            struct ProgramPresets {
                static gsp<ProgramInfo> gaussianBlur(GL33Context* glCtx) {
                    auto prog = glCtx->createConfiguredProgram(CreateProgramConfig { .fragCode = R"(
#version 330 core

in vec2 fragTexCoord;

uniform sampler2D uTexture;

uniform vec2 uDelta; // (0, 1) or (1, 0)
uniform float uRadius; // 0.0 - 1.0
uniform int uIterations;

out vec4 outColor;

vec4 sampleTexture(vec2 texCoord) {
    return texture(uTexture, texCoord);
}

float gaussian(float x) {
    return exp(-x * x / 0.24);
}

void main() {
    vec4 sum = vec4(0.0);
    float wsum = 0.0;
    
    for (int i = -uIterations; i <= uIterations; i++) {
        float offset = float(i) / float(uIterations);
        float weight = gaussian(offset);
        sum += sampleTexture(fragTexCoord + uDelta * offset * uRadius) * weight;
        wsum += weight;
    }

    outColor = sum / wsum;
    outColor.a = 1.0;
}
)" }.defaultColorVert());
                    prog->fragConfig.colorUniformName = std::nullopt;
                    return prog;
                }

                static gsp<ProgramInfo> yuvConverter(GL33Context* glCtx) {
                    auto prog = glCtx->createConfiguredProgram(CreateProgramConfig { .fragCode = R"(
#version 330 core

in vec2 fragTexCoord;

uniform sampler2D uTexture;
uniform ivec2 uResolution;
uniform bool uFlipY;

out vec4 outColor;

vec3 getPixel(int x, int y) {
    return texelFetch(uTexture, ivec2(x, uResolution.y - y - 1), 0).xyz;
}

float getY(int x, int y) {
    vec3 pixel = getPixel(x, y);
    return dot(pixel, vec3(0.299, 0.587, 0.114));
}

float getU(int x, int y) {
    vec3 pixel = (
        getPixel(x, y)
        + getPixel(x, y + 1)
        + getPixel(x + 1, y)
        + getPixel(x + 1, y + 1)
    ) * 0.25;
    return dot(pixel, vec3(-0.168736, -0.331264, 0.5)) + 0.5;
}

float getV(int x, int y) {
    vec3 pixel = (
        getPixel(x, y)
        + getPixel(x, y + 1)
        + getPixel(x + 1, y)
        + getPixel(x + 1, y + 1)
    ) * 0.25;
    return dot(pixel, vec3(0.5, -0.418688, -0.081312)) + 0.5;
}

float getYI(int index) {
    return getY(index % uResolution.x, index / uResolution.x);
}

float getUI(int index) {
    return getU((index % (uResolution.x / 2)) * 2, index / (uResolution.x / 2) * 2);
}

float getVI(int index) {
    return getV((index % (uResolution.x / 2)) * 2, index / (uResolution.x / 2) * 2);
}

void main() {
    int w = uResolution.x; int h = uResolution.y;
    ivec2 curr_pos = ivec2(fragTexCoord * vec2(uResolution));
    if (!uFlipY) curr_pos.y = h - curr_pos.y - 1;
    int byte_index = (int(curr_pos.x) + int(curr_pos.y) * w) * 4;

    int y_bytes = w * h; int uv_bytes = y_bytes / 4;

    if (byte_index < y_bytes) {
        int pixel_index = byte_index;
        outColor = vec4(
            getYI(pixel_index), getYI(pixel_index + 1),
            getYI(pixel_index + 2), getYI(pixel_index + 3)
        );
    } else if (byte_index < y_bytes + uv_bytes) {
        int pixel_index = byte_index - y_bytes;
        outColor = vec4(
            getUI(pixel_index), getUI(pixel_index + 1),
            getUI(pixel_index + 2), getUI(pixel_index + 3)
        );
    } else if (byte_index < y_bytes + uv_bytes * 2) {
        int pixel_index = byte_index - y_bytes - uv_bytes;
        outColor = vec4(
            getVI(pixel_index), getVI(pixel_index + 1),
            getVI(pixel_index + 2), getVI(pixel_index + 3)
        );
    } else outColor = vec4(0);
}
)" }.defaultColorVert());
                    prog->fragConfig.colorUniformName = std::nullopt;
                    return prog;
                }

                static gsp<ProgramInfo> circle(GL33Context* glCtx) {
                    return glCtx->createConfiguredProgram(CreateProgramConfig { .fragCode = R"(
#version 330 core

in vec2 fragTexCoord;
in vec4 vColor;

uniform vec4 uColor;
uniform sampler2D uTexture;

out vec4 outColor;

void main() {
    outColor = vColor * uColor * texture(uTexture, fragTexCoord);

    float dist = length(fragTexCoord - vec2(0.5));
    float edgeWidth = fwidth(dist);
    float alpha = 1.0 - smoothstep(0.5 - edgeWidth, 0.5, dist);
    outColor.a *= alpha;
}
)" }.defaultColorVert());
                }
            };

            void drawMesh(Mesh& mesh) noexcept {
                if (!vertexPool->valid(mesh.vertices)) {
                    std::abort();
                }

                auto* prog = mesh.program ? mesh.program : defaultProgram.get();
                auto* tex = mesh.texture ? mesh.texture : defaultWhiteTexture.get();

                prog->vertexLayoutPool.checkAndNext(frameSig);
                prog->setVertices(mesh.vertices);

                auto progGuard = prog->use();
                auto& vertexLayout = prog->vertexLayoutPool.current();
                auto vaoGuard = vertexLayout.vao->use();
                auto texGuard = tex->use();

                if (prog->fragConfig.colorUniformName.has_value()) {
                    prog->getUniformLocation(prog->fragConfig.colorUniformName.value()).setv4(mesh.color);
                }

                if (prog->fragConfig.textureUniformName.has_value()) {
                    prog->getUniformLocation(prog->fragConfig.textureUniformName.value()).seti(texGuard.index);
                }

                gl.glDrawArrays(GL_TRIANGLES, 0, mesh.vertices.count);
                drawCallsCount++;
            }

            GLvec4 getViewport() const noexcept { return currentViewport; }

            struct ViewportGuard {
                GL33Context* glCtx;
                GLvec4 vp;

                ViewportGuard(GL33Context* glCtx, GLvec4 vp) : glCtx(glCtx), vp(vp) {}
                NO_COPY(ViewportGuard)
                NO_MOVE(ViewportGuard)

                ~ViewportGuard() { glCtx->setViewport(vp); }
            };

            ViewportGuard getViewportGuard() noexcept {
                return ViewportGuard(this, getViewport());
            }

            gsp<ViewportGuard> getViewportGuardSp() noexcept {
                auto* guard = new ViewportGuard(this, getViewport());
                return gsp<ViewportGuard>(guard);
            }

            void copyTexture(TextureInfo* src, TextureInfo* dst) noexcept {
                if (!dst->isSameSize(src)) {
                    dst->use().image2D(src->width, src->height, nullptr);
                }

                auto tempReadFbo = allocTempFramebuffer();
                auto tempReadFboGuard = tempReadFbo.get()->use(src, GL_READ_FRAMEBUFFER);
                auto dstGuard = dst->use();

                gl.glCopyTexSubImage2D(
                    GL_TEXTURE_2D, 0,
                    0, 0,
                    0, 0,
                    src->width, src->height
                );
            }

            void copyCurrentToTexture(TextureInfo* dst) noexcept {
                auto kfboGuard = getFBOGuard();
                auto tempDrawFbo = allocTempFramebuffer();
                auto tempDrawFboGuard = tempDrawFbo.get()->use(dst, GL_DRAW_FRAMEBUFFER);
                gl.glBindFramebufferProxy(GL_READ_FRAMEBUFFER, kfboGuard.drawFbo);
                gl.glBlitFramebuffer(
                    0, 0, dst->width, dst->height,
                    0, 0, dst->width, dst->height,
                    GL_COLOR_BUFFER_BIT, GL_NEAREST
                );
            }

            gsp<TextureInfo> ensureTexturePingPong(TextureInfo* texture) noexcept {
                if (!texture->pingPong) texture->pingPong = createTexture();
                copyTexture(texture, texture->pingPong.get());
                return texture->pingPong;
            }

            void renderIntoTexture(TextureInfo* texture, Mesh& descMesh) noexcept {
                auto vpGuard = getViewportGuard();
                auto pingPong = ensureTexturePingPong(texture);
                auto tempDrawFbo = allocTempFramebuffer();
                auto tempDrawFboGuard = tempDrawFbo.get()->use(texture, GL_DRAW_FRAMEBUFFER);
                auto feGuard = getFeatureGuard(GL_BLEND);

                setViewport(texture->width, texture->height);
                gl.glDisable(GL_BLEND);

                descMesh.vertices.reset();
                descMesh.addFullRect();
                descMesh.texture = pingPong.get();
                drawMesh(descMesh);
            }

            void gaussianBlurToTexture(TextureInfo* texture, float64 radius) {
                auto mesh = requestMesh(6);
                mesh.program = preloadedPrograms.gaussianBlur.get();

                auto progGuard = mesh.program->use();
                mesh.program->getUniformLocation("uIterations").seti(std::ceil(radius / (1.0 + 0.15 * std::log2(radius + 1))));

                mesh.program->getUniformLocation("uDelta").setv2({ 0.0, 1.0 });
                mesh.program->getUniformLocation("uRadius").setf(radius / texture->height);
                renderIntoTexture(texture, mesh);

                mesh.program->getUniformLocation("uDelta").setv2({ 1.0, 0.0 });
                mesh.program->getUniformLocation("uRadius").setf(radius / texture->width);
                renderIntoTexture(texture, mesh);
            }

            void renderToDrawFbo(uint64 width, uint64 height, Mesh& descMesh) {
                if (!defaultPingpong->isSameSize(width, height)) {
                    defaultPingpong->use().image2D(width, height, nullptr);
                }

                copyCurrentToTexture(defaultPingpong.get());
                auto feGuard = getFeatureGuard(GL_BLEND);

                setViewport(width, height);
                gl.glDisable(GL_BLEND);

                descMesh.vertices.reset();
                descMesh.addFullRect();
                descMesh.texture = defaultPingpong.get();
                drawMesh(descMesh);
            }

            bool getCurrentIsMultiSampled() noexcept {
                GLint samples = 0;
                gl.glGetIntegerv(GL_SAMPLES, &samples);
                return samples > 1;
            }

            struct {
                gsp<ProgramInfo> gaussianBlur;
                gsp<ProgramInfo> yuvConverter;
                gsp<ProgramInfo> circle;
            } preloadedPrograms;

            void frameEnded() noexcept {
                drawCallsCount = 0;
                frameSig++;
                vertexPool->reset();
            }

            Mesh requestMesh(uint64 verticesCount) noexcept {
                return {
                    .vertices = vertexPool->alloc(verticesCount)
                };
            }

            struct AsyncFrameReader {
                GL33Context* glCtx;
                uint64 frameWidth, frameHeight;

                AsyncFrameReader() = default;
                NO_COPY(AsyncFrameReader)
                AsyncFrameReader(AsyncFrameReader&& other) = default;
                AsyncFrameReader& operator=(AsyncFrameReader&& other) = default;

                void initBufferSlots(uint64 size) {
                    for (uint64 i = 0; i < size; i++) {
                        addBufferSlot();
                    }
                }

                struct ReadResult {
                    uint64 size;
                    uint64 frameIndex;

                    ReadResult() = default;
                    NO_COPY(ReadResult)
                    ReadResult(ReadResult&& other) = default;
                    ReadResult& operator=(ReadResult&& other) = default;

                    static gsp<ReadResult> Make(uint64 size, uint64 frameIndex) {
                        auto* result = new ReadResult();
                        result->size = size;
                        result->frameIndex = frameIndex;
                        return gsp<ReadResult>(result);
                    }

                    gsp<BufferInfo> pbo;

                    struct UsingGuard {
                        gsp<BufferInfo::UsingGuard> pboGuard;
                        gsp<BufferInfo::UsingGuard::MappingGuard> mapGuard;

                        UsingGuard(const gsp<BufferInfo>& pbo, GLsizei size)
                            : pboGuard(pbo->useSp())
                            , mapGuard(pboGuard->mapSp(0, size, GL_MAP_READ_BIT))
                        {}
                        
                        NO_COPY(UsingGuard)
                        UsingGuard(UsingGuard&& other) = default;
                        UsingGuard& operator=(UsingGuard&& other) = default;

                        uint8* data() const {
                            return (uint8*)mapGuard->data;
                        }
                    };

                    UsingGuard use() {
                        return UsingGuard(pbo, size);
                    }
                };

                void requestRead() {
                    flush();

                    for (auto& slot : bufferSlots) {
                        if (!slot.sync) {
                            readToSlot(slot);
                            return;
                        }
                    }

                    addBufferSlot();
                    readToSlot(bufferSlots.back());
                }

                using CallbackFunc = std::function<void(ReadResult&)>;
                CallbackFunc callback;

                void flush() {
                    for (auto& slot : bufferSlots) {
                        if (!slot.sync || !slot.sync->isSignaled()) continue;
                        slot.sync = nullptr;

                        auto result = ReadResult::Make(getBufferSize(), slot.frameIndex);
                        result->pbo = std::move(slot.buffer);
                        readResults.push_back(result);
                    }

                    emit();
                }

                void finish() {
                    glCtx->gl.glFinish();

                    for (auto& slot : bufferSlots) {
                        if (!slot.sync) continue;
                        slot.sync->wait(GL_SYNC_FLUSH_COMMANDS_BIT);
                        flush();
                    }
                }

                private:
                struct BufferSlot {
                    gsp<BufferInfo> buffer;
                    gsp<TextureInfo> texture;
                    gsp<SyncInfo> sync;
                    uint64 frameIndex;
                };

                std::vector<BufferSlot> bufferSlots;
                std::vector<gsp<BufferInfo>> pendingBuffers;
                std::vector<gsp<ReadResult>> readResults;
                uint64 currentFrameIndex;
                uint64 lastEmitFrameIndex;

                void addBufferSlot() {
                    if (frameWidth % 2 != 0 || frameHeight % 2 != 0) {
                        throw std::runtime_error("Frame size must be even");
                    }

                    auto& slot = bufferSlots.emplace_back();
                    slot.buffer = allocPbo();
                }

                void readToSlot(BufferSlot& slot) {
                    if (!slot.buffer) slot.buffer = allocPbo();

                    if (glCtx->getCurrentIsMultiSampled()) {
                        if (!slot.texture) {
                            slot.texture = glCtx->createTexture();
                            slot.texture->use().image2D(frameWidth, frameHeight, nullptr);
                        }

                        glCtx->copyCurrentToTexture(slot.texture.get());

                        auto tempDrawFbo = glCtx->allocTempFramebuffer();
                        auto drawFboGuard = tempDrawFbo.get()->use(slot.texture.get(), GL_DRAW_FRAMEBUFFER);
                        auto tempReadFbo = glCtx->allocTempFramebuffer();
                        auto readFboGuard = tempReadFbo.get()->use(slot.texture.get(), GL_READ_FRAMEBUFFER);

                        readToSlotDirect(slot);
                    } else {
                        readToSlotDirect(slot);
                    }
                }

                void readToSlotDirect(BufferSlot& slot) {
                    glCtx->convertToYUV(frameWidth, frameHeight, true);
                    auto pboGuard = slot.buffer->use();
                    glCtx->gl.glReadPixels(0, 0, frameWidth, getBufferHeight(), GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
                    slot.sync = glCtx->createSync();
                    slot.frameIndex = currentFrameIndex++;
                }

                void emit() {
                    while (readResults.size()) {
                        for (uint64 i = 0; i < readResults.size(); i++) {
                            auto& result = readResults[i];
                            if (result->frameIndex == 0 || result->frameIndex == lastEmitFrameIndex + 1) {
                                lastEmitFrameIndex = result->frameIndex;
                                callback(*result);
                                pendingBuffers.push_back(std::move(result->pbo));
                                readResults.erase(readResults.begin() + i);
                                break;
                            }
                        }
                    }
                }

                gsp<BufferInfo> allocPbo() {
                    if (pendingBuffers.empty()) {
                        auto pbo = glCtx->createBuffer(GL_PIXEL_PACK_BUFFER);
                        pbo->use().data(getBufferSize(), nullptr, GL_STREAM_READ);
                        return pbo;
                    }

                    auto ret = std::move(pendingBuffers.back());
                    pendingBuffers.pop_back();
                    return ret;
                }

                uint64 getBufferHeight() noexcept {
                    return (frameHeight * 3 + 7) / 8;
                }

                uint64 getBufferSize() noexcept {
                    return frameWidth * getBufferHeight() * 4;
                }
            };

            AsyncFrameReader createAsyncFrameReader(uint64 frameWidth, uint64 frameHeight) {
                AsyncFrameReader reader {};
                reader.glCtx = this;
                reader.frameWidth = frameWidth;
                reader.frameHeight = frameHeight;
                reader.initBufferSlots(4);
                return reader;
            }

            struct FBOGuard {
                GL33Context* glCtx;
                GLuint readFbo, drawFbo;

                FBOGuard(GL33Context* glCtx) : glCtx(glCtx) {
                    readFbo = glCtx->gl.localState.currentFramebuffers[GL_READ_FRAMEBUFFER];
                    drawFbo = glCtx->gl.localState.currentFramebuffers[GL_DRAW_FRAMEBUFFER];
                }

                NO_COPY(FBOGuard)
                NO_MOVE(FBOGuard)

                ~FBOGuard() {
                    glCtx->gl.glBindFramebufferProxy(GL_READ_FRAMEBUFFER, readFbo);
                    glCtx->gl.glBindFramebufferProxy(GL_DRAW_FRAMEBUFFER, drawFbo);
                }
            };

            FBOGuard getFBOGuard() noexcept {
                return FBOGuard(this);
            }

            gsp<FBOGuard> getFBOGuardSp() noexcept {
                auto* guard = new FBOGuard(this);
                return gsp<FBOGuard>(guard);
            }

            void convertToYUV(uint64 width, uint64 height, bool flipY = false) noexcept {
                auto mesh = requestMesh(6);
                mesh.program = preloadedPrograms.yuvConverter.get();
                mesh.color = GLvec4::White();

                auto progGuard = mesh.program->use();
                mesh.program->getUniformLocation("uResolution").seti(width, height);
                mesh.program->getUniformLocation("uFlipY").seti(flipY);
                renderToDrawFbo(width, height, mesh);
            }

            gsp<TextureInfo> createTextureFromDecoded(const DecodedRGBATexture& decoded, bool enableMipmap = false) {
                if (!decoded.valid()) throw std::runtime_error("invalid decoded texture");

                auto tex = createTexture();
                tex->use().image2D(decoded, enableMipmap);
                return tex;
            }

            struct TempFramebufferSlot {
                gsp<FramebufferInfo> fbo;
                bool isUsing;
            };

            private:
            std::vector<TempFramebufferSlot> tempFramebufferSlots;

            uint64 allocTempFramebufferIndex() noexcept {
                for (auto& slot : tempFramebufferSlots) {
                    if (!slot.isUsing) return &slot - &tempFramebufferSlots[0];
                }

                auto& slot = tempFramebufferSlots.emplace_back();
                slot.fbo = createFramebuffer();
                return &slot - &tempFramebufferSlots[0];
            }
            public:

            struct TempFramebufferGuard {
                GL33Context* glCtx;
                uint64 index;

                TempFramebufferGuard(GL33Context* glCtx, uint64 index) : glCtx(glCtx), index(index) {
                    glCtx->tempFramebufferSlots[index].isUsing = true;
                }

                NO_COPY(TempFramebufferGuard)
                NO_MOVE(TempFramebufferGuard)

                gsp<FramebufferInfo> get() { return glCtx->tempFramebufferSlots[index].fbo; }
                ~TempFramebufferGuard() { glCtx->tempFramebufferSlots[index].isUsing = false; }
            };

            TempFramebufferGuard allocTempFramebuffer() noexcept {
                return TempFramebufferGuard(this, allocTempFramebufferIndex());
            }

            gsp<TempFramebufferGuard> allocTempFramebufferSp() noexcept {
                auto* guard = new TempFramebufferGuard(this, allocTempFramebufferIndex());
                return gsp<TempFramebufferGuard>(guard);
            }

            private:
            gsp<ProgramInfo> defaultProgram;
            gsp<TextureInfo> defaultWhiteTexture;
            gsp<VertexPool> vertexPool;
            gsp<TextureInfo> defaultPingpong;
            bool resourcesInitialized = false;
            GLvec4 currentViewport;
            uint64 frameSig;

            void initDefaultResources() {
                if (resourcesInitialized) return;
                resourcesInitialized = true;
            
                defaultProgram = createConfiguredProgram(CreateProgramConfig { }.defaultColorVert().defaultColorFrag());
                preloadedPrograms.gaussianBlur = ProgramPresets::gaussianBlur(this);
                preloadedPrograms.yuvConverter = ProgramPresets::yuvConverter(this);
                preloadedPrograms.circle = ProgramPresets::circle(this);

                unsigned char whiteTextureData[16] = {
                    255, 255, 255, 255,
                    255, 255, 255, 255,
                    255, 255, 255, 255,
                    255, 255, 255, 255
                };

                defaultWhiteTexture = createTexture();
                defaultWhiteTexture->use().image2D(
                    2, 2,
                    (void*)(&whiteTextureData[0])
                );

                defaultPingpong = createTexture();

                gl.glEnable(GL_BLEND);
                gl.glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                vertexPool = VertexPool::Make();
            }
        };

        struct GL33Canvas {
            Transform2D transform;
            GL33Context* glCtx;

            static GL33Canvas Make(GL33Context* glCtx) {
                GL33Canvas canvas {};
                canvas.glCtx  = glCtx;
                return canvas;
            }

            GLvec2 toNDC(const GLvec2& pos) noexcept {
                auto vp = glCtx->getViewport();
                return {
                    (pos.x - vp.x) / vp.z * 2.0 - 1.0,
                    -((pos.y - vp.y) / vp.w * 2.0 - 1.0)
                };
            }

            GLvec2 transformPoint(const GLvec2& pos) noexcept {
                auto p = transform.transformPoint(pos.x, pos.y);
                return { p.x, p.y };
            }

            void normVertices(VertexPool::AllocResult& vertices) noexcept {
                for (auto& v : vertices) {
                    v.position = toNDC(transformPoint(v.position));
                }
            }

            void resetTransform() noexcept { transform = Transform2D(); }
            void translate(float64 x, float64 y) noexcept { transform.translate(x, y); }
            void translate(const GLvec2& pos) noexcept { transform.translate(pos.x, pos.y); }
            void scale(float64 x, float64 y) noexcept { transform.scale(x, y); }
            void scale(const GLvec2& scale) noexcept { transform.scale(scale.x, scale.y); }
            void rotate(float64 angle) noexcept { transform.rotate(angle); }
            void rotateDegrees(float64 angle) noexcept { rotate(angle / 180.0 * std::numbers::pi); }

            void save() noexcept { transformHistory.push_back(transform); }
            void restore() noexcept { transform = transformHistory.back(); transformHistory.pop_back(); }

            void drawMesh(Mesh& mesh) noexcept {
                normVertices(mesh.vertices);
                glCtx->drawMesh(mesh);
            }

            struct DrawRectConfig {
                GLvec2 position, size;
                GLvec4 color = { 1.0, 1.0, 1.0, 1.0 };
                GLvec2 uvPosition = { 0.0, 0.0 };
                GLvec2 uvSize = { 1.0, 1.0 };
                TextureInfo* texture;
            };

            void drawRect(const DrawRectConfig& config) noexcept {
                auto mesh = glCtx->requestMesh(6);
                mesh.color = config.color;
                mesh.texture = config.texture;
                mesh.addRect(config.position, config.size, config.uvPosition, config.uvSize);
                drawMesh(mesh);
            }

            private:
            std::vector<Transform2D> transformHistory;
        };

        struct VideoRecorder {
            VideoRecorder() = default;
            NO_COPY(VideoRecorder)
            NO_MOVE(VideoRecorder)

            using CallbackFunc = std::function<void(uint64)>;
            
            struct Config {
                uint64 nominalSize = 1920 * 1080 * 16;
                bool callbackIsThreadSafe = false;
                uint64 msaaSamples = 4;
            };

            static gsp<VideoRecorder> Make(
                const gsp<GL33Context>& glCtx,
                uint64 width, uint64 height,
                const CallbackFunc& callback,
                const Config& config
            ) {
                auto* recorder = new VideoRecorder();

                recorder->glCtx = glCtx;
                recorder->asyncFrameReader = glCtx->createAsyncFrameReader(width, height);
                recorder->asyncFrameReader.callback = [=](GL33Context::AsyncFrameReader::ReadResult& result) {
                    recorder->ensureCallbackIsDone();
                    auto slotIndex = recorder->allocYUVFrameSlot();
                    auto& slot = recorder->yuvFrameSlots[slotIndex];
                    slot.frame->fromPtr(result.use().data());

                    if (!config.callbackIsThreadSafe) {
                        recorder->callback(slotIndex);
                    } else {
                        recorder->callbackThread = std::thread([=]() {
                            recorder->callback(slotIndex);
                        });
                    }
                };

                recorder->callback = callback;

                auto surfacesCount = std::clamp<uint64>(
                    config.nominalSize / (width * height),
                    1, 512
                );

                for (uint64 i = 0; i < surfacesCount; i++) {
                    if (config.msaaSamples > 1) {
                        auto surface = glCtx->createTexture(GL_TEXTURE_2D_MULTISAMPLE);
                        surface->use().image2DMultisample(width, height, config.msaaSamples);
                        recorder->surfaces.push_back(surface);
                    } else {
                        auto surface = glCtx->createTexture(GL_TEXTURE_2D);
                        surface->use().image2D(width, height, nullptr);
                        recorder->surfaces.push_back(surface);
                    }
                }

                recorder->maxConcurrentYuvSlots = std::clamp<uint64>(
                    config.nominalSize / (width * height) * 4,
                    1, 4096
                );

                return gsp<VideoRecorder>(recorder);
            }

            struct FrameUsingGuard {
                VideoRecorder* ref;

                FrameUsingGuard(VideoRecorder& recorder) : ref(&recorder) {
                    auto& surface = ref->surfaces[ref->currentSurfaceIndex];
                    ref->currentSurfaceIndex = (ref->currentSurfaceIndex + 1) % ref->surfaces.size();

                    tempDrawFbo = ref->glCtx->allocTempFramebufferSp();
                    drawFboGuard = tempDrawFbo->get()->useSp(surface.get(), GL_DRAW_FRAMEBUFFER);
                    tempReadFbo = ref->glCtx->allocTempFramebufferSp();
                    readFboGuard = tempReadFbo->get()->useSp(surface.get(), GL_READ_FRAMEBUFFER);
                }

                NO_COPY(FrameUsingGuard)
                NO_MOVE(FrameUsingGuard)

                ~FrameUsingGuard() {
                    ref->asyncFrameReader.requestRead();
                }

                private:
                gsp<GL33Context::TempFramebufferGuard> tempDrawFbo;
                gsp<FramebufferInfo::UsingGuard> drawFboGuard;
                gsp<GL33Context::TempFramebufferGuard> tempReadFbo;
                gsp<FramebufferInfo::UsingGuard> readFboGuard;
            };

            FrameUsingGuard useFrame() noexcept {
                return FrameUsingGuard(*this);
            }

            gyuv420frame::YUV420Frame* referYUVFrame(uint64 index) noexcept {
                std::lock_guard<std::mutex> guard(yuvFrameSlotsMutex);
                return yuvFrameSlots[index].frame.get();
            }

            void returnYUVFrame(uint64 index) noexcept {
                std::lock_guard<std::mutex> guard(yuvFrameSlotsMutex);
                yuvFrameSlots[index].isUsing = false;
            }

            void finish() {
                asyncFrameReader.finish();
                ensureCallbackIsDone();
            }

            ~VideoRecorder() {
                finish();
            }

            private:
            gsp<GL33Context> glCtx;
            GL33Context::AsyncFrameReader asyncFrameReader;
            CallbackFunc callback;
            uint64 maxConcurrentYuvSlots;

            std::vector<gsp<TextureInfo>> surfaces;
            uint64 currentSurfaceIndex = 0;

            struct YUVFrameSlot {
                gsp<gyuv420frame::YUV420Frame> frame;
                bool isUsing;
            };

            std::vector<YUVFrameSlot> yuvFrameSlots;
            std::mutex yuvFrameSlotsMutex;
            std::thread callbackThread;

            void ensureCallbackIsDone() noexcept {
                if (callbackThread.joinable()) callbackThread.join();
            }

            uint64 allocYUVFrameSlot() {
                while (getYUVFrameSlotsInUse() > maxConcurrentYuvSlots) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                }

                std::lock_guard<std::mutex> guard(yuvFrameSlotsMutex);

                for (uint64 i = 0; i < yuvFrameSlots.size(); i++) {
                    auto& slot = yuvFrameSlots[i];
                    if (!slot.isUsing) {
                        slot.isUsing = true;
                        return i;
                    }
                }

                auto& slot = yuvFrameSlots.emplace_back();
                slot.frame = gyuv420frame::YUV420Frame::Make(asyncFrameReader.frameWidth, asyncFrameReader.frameHeight);
                slot.isUsing = true;
                return yuvFrameSlots.size() - 1;
            }

            uint64 getYUVFrameSlotsInUse() noexcept {
                std::lock_guard<std::mutex> guard(yuvFrameSlotsMutex);
                return std::count_if(yuvFrameSlots.begin(), yuvFrameSlots.end(), [](const auto& slot) {
                    return slot.isUsing;
                });
            }
        };

        struct TextManager {
            static constexpr uint64 maxCacheSize = 128;

            using Renderer = std::function<DecodedRGBATexture(const std::string&, uint64)>;
            Renderer renderer;
            gsp<GL33Context> glCtx;

            void check() {
                gassert::assert(!!renderer, "TextManager: renderer is not set");
                gassert::assert(!!glCtx, "TextManager: glCtx is not set");
            }

            struct GetTextureResult {
                TextureInfo* texture;
                float64 scale;

                GLvec2 size() const noexcept {
                    return texture->size() * scale;
                }
            };

            bool getTexture(
                const std::string& text, float64 fontSize,
                GetTextureResult& result
            ) {
                if (fontSize <= 0.0) return false;

                uint64 isize = std::ceil(fontSize / 48) * 48;
                result.scale = fontSize / isize;
                auto key = std::make_pair(text, isize);

                {
                    auto it = cache.find(key);
                    if (it != cache.end()) {
                        result.texture = it->second.get();
                        return true;
                    }
                }

                if (cache.size() >= maxCacheSize) {
                    static std::mt19937 rng { std::random_device {} () };
                    std::uniform_int_distribution<uint64> dist { 0, cache.size() - 1 };
                    auto it = cache.begin();
                    std::advance(it, dist(rng));
                    cache.erase(it);
                }

                auto decoded = renderer(text, isize);
                if (!decoded.valid()) throw std::runtime_error("texture is invalid");

                auto tex = glCtx->createTexture();
                tex->use().image2D(decoded);
                cache[key] = tex;

                result.texture = tex.get();
                return true;
            }

            struct DrawTextConfig {
                std::string text;
                float64 fontSize;
                GLvec2 pos, anchor;
                float64 rotation;
                GLvec2 scale;
                GLvec4 color;

                void normScale() noexcept {
                    auto wScale = std::min<float64>(std::max(scale.x, scale.y), 16.0);

                    if (wScale > 1.0) {
                        scale /= wScale;
                        fontSize *= wScale;
                    }
                }
            };

            void drawText(GL33Canvas& cvs, DrawTextConfig& config) {
                config.normScale();

                static GetTextureResult textureResult;
                if (!getTexture(config.text, config.fontSize, textureResult)) return;

                auto size = textureResult.size() * config.scale;

                cvs.save();
                cvs.translate(config.pos);
                cvs.rotateDegrees(config.rotation);
                cvs.drawRect({
                    .position = -size * config.anchor,
                    .size = size,
                    .color = config.color,
                    .texture = textureResult.texture
                });
                cvs.restore();
            }

            private:
            std::map<std::pair<std::string, uint64>, gsp<TextureInfo>> cache;
        };
    }

    #undef NO_COPY
    #undef NO_MOVE
}
