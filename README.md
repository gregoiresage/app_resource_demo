Pebble App Resource Demo
=================

This is a simple pebble demo that shows how to use app resource to save memory

The pebble app displays a list of persons. With the up/down button, you change the displayed person.

The poeple.json file contains a long list of persons (firstname/lastname).
This file is converted to a binary file in the wscript.
In the pebble app, we load the displayed person from the binary on demand. Only one person is loaded at a time. 
