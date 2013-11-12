This is my implementation of the type-checking portion of a Decaf compiler.

My output will differ from the reference output in the following ways:

    * Arguments are evaluated from left to right, so errors are output from left to right
    * The entire process operates in only two passes, so other than errors reported in the first
         pass, all errors are output in order of line number.
        
