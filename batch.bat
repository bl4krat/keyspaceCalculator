@echo Start time: %TIME% >  timerstart.txt
keyCalc.py 4 -d26
@echo End time: %TIME% > timerend.txt
@type timerstart.txt
@type timerend.txt
@del timerstart.txt
@del timerend.txt
