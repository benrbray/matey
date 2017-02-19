from distutils.core import setup, Extension;

# matey extension module
matey_module = Extension(
	"_matey",
	extra_compile_args=["-Wno-unused-variable"],
	sources=["src/mateymodule.c", "src/matrix.c"]
);

# distribution
setup(name="matey",
	  version="0.0",
	  description="Numerical linear algebra for pirates, aaarrggh!",
	  author="Benjamin R. Bray",
	  url="https://github.com/benrbray/matey",
	  ext_modules=[matey_module],
	  packages=["matey"]);
