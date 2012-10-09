import os,re

def tester(test_var, excutable_var,Message,verbage):
    OK=False
    output = os.popen("make %s" % test_var)
    lines = output.readlines()
    print "\tRunning %s..." % verbage
    output = os.popen("./%s" % excutable_var)
    lines = output.readlines()
    for line in lines:
        if line==Message:
		OK=True;	

    	if OK == True:
        	print "\tPassing the test\n"
    	if OK == False:
        	print "\tFailed the test\n"
   	return OK

tests=[]
tests.append(tester('test1','/test1','Checking Errors in SetParent\n','Testing Setting SetParent in Forest'))
tests.append(tester('test2','/test2','Checking Errors if Initializing with value less than zero\n','Checking Errors if Initializing with value less than zero'))
tests.append(tester('test3','/test3','Checking Errors if SetChild set twice with same value\n','Checking Errors if SetChild set twice with same value'))

print "Passed %d of %d tests." % (tests.count(True),len(tests))

#os.system("make clean")
