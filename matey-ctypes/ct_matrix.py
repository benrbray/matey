# built-in
import ctypes;

# custom modules
import exceptions;
import numbers as numtypes;

################################################################################

class matrix(object):
	
	def __init__(self, arraylike):
		# flattened matrix
		numbers = [];
        
        # check if input is existing c array
        
		
		# normalize input to list of numbers from 0d, 1d, or 2d array
		if isinstance(arraylike, numtypes.Number):
			# handle scalar
			numbers = [arraylike];
			self.shape = ();
		else:
			row_dim = len(arraylike);
			col_dim = None;
			
			# inspect second dimension
			for row in arraylike:
				# check for scalar vs. list
				if isinstance(row, numtypes.Number):
					# validate column vector dimensions
					if col_dim is None:
						col_dim = 0;
					elif col_dim > 0:
						raise exceptions.InputError("Matrix dimensions don't match.", arraylike);
					# store scalar entry
					numbers.append(row);
				else:
					# validate matrix dimensions
					if col_dim is None:
						col_dim = len(row);
					elif col_dim != len(row):
						raise exceptions.InputError("Matrix dimensions don't match.", arraylike);
					# store row entries
					numbers += row;
			
			# define shape
			if col_dim: self.shape = (row_dim, col_dim);
			else:	    self.shape = (row_dim,);
			
		# allocate host memory for matrix
		self.csize = len(numbers);
		self.cptr = (ctypes.c_double * self.csize)(*numbers);
		
	#### OPERATORS #############################################################
	
	## Elementwise Operations --------------------------------------------------
	
	def __add__(self, other):
        assert isinstance(other, matrix);
	
	## Matrix Operations -------------------------------------------------------
		
	#### PRETTY PRINTING #######################################################
	
	def __str__(self):
		offset = len("matey.ct.matrix([ ");
		
		if len(self.shape) == 0:
			result = self.cptr[0];
		elif len(self.shape) == 1:
			elements = [str(x) for x in self.cptr[:]];
			result = "[ %s ]" % ", ".join(elements);
		elif len(self.shape) == 2:
			rows = [];
			for k in range(0, self.csize, self.shape[0]):
				elements = [str(x) for x in self.cptr[k:k+self.shape[0]]];
				rowstr = "[ %s ]" % ", ".join(elements);
				if k > 0: rowstr = " " * offset + rowstr;
				rows.append(rowstr);
			result = "[ %s ]" % "\n".join(rows);
		
		return "matey.ct.matrix(%s)" % result;
	
	__repr__ = __str__;
