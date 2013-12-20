#!/usr/bin/python
import os
import subprocess

for files in os.listdir("."):
    if files.endswith(".out"):
        print "-------------------------------------------------------------------------------"
        print "Run test executable : " + files

        files = './' + files 
        args = files
#Or just:
#args = "bin/bar -c somefile.xml -d text.txt -r aString -f anotherString".split()
        popen = subprocess.Popen(args, stderr=subprocess.PIPE)
        popen.wait()
        output = popen.stderr.read()
        print output
        print "-------------------------------------------------------------------------------"
        print '\n\n'
