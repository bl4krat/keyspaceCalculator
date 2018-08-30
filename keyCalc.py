# keyspaceCalculator
#
# Written to obtain some test data to solve the
# following problem:
#
# How big is the keyspace for a password:
# a) Consisting of l characters, each from n possible charaters?
# b) What if d identical characters in a row are prohibited? or (not and)
# c) What if you can't have r of the same character anywhere?
#
# (c) bl4krat 2018
#
# The numbers involved rapidly become impractical to brute-force.
# so for sanity, we set the following maximum values (see validate() ):
#
# Max password length = 15, Max depth = 26
#
################################################################################

import sys

################################################################################
def printHelp():
		  #00000000001111111111222222222233333333334444444444555555555566666666667777777777
	print()
	print(" keyspaceCalculator")
	print(" (c) bl4krat 2018")
	print()
	print(" Written to obtain some test data to solve the following problem:")
	print()
	print(" How big is the keyspace for a password:")
	print("  a) Consisting of n (length) characters, each from d (depth) possible")
	print("     characters?")
	print("  b) What if c identical consecutive characters  are prohibited?")
	print("  c) What if you can't have r of the same character anywhere? (repeated letters)")
	print()	
	print(" Useage:")
	print(" keyCal [options] n")
	print()
	print(" Options:")
	print(" -d={value}  depth   - how many values to choose from. (default = 6)")
	print(" -c={value}  doubles - disallow passwords with any character appearing c times")
	print("                       in a row. (default = 0 = off)")
	print(" -r={value}  repeats - disallow password with any charater repeated r times.")
	print("                       (default = 0 = off)")
	print()
	print(" Note: -c1 or -d1 are both valid, but block all possible passwords.....")
	print()
	print(" Example:")
	print(" keycal 8            (character depth 26, length 8)")
	print(" keycal -d5 7        (character depth  5, length 7)")
	print(" keycal -c2 -d10 10  (character depth 10, length 10, no double characters)")

################################################################################

def printValues():
	print("n = " + str(n))
	print("d = " + str(d))
	print("c = " + str(c))
	print("r = " + str(r))
	
################################################################################

def printError(text):			# print an error message, the values, then quit()
	print("Error: " + text)
	printValues()
	print
	quit()

################################################################################

def parseCommandLine(): 	# gets (but doesnt check) the values. 
							# We could crash here if non-numerical values are typed.
	global n				# Use global variables, not local copies
	global d
	global c
	global r
	
	if len(sys.argv) == 1:	    # no parameters passsed
		printError("You must supply a length. (try --help to see useage.)")
  
	for arg in sys.argv[1:]:
		print("arg: '" + arg +"'. Expands to: '" + arg[0:2] + "', '" + arg[2:] + "'")
		print(type(arg))
		if    arg == "--help":		# print help
			printHelp()				# The printHelp() fn terminates the script
		elif arg[0:2] == "-d":		# set d(epth)
			d = eval(arg[2:])
		elif arg[0:2] == "-c":		# set c(onsecutive)
			c = eval(arg[2:])
		elif arg[0:2] == "-r":		# set r(epeats)
			r = eval(arg[2:])
		else:						# else set (le)n(gth)
			n = eval(arg)
	
	validate()						# sanity check values
  
################################################################################

def validate():				# Checks values are in range (if we got this far)
	MAX_N = 15		# Password length (required)
	MIN_N =  1

	MAX_D = 26		# characterSpace: so we only use [A...Z] (chr(65)...chr(90))
	MIN_D =  1		# (d = depth) (any value less than n will block all passwords)

	MAX_C = n		# max value is the password length (set it once we know n)
	MIN_C = 0		# Dont blacklist based on the 'double letter' rule

	MAX_R = n		# max value is the password length  (set it once we know n)
	MIN_R = 0		# Dont blacklist based on 'repeated' letters
	
	if n < MIN_N or n > MAX_N: 	# n out of range
		printError("Length must be between " + str(MIN_N) + " & " + str(MAX_N))
	if d < MIN_D or d > MAX_D:	# d out of range
		printError("Character depth must be between " + str(MIN_D) + " & " + str(MAX_D))
	if c < MIN_C or c > MAX_C:	# c out of range
		printError("Consecutive repeats must be between " + str(MIN_C) + " & " + str(MAX_C))
	if r < MIN_R or r > MAX_R:	# r out of range
		printError("Repeats must be between " + str(MIN_R) + " & " + str(MAX_R))

################################################################################

def validatePassword(c, r, password):
	length = len(password)
	
	for x in range(length):
		possibleConsecutive = True		# This could be a consecutive fail
		consecutiveCount    = 0			# how many 'same in a row' found so far
		repeatCount			= 0			# how many 'repeated characters' found
		for y in range(x, length):
			#print("Comparing: x = " + str(x) + " , y = " + str(y))
			
			if c > 0 and possibleConsecutive:		# ***check for consecutives***
				#print("Comparing: x = " + str(x) + " , y = " + str(y) + " for consecutive")
				if password[x] == password [y]:
					consecutiveCount += 1
					if consecutiveCount >= c:
						return(False, "Consecutive")	# consecutive validation check failed
				else:
					possibleConsecutive = False	#not a consecutive repeat - stop checking
					
			if r > 0:								# ***check for repeats***
				#print("Comparing: x = " + str(x) + " , y = " + str(y) + " for repeat")
				if password[x] == password [y]:
					repeatCount += 1
					if repeatCount >= r:
						return(False, "Repeat")		# repeat validation check failed
	
	return(True, "Valid")

################################################################################

def checkForPasswords(n, d, c, r, password):
	global candidateCount
	global validPasswordCount
	
	base = ord('A')
	
	if n == 0:			# nothing to add, so we validate the password here
		candidateCount += 1
		valid = True
		reason = 'No validation check'
		
		if c > 0 or r > 0 :		#then we must validate
			valid, reason = validatePassword(c, r, password)
			
		if valid:
			validPasswordCount += 1
			
		#print(password + ": " + str(valid) + " - " + reason)
											#you REALLY dont want to print each
											#possible password unless you are
											#debugging. For n=4, d=26, (456976 passwords)
											#this changes execution time from 0.4 seconds
											#to 26 seconds on a 49 row high cmd prompt
											#or 17 seconds on an 8 row high cmd prompt
											#on windows10 with a core i7-7700.
	else:
		for letter in range(d):	# recursively add the next letter
			checkForPasswords(n-1, d, c, r, password + chr(letter + base))

### Start here #################################################################

## set initial values
n = 0		# =0 >> do nothing and quit.
d = 6		# default depth (ie choose from [ABCDEF] only 
c = 0		# default consecutive repeat = off
r = 0		# default             repeat = off			

parseCommandLine()					# parse the values and then sanity check.
print("Success!!!")					# if we get here, we have validated.!!
printValues()

candidateCount = 0
validPasswordCount =0
checkForPasswords(n, d, c, r, '')

print('Number of password candidates: ' + str(candidateCount))
print('Number of valid passwords    : ' + str(validPasswordCount))
