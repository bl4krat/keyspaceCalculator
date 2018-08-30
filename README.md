# keyspaceCalculator

(c) bl4krat 2018

A python script written to obtain some test data to solve the
following problem:

How big is the keyspace for a password:
a) Consisting of n characters, each from d possible charaters?
b) What if c identical characters in a row are prohibited? or (not and)
c) What if you can't have r of the same character anywhere?

The numbers involved rapidly become impractical to brute-force.
so for sanity, we set the following maximum values (see validate() ):

Max password length = 15, Max depth = 26

Note: The input is not fully sanitised - garbage in will cause a crash.