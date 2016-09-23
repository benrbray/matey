from distutils.core import setup, Extension;

module = Extension("newton", 
				   sources=["newton.c"]);

setup(name = "newton", 
	  version="1.0",
	  description="Finds zeros using Newton's method.",
	  ext_modules=[module]);
