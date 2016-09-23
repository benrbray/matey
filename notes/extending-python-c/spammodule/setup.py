from distutils.core import setup, Extension;

module = Extension("spammodule", 
				   sources=["spammodule.c"]);

setup(name = "spammodule", 
	  version="1.0",
	  description="spam package!",
	  ext_modules=[module]);
