#! /usr/bin/python

import sys
from optparse import OptionParser

class comm:
    def __init__ (self, filename1, filename2):
        if filename1 == '-':
            f1 = sys.stdin
            self.line1=f1.read().splitlines()
        else:
            f1 = open (filename1, 'r')
            self.line1 = f1.read().splitlines()
            f1.close()
        if filename2 =='-':
            f2 = sys.stdin
            self.line2 = f2.read().splitlines()
        else:
            f2 = open (filename2, 'r')
            self.line2 = f2.read().splitlines()
            f2.close()

        self.l1=0
        self.l2=0
class main():
    version_msg = "%v1.0"
    usage_msg = """%prog [OPTION] FILE1 FILE2."""

    parser = OptionParser(version=version_msg,usage=usage_msg)
    parser.add_option("-1",action="store_true",dest="f",
                      default=False,help="compress first line")
    parser.add_option("-2",action="store_true",dest="s",
                      default=False,help="compress second line")
    parser.add_option("-3",action="store_true",dest="t",
                      default=False,help="compress third line")
    parser.add_option("-u",action="store_true",dest="u",default=False,
                       help="treat this as unsorted file")
    options, args = parser.parse_args(sys.argv[1:])
    
    file1 = args[0]
    file2 = args[1]
    if file1 == '-' and file2 =='-':
        parser.error("only one file can be read from stdin")
   # print options.f
   # print options.s
   # print options.t
    if len(args)!=2:
        parser.error("wrong number of operands")
        
    try:
        cpr = comm(file1,file2)
        if options.u==False:
            for k in range(cpr.l1,len(cpr.line1)+1):
                   # print k
                for a in range(cpr.l2,len(cpr.line2)):
                    if k==len(cpr.line1):
                        if options.s==True:
                            break
                        elif options.f!=True:
                            sys.stdout.write('\t')
                        sys.stdout.write (cpr.line2[a]+'\n')
                        continue
                    elif cpr.line1[k] < cpr.line2[a]:
                        if options.f==False:
                            sys.stdout.write (cpr.line1[k]+'\n')
                        cpr.l1=cpr.l1+1
                        #print "executed line1"
                        break
                    elif cpr.line1[k] > cpr.line2[a]:
                        if options.s==False:
                            if options.f!=True:
                                sys.stdout.write ('\t')
                            sys.stdout.write(cpr.line2[a]+'\n')

                        cpr.l2=cpr.l2+1
                        #print"executed line2"
                        continue
                    elif cpr.line1[k] == cpr.line2[a]:
                        if options.t==False:
                            if options.f==False:
                                sys.stdout.write('\t')
                            if options.s==False:
                                sys.stdout.write('\t')
                            sys.stdout.write (cpr.line1[k]+'\n')
                        cpr.l1=cpr.l1+1
                        cpr.l2=cpr.l2+1
                        #print "executed line3"
                        break
                if cpr.l1<len(cpr.line1) and options.f==False and cpr.l2==len(cpr.line2):
                        sys.stdout.write (cpr.line1[k]+'\n')
                        cpr.l1=cpr.l1+1
                        continue
        elif options.u==True:
            for a in range(len(cpr.line1)):
                sign = False
                for k in range(len(cpr.line2)):
                
                    if cpr.line1[a].rstrip('\r\n') == cpr.line2[k].rstrip('\r\n'):
                       # print k,
                        #print cpr.line2[k]
                        sign=True
                        del cpr.line2[k]
                        break
                if sign==True:
                    sys.stdout.write ('\t\t')
                sys.stdout.write (cpr.line1[a]+'\n')
            for k in range(len(cpr.line2)):
                sys.stdout.write ( '\t'+cpr.line2[k]+'\n')
    except IOError as err:
        parser.error("I/O error{{0}}: {1}". format(error,strerror))

if __name__=="__main__":
    main()
    
            
