# keyspaceCalculator

A python script written to obtain some test data to solve the
following problem:

How big is the keyspace for a password:
a) Consisting of l characters, each from n possible charaters?
b) What if d identical characters in a row are prohibited? or (not and)
c) What if you can't have r of the same character anywhere?

(c) bl4krat 2018

The numbers involved rapidly become impractical to brute-force.
so for sanity, we set the following maximum values (see validate() ):

Max password length = 15, Max depth = 26
