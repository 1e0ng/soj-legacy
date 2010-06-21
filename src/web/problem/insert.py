#!python
import os,string,re
p0=re.compile('\d+(?=\.htm)',re.I)
p=re.compile('(?<=<title>)([\w\s]+)(?=</title>)',re.I)
p1=re.compile('(?<=<h1>)([\w\s]+)(?=</h1>)',re.I)
p2=re.compile('(?<=<h2>)([\w\s]+)(?=</h2>)',re.I)
fl=os.listdir(os.getcwd())
out=open('insert.sql','w')
for fn in fl:
	t0=p0.search(fn)
	if t0:
		fin=open(fn,'r')
		fc=fin.read()
		title=p.search(fc)
		if title:
			print t0.group()+"-->"+title.group()
			out.write('insert into problem (`pid`,`problemName`) values('+t0.group()+',\''+title.group()+'\');'+'\n')
		else:
			h1=p1.findall(fc)
			if len(h1)>=2:
				print '1'
				out.write('insert into problem (`pid`,`problemName`) values('+t0.group()+',\''+h1[1]+'\');'+'\n')
				continue
			if len(h1)>=1:
				print '0'
				out.write('insert into problem (`pid`,`problemName`) values('+t0.group()+',\''+h1[0]+'\');'+'\n')
			else:
				h2=p2.search(fc)
				if(h2):
					print '2'
					out.write('insert into problem (`pid`,`problemName`) values('+t0.group()+',\''+h2.group()+'\');'+'\n')
					
		fin.close()
out.close()

