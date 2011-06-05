# BUILDING #

To build `queens`, run:

        make

This will construct the executable and ensure that runTrials.sh has the correct permissions.

# USAGE #

The default behavior will perform a hill-climbing search of the N-queens
problem and output the resultant board and the number of attacking
queens. Full usage instructions for `queens' are as below. You can also
get usage instructions by running `queens -?'.

        queens [-rcq?] [-d N]
            -r      Use random restarts to find solution
            -q      Suppress printing the board and number of
                    attacking queens
            -d N	Sets the board dimension and number of
                    queens to N (Default = 8)
            -?	    Print this usage message

Note that queens is fairly stupid in its options checking, so please
only feed it integers when using the -d option. Also note that board
sizes over ~20 tend to have rather long running times.

