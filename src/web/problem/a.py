#!python
import os,string,re
fl=os.listdir(os.getcwd())
p=re.compile('<img src=[\'\"](\d+\w*\.((gif)|(jpg)))[\'\"]',re.IGNORECASE)
print p
for fn in fl:
	if(re.search('\.htm',fn)):
		f=open(fn,'r')
		fc=f.read()
		f.close()
		f=open(fn,'w')
		fc=p.sub(r'<img src="image/\1"',fc)
		f.write(fc)
		f.close()
