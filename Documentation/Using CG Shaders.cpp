//////////////////////
// Using CG Shaders //
// ---------------- //
//////////////////////

// Note: I use the term 'pixel shader,' while CG uses 'fragment shader'.

////////////////////////////
// Includes and Libraries //
// ---------------------- //
////////////////////////////

// General Cg include
#include <Cg/cg.h>
// OpenGL Cg include
#include <Cg/cgGL.h>
// DirectX 9 Cg include
#include <Cg/cgD3D9.h>
// DirectX 8 Cg include
#include <Cg/cgD3D8.h>
// General Cg library
cg.lib/so
// OpenGL Cg library
cgGL.lib/so
// DirectX 9 Cg library
cgD3D9.lib/so
// DirectX 8 Cg library
cgD3D8.lib/so

/////////////////////////////////////
// Initializing and Setting Up CG: //
// ------------------------------- //
/////////////////////////////////////

// 1. (DirectX Only) Declare and create the Direct3D variables (device,
//      main thing (direct3D variable), parameters, and vertex declaration).
    LPDIRECT3D9 direct3D = null ;
    LPDIRECT3DDEVICE9 direct3DDevice = null ;
    LPDIRECT3DVERTEXDECLARATION9 direct3DVertexDeclaration = null ; 
    //create and set the Direct3D parameters
    D3DPRESENT_PARAMETERS d3dpp ;
    d3dpp.Windowed = ... ;
    d3dpp.SwapEffect = ... ;
    direct3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                          &d3dpp, &direct3DDevice );

// 2. Declare a CGcontext for the CG shaders.
    CGcontext cgContext ;
    
// 3. Declare a CGprogram and CGprofile for each shader, both vertex and pixel.
    CGprogram vertexShaderProgram ;
    CGprofile vertexShaderProfile ;
    CGprogram pixelShaderProgram ;
    CGprofile pixelShaderProfile ;
    
// 4. Declare CGparameter objects for the parameters used in the shader programs that you want to modify.
    CGparameter rockTexture;
    CGparameter normalTexture;
    CGparameter modelViewMatrix;
    CGparameter lightPosition;
    CGparameter lightDiffuseColor;
    
// 5. Set the error callback function for CG.
    void cgErrorCallback ()
    {
        std::cout << cgGetErrorString ( cgGetError (), cgGetLastListing ( cgContext ) ) << "\n" ;
    }
    
    ...
    
    cgSetErrorCallback ( cgErrorCallback ) ;
    
// 6. Create the CGcontext object.
    cgContext = cgCreateContext () ;
    
// 7. (DirectX Only) Set the Direct3D device. (Only when using CG's expanded interface.)
    cgD3D9SetDevice( direct3DDevice );

// 8. Create the appropriate CGprofile objects.
    // OpenGL version
    vertexShaderProfile = cgGLGetLatestProfile ( CG_GL_VERTEX ) ;
    pixelShaderProfile = cgGLGetLatestProfile ( CG_GL_FRAGMENT ) ;
    cgGLSetOptimalOptions ( vertexShaderProfile ) ;
    cgGLSetOptimalOptions ( pixelShaderProfile ) ;
    // Make sure the profiles aren't bad
    if ( vertexShaderProfile == CG_PROFILE_UNKNOWN )
    {
        std::cout << "Bad vertex shader profile!\n" ;
    }
    if ( pixelShaderProfile == CG_PROFILE_UNKNOWN )
    {
        std::cout << "Bad pixel shader profile!\n" ;
    }
    
    // DirectX (9.0) version
    vertexShaderProfile = cgD3D9GetLatestPixelProfile () ;
    pixelShaderProfile = cgD3D9GetLatestVertexProfile () ;
    const char* vertexShaderOptions = cgD3D9GetOptimalOptions ( vertexShaderProfile ) ;
    const char* pixelShaderOptions = cgD3D9GetOptimalOptions ( pixelShaderProfile ) ;
    // Make sure the profiles aren't bad
    if ( vertexShaderProfile == CG_PROFILE_UNKNOWN )
    {
        std::cout << "Bad vertex shader profile!\n" ;
    }
    if ( pixelShaderProfile == CG_PROFILE_UNKNOWN )
    {
        std::cout << "Bad pixel shader profile!\n" ;
    }

// 9. Create and load the shader programs.
    // OpenGL version
    vertexShaderProgram = cgCreateProgramFromFile ( cgContext, CG_SOURCE, "vertexShaderProgram.cg", vertexShaderProfile, "main", 0 ) ;
    if ( !vertexShaderProgram )
    {
        return ;
    }
    cgGLLoadProgram ( vertexShaderProgram ) ;
    pixelShaderProgram = cgCreateProgramFromFile ( cgContext, CG_SOURCE, "pixelShaderProgram.cg", pixelShaderProfile, "main", 0 ) ;
    if ( !pixelShaderProgram )
    {
        return ;
    }
    cgGLLoadProgram ( pixelShaderProgram ) ;
    
    // DirectX (9.0) version
    bool useParameterShadowing = false ;    // dummy value
    int directXShaderAssemblyFlags = 0 ;    // dummy value
    vertexShaderProgram = cgCreateProgramFromFile ( cgContext, CG_SOURCE, "vertexShaderProgram.cg", vertexShaderProfile, "main", vertexShaderOptions ) ;
    if ( !vertexShaderProgram )
    {
        return ;
    }
    if ( cgD3D9LoadProgram ( vertexShaderProgram, useParameterShadowing, directXShaderAssemblyFlags ) != D3D_OK )
    {
        std::cout << "Failed to load vertexShaderProgram into DirectX.\n" ;
    }
    pixelShaderProgram = cgCreateProgramFromFile ( cgContext, CG_SOURCE, "pixelShaderProgram.cg", pixelShaderProfile, "main", pixelShaderOptions ) ;
    if ( !pixelShaderProgram )
    {
        return ;
    }
    if ( cgD3D9LoadProgram ( pixelShaderProgram, useParameterShadowing, directXShaderAssemblyFlags ) != D3D_OK )
    {
        std::cout << "Failed to load pixelShaderProgram into DirectX.\n" ;
    }

// 10. (DirectX Only) Create, set, and validate a vertex declaration
//  in the situation that the shader program uses explicit binding semantics
    CGparameter position = cgGetNamedParameter( g_CGprogram, "IN.position");
	CGparameter color    = cgGetNamedParameter( g_CGprogram, "IN.color0");
    
    // This declaration gets the information from the arguments themselves (last two parameters)
	const D3DVERTEXELEMENT9 declaration [] =
	{
		{ 0, 0 * sizeof ( float ), D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, 
		cgD3D9ResourceToDeclUsage ( cgGetParameterResource ( position ) ),
		static_cast<BYTE> ( cgGetParameterResourceIndex ( position ) ) },

		{ 0, 3 * sizeof ( float ), D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, 
		cgD3D9ResourceToDeclUsage ( cgGetParameterResource ( color ) ),
		static_cast<BYTE> ( cgGetParameterResourceIndex ( color ) ) },

		D3DDECL_END (),
	} ;

	cgD3D9ValidateVertexDeclaration ( vertexShaderProgram, declaration ) ;

	direct3DDevice->CreateVertexDeclaration ( declaration, &direct3DVertexDeclaration ) ;

// 11. Bind the desired shader parameters to parameters of the shader program
    modelViewMatrix = cgGetNamedParameter ( vertexShaderProgram, "modelViewProjMatrix" ) ;
	lightPosition = cgGetNamedParameter ( vertexShaderProgram, "vLightPosition" ) ;
	lightDiffuseColor = cgGetNamedParameter ( pixelShaderProgram, "fLightDiffuseColor" ) ;


///////////////////////////////
// Using CG Shaders In Code: //
// ------------------------- //
///////////////////////////////

// 1. Enable the shaders' profiles and bind the shader programs.
    // OpenGL version
    cgGLEnableProfile ( vertexShaderProfile ) ;
    cgGLEnableProfile ( pixelShaderProfile ) ;
        
    cgGLBindProgram ( vertexShaderProgram ) ;
    cgGLBindProgram ( pixelShaderProgram ) ;
    
    // DirectX (9.0) version
    direct3DDevice->SetVertexDeclaration ( direct3DVertexDeclaration ) ;
    if ( cgD3D9BindProgram( vertexShaderProgram ) != D3D_OK )
    {
        std::cout << "Could not bind vertexShaderProgram!\n" ;
    }
    if ( cgD3D9BindProgram( pixelShaderProgram ) != D3D_OK )
    {
        std::cout << "Could not bind vertexShaderProgram!\n" ;
    }
    
// 2. Set the shader program parameters.
//      Note that there are many types of parameters, and
//      each type that is supported has corresponding
//      get/set functions (see the API for more info).
    // OpenGL version
    cgGLSetStateMatrixParameter ( modelViewMatrix, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY ) ;
	cgGLSetParameter3f ( lightPosition, 0.0f, 20.0f, 0.0f ) ;
	cgGLSetParameter3f ( lightDiffuseColor, 1.0f, 1.0f, 1.0f ) ;
    
    // DirectX (9.0) version
    // TO BE WRITTEN IN THE FUTURE

// 3. Render your scene.
    OpenGL/DirectX calls... la la la...    

// 4. (OpenGL Only) Disable the shaders' profiles.
    cgGLDisableProfile ( vertexShaderProfile ) ;
    cgGLDisableProfile ( pixelShaderProfile ) ;


/////////////////////
// Cleaning Up CG: //
// --------------- //
/////////////////////

// 1. (DirectX Only) Set the device to null.
    cgD3D9SetDevice ( null ) ;

// 2. Destroy the CG programs and contexts.
    cgDestroyProgram ( vertexShaderProgram ) ;
    cgDestroyProgram ( pixelShaderProgram ) ;
    cgDestroyContext ( cgContext ) ;
