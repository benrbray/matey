from distutils.core import setup, Extension;

module = Extension(
	"matey",
	extra_compile_args=["-Wno-unused-variable"],
	sources=["src/mateymodule.c", "src/matrix.c"]
);

setup(name="matey",
	  version="0.0",
	  description="Numerical linear algebra for pirates, aaarrggh!",
	  ext_modules=[module]);
