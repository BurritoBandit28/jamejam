//
// Created by burrito on 07/04/2026.
//
#define SDL_MAIN_HANDLED


#include <iostream>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include "resource_location.h"
#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#ifdef _WIN32
    #include <windows.h>
    #include <GL/glu.h>
#else
    #    #include <GL/glu.h>
#endif


GLuint gProgramID = 0;
GLint gVertexPos2DLocation = -1;
GLuint gVBO = 0;
GLuint gIBO = 0;

static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_AudioStream *stream = NULL;
static Uint8 *wav_data = NULL;
static Uint32 wav_data_len = 0;

static int height = 480;
static int width = 640;

void printProgramLog( GLuint program )
{
    //Make sure name is shader
    if( glIsProgram( program ) )
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a program\n", program );
    }
}

void printShaderLog( GLuint shader )
{
    //Make sure name is shader
    if( glIsShader( shader ) )
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        //Get info string length
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );

        //Allocate string
        char* infoLog = new char[ maxLength ];

        //Get info log
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a shader\n", shader );
    }
}

bool initGL()
{
	//Success flag
	bool success = true;

	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER );

	//Get vertex source
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource( vertexShader, 1, vertexShaderSource, NULL );

	//Compile vertex source
	glCompileShader( vertexShader );

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &vShaderCompiled );
	if( vShaderCompiled != GL_TRUE )
	{
		SDL_Log( "Unable to compile vertex shader %d!\n", vertexShader );
		printShaderLog( vertexShader );
        success = false;
	}
	else
	{
		//Attach vertex shader to program
		glAttachShader( gProgramID, vertexShader );


		//Create fragment shader
		GLuint fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );

		//Get fragment source
		const GLchar* fragmentShaderSource[] =
		{
			"#version 140\nin vec4 gl_FragCoord; out vec4 LFragment; uniform vec2 WindowSize;void main() { LFragment = vec4(  gl_FragCoord.y/WindowSize.y,gl_FragCoord.x/WindowSize.x, 0, 1.0 ); }"
		};

		//Set fragment source
		glShaderSource( fragmentShader, 1, fragmentShaderSource, NULL );

		//Compile fragment source
		glCompileShader( fragmentShader );

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled );
		if( fShaderCompiled != GL_TRUE )
		{
			SDL_Log( "Unable to compile fragment shader %d!\n", fragmentShader );
			printShaderLog( fragmentShader );
			success = false;
		}
		else
		{
			//Attach fragment shader to program
			glAttachShader( gProgramID, fragmentShader );


			//Link program
			glLinkProgram( gProgramID );

			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv( gProgramID, GL_LINK_STATUS, &programSuccess );
			if( programSuccess != GL_TRUE )
			{
				SDL_Log( "Error linking program %d!\n", gProgramID );
				printProgramLog( gProgramID );
				success = false;
			}
			else
			{
				//Get vertex attribute location
				gVertexPos2DLocation = glGetAttribLocation( gProgramID, "LVertexPos2D" );
				if( gVertexPos2DLocation == -1 )
				{
					SDL_Log( "LVertexPos2D is not a valid glsl program variable!\n" );
					success = false;
				}
				else
				{
					//Initialize clear color
					glClearColor( 0.f, 0.f, 0.f, 1.f );

					//VBO data
					GLfloat vertexData[] =
					{
						-1.0f, -1.0f,
						 1.0f, -1.0f,
						 1.0f,  1.0f,
						-1.0f,  1.0f
					};

					//IBO data
					GLuint indexData[] = { 0, 1, 2, 3 };

					//Create VBO
					glGenBuffers( 1, &gVBO );
					glBindBuffer( GL_ARRAY_BUFFER, gVBO );
					glBufferData( GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW );

					//Create IBO
					glGenBuffers( 1, &gIBO );
					glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
					glBufferData( GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW );
				}
			}
		}
	}

	return success;
}

void render()
{
	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );

	//Render quad

	{
		//Bind program
		glUseProgram( gProgramID );

		//Enable vertex position
		glEnableVertexAttribArray( gVertexPos2DLocation );

		//Set vertex data
		glBindBuffer( GL_ARRAY_BUFFER, gVBO );
		glVertexAttribPointer( gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL );

		//Set index data and render
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, gIBO );
		glDrawElements( GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL );

		//Disable vertex position
		//glDisableVertexAttribArray( gVertexPos2DLocation );

		//Unbind program
		glUseProgram( 0 );
	}
}

int loadSDL() {

    // GL stuff
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );


    // basic sdl setup
    SDL_AudioSpec spec;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) {
        printf("SDL_Init failed: %s\n", SDL_GetError());
    }

    if (!SDL_CreateWindowAndRenderer("Game Window (WIP TEST BUILD)", 640, 480, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!window) {
        printf("Window failed to be created: %s\n", SDL_GetError());
    }

    // in future a dedicated audio manager will be made, this is for a test
    if (!SDL_LoadWAV("./assets/base/sound/music/menu.wav", &spec, &wav_data, &wav_data_len)) {
        SDL_Log("Couldn't load .wav file: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, NULL, NULL);
    if (!stream) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    SDL_ResumeAudioStreamDevice(stream);


    //Create context
    SDL_GLContext gContext = SDL_GL_CreateContext( window );
    if( gContext == NULL )
    {
        printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
        return SDL_APP_FAILURE;
    }
    //Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if( glewError != GLEW_OK )
    {
        printf( "Error initializing GLEW! %s\n", glewGetErrorString( glewError ) );
    }

    //Use Vsync
    if( SDL_GL_SetSwapInterval( 1 ) < 0 )
    {
        printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
    }

    //Initialize OpenGL
    if( !initGL() )
    {
        printf( "Unable to initialize OpenGL!\n" );
        return SDL_APP_FAILURE;
    }

    bool running = true;
	bool pause = false;
	int uniform_WindowSize = glGetUniformLocation(gProgramID,"WindowSize");
	glUseProgram(gProgramID);
	glUniform2f(uniform_WindowSize, width, height);
    SDL_Event e;
    render();
    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT || (e.type == SDL_EVENT_KEY_DOWN && e.key.scancode == SDL_SCANCODE_ESCAPE)) {
                running = false;
            }
        	if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
        		pause =! pause;
        		if (pause) {
        			SDL_PauseAudioStreamDevice(stream);
        		}
        		else {
        			SDL_ResumeAudioStreamDevice(stream);
        		}
        	}
        	if (e.type == SDL_EVENT_WINDOW_RESIZED) {
        		SDL_GetWindowSizeInPixels(window,&width,&height);
        		glUseProgram(gProgramID);
        		glUniform2f(uniform_WindowSize, width, height);
        		glViewport(0, 0, width, height);
        	}
        }

        if (SDL_GetAudioStreamQueued(stream) < (int)wav_data_len) {
            /* feed more data to the stream. It will queue at the end, and trickle out as the hardware needs more data. */
            SDL_PutAudioStreamData(stream, wav_data, wav_data_len);
        }
    	//Render quad
    	render();


    	//Update screen
    	SDL_GL_SwapWindow( window );
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    SDL_free(wav_data);
    return SDL_APP_SUCCESS;
}



int main() {
    ResourceLocation rl1 = ResourceLocation("base", "test");
    ResourceLocation rl2 = ResourceLocation::empty();
    rl2.parse("base:music/menu");

    std::cout << rl1.toString() << " " << rl2.toString() << std::endl;

   return loadSDL();
}


