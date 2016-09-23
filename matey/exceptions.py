# MateyError
class MateyError(Exception):
    """Base class for `matey` exceptions."""
    
    def __init__(self, message):
        self.message = message;
    
    def __str__(self):
        return "%s: %s" % (self.__name__, message);

# InputError
class InputError(MateyError):
    """Exception raised for invalid user-provided input."""
    
    def __init__(self, expression, message):
        self.expression = expression;
        self.message = message;
    
    def __str__(self):
        return "InputError:  %s\n\t%s" % (self.expression, self.message);
