Cake Taker
==========

A digital conveyor of birthday cakes.

To prepare a cake taker:

    python pack_cake PASSWORD /path/to/cake.jpg

This will create a `cake_taker` executable. When given the correct password,
the `cake_taker` will write the cake back out to a file:

    ./cake_taker PASSWORD
    CORRECT!
    Writing cake to cake.jpg

If you are incorrect, it will error and exit:

    ./cake_taker not-the-password
    Incorrect password; please try again!

The cake is protected by state-of-the art encryption (XOR from a linear
congruantial generator), and is utterly impossible to extract from the
executable without the key.
