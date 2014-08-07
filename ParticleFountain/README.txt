Compiled using Visual C++ Express 2010 with OpenGL and GLUT

Main Program: ParticleFountain.cpp

Stand Alone Classes:
	Particle (particle_class.h, particle_priv.h, particle_impl.cpp)

You must install the OpenGL and GLUT libraries before you can use this code:

	http://www.opengl.org/

After this, you need to change the #include<GLUT/GLUT> and #include<OpenGL/OpenGL> so that they point to where you have
saved those libraries.  You must set 'Enable Incremental linking' to 'NO' to prevent compilation errors.