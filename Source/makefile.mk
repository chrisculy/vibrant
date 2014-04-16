# ======================= Variables ======================= #

# Note: The user should set the make variable PLATFORM to one of the following:
# 
#	WINDOWS
#	MAC
#	LINUX

PLATFORM=WINDOWS

# Windows Specific Variables.
vibrant_ld_libs_WINDOWS=-lws2_32 $(libraries_WINDOWS)
vopengl_ld_libs_WINDOWS=-lopengl32 -lglu32 $(libraries_WINDOWS)
vtestapp_ld_libs_WINDOWS=-lopengl32 -lglu32 $(libraries_WINDOWS)
vibrant_output_dir_WINDOWS=vibrant_win_debug
vopengl_output_dir_WINDOWS=vopengl_win_debug
vtestapp_output_dir_WINDOWS=vtestapp_win_debug
libraries_WINDOWS=-lkernel32 -lgdi32
# -luser32 -lwinspool -lcomdlg32 \
# -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lodbccp32

# Linux Specific Variables.
vibrant_ld_libs_LINUX=
vopengl_ld_libs_LINUX=
vtestapp_ld_libs_LINUX=
vibrant_output_dir_LINUX=vibrant_lin_debug
vopengl_output_dir_LINUX=vopengl_lin_debug
vtestapp_output_dir_LINUX=vtestapp_lin_debug

# Mac Specific Variables.
vibrant_ld_libs_MAC=
vopengl_ld_libs_MAC=
vtestapp_ld_libs_MAC=
vibrant_output_dir_MAC=vibrant_mac_debug
vopengl_output_dir_MAC=vopengl_mac_debug
vtestapp_output_dir_MAC=vtestapp_mac_debug

# General Configuration Variables.
CXX=g++
CXXFLAGS=-Wall -g -c
LDFLAGS=
MKDIR=mkdir
link_to_vibrant_flags= -L./ -lVibrant

# ------------------------ Vibrant ------------------------ #
vibrant_sources=
include vibrant_dll_files.mk
vibrant_output_dir=$(vibrant_output_dir_${PLATFORM})
vibrant_objects=$(foreach obj,$(vibrant_sources:.cpp=.o),$(vibrant_output_dir)/$(obj))
vibrant_precompiled_header=$(vibrant_output_dir)/vprecompiled.gch
vibrant_library=Vibrant.dll
vibrant_cxxflags=-DDLL_BUILD
vibrant_ldflags=-shared -Wl,--out-implib,libVibrant.a
vibrant_ld_libs=$(vibrant_ld_libs_${PLATFORM})
# ------------------------ Vibrant ------------------------ #

# ----------------- Vibrant OpenGL Module ----------------- #
vopengl_sources=
include vopengl_dll_files.mk
vopengl_output_dir=$(vopengl_output_dir_${PLATFORM})
vopengl_objects=$(foreach obj,$(vopengl_sources:.cpp=.o),$(vopengl_output_dir)/$(obj))
vopengl_precompiled_header=$(vopengl_output_dir)/vprecompiled_opengl.gch
vopengl_library=VOpenGL.dll
vopengl_cxxflags=-DDLL_BUILD -ID:/Programming/alterr/Vibrant/Include
vopengl_ldflags=-shared -Wl,--out-implib,libVOpenGL.a
vopengl_ld_libs=$(vopengl_ld_libs_${PLATFORM}) $(link_to_vibrant_flags)
# ----------------- Vibrant OpenGL Module ----------------- #

# --------------- Vibrant Test Application ---------------- #
vtestapp_sources=
include vtestapp_files.mk
vtestapp_output_dir=$(vtestapp_output_dir_${PLATFORM})
vtestapp_objects=$(foreach obj,$(vtestapp_sources:.cpp=.o),$(vtestapp_output_dir)/$(obj))
vtestapp_executable=VTestApp.exe
vtestapp_cxxflags=
vtestapp_ldflags=
vtestapp_ld_libs=$(vtestapp_ld_libs_${PLATFORM}) $(link_to_vibrant_flags)
# --------------- Vibrant Test Application ---------------- #

# ======================= Variables ======================= #


# ======================== Targets ======================== #
all: vibrant vopengl vconfig vtestapp


# ------------------------ Vibrant ------------------------ #
# Compile the main Vibrant DLL.
vibrant: $(vibrant_output_dir) $(vibrant_library) makefile.mk

# Create the output directory if needed.
$(vibrant_output_dir):
	$(MKDIR) $(vibrant_output_dir)

# Link the object files into the library.
$(vibrant_library): $(vibrant_precompiled_header) $(vibrant_objects)
	$(CXX) $(LDFLAGS) $(vibrant_ldflags) $(vibrant_objects) -o $@ $(vibrant_ld_libs)

# Compile the source code into object files.
$(vibrant_output_dir)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(vibrant_cxxflags) -o $(vibrant_output_dir)/$*.o $<

# Compile the precompiled header.
$(vibrant_precompiled_header): $(notdir $(vibrant_precompiled_header:.gch=.h))
	$(CXX) $(CXXFLAGS) $(vibrant_cxxflags) -o $@ $<

# Clean the project.
vibrant_clean:
	$(RM) *.dll && cd $(vibrant_output_dir) && $(RM) *.o
# ------------------------ Vibrant ------------------------ #


# ----------------- Vibrant OpenGL Module ----------------- #
# Compile the VOpenGL DLL.
vopengl: $(vopengl_output_dir) $(vopengl_library) vibrant makefile.mk

# Create the output directory if needed.
$(vopengl_output_dir):
	$(MKDIR) $(vopengl_output_dir)

# Link the object files into the library.
$(vopengl_library): $(vopengl_precompiled_header) $(vopengl_objects)
	$(CXX) $(LDFLAGS) $(vopengl_ldflags) $(vopengl_objects) -o $@ $(vopengl_ld_libs)

# Compile the source code into object files.
$(vopengl_output_dir)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(vopengl_cxxflags) -o $(vopengl_output_dir)/$*.o $<

# Compile the precompiled header.
$(vopengl_precompiled_header): $(notdir $(vopengl_precompiled_header:.gch=.h))
	$(CXX) $(CXXFLAGS) $(vopengl_cxxflags) -o $@ $<

# Clean the project.
vopengl_clean:
	$(RM) *.dll && $(RM) *.a && cd $(vopengl_output_dir) && $(RM) *.o
# ----------------- Vibrant OpenGL Module ----------------- #


# -------------- Vibrant Configuration Tool --------------- #
vconfig: vibrantconfig.o vibrant
	$(CXX) $(LDFLAGS) -o $@ $< $(link_to_vibrant_flags)

vibrantconfig.o: vibrantconfig.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

vconfig_clean:
	$(RM) vconfig.exe
# -------------- Vibrant Configuration Tool --------------- #


# --------------- Vibrant Test Application ---------------- #
# Compile the VTestApp executable.
vtestapp: vibrant vopengl makefile.mk $(vtestapp_output_dir) $(vtestapp_executable) 

# Create the output directory if needed.
$(vtestapp_output_dir):
	$(MKDIR) $(vtestapp_output_dir)

# Link the object files into the library.
$(vtestapp_executable): $(vtestapp_objects)
	$(CXX) $(LDFLAGS) $(vtestapp_ldflags) $(vtestapp_objects) -o $@ $(vtestapp_ld_libs)

# Compile the source code into object files.
$(vtestapp_output_dir)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(vtestapp_cxxflags) -o $(vtestapp_output_dir)/$*.o $<

# Clean the project.
vtestapp_clean:
	$(RM) $(vtestapp_executable)
# --------------- Vibrant Test Application ---------------- #

clean: vibrant_clean vopengl_clean vconfig_clean vtestapp_clean

# ======================== Targets ======================== #
