from pymongo import MongoClient
import urllib2
import os,commands
from compare import *

posts = MongoClient("mongodb://laikadis:iseasyrae@oceanic.mongohq.com:10025/machuca")['machuca']['post']
images_path ="images_repository/"
submitted_path = "submitted-face-pics/"
face_pics = "face-pics/"

if not os.path.exists(images_path): os.makedirs(images_path)
subpath = commands.getstatusoutput('ls '+submitted_path)[1:][0].split("\n")
print subpath
facepics  =commands.getstatusoutput('ls '+face_pics)[1:][0].split("\n")
print facepics
for i in subpath:
	for j in facepics:
		print "i = %s vs j = %s"%(i,j)
		print main(submitted_path+i,face_pics+j) < 1
		#print os.path.exists(submitted_path+i)
		#if  main(submitted_path+i, face_pics+j) < 4060585:
		#''	print "i = %s vs j = %s"%(i,j)
for post in posts.find():
	f = open(images_path+post["photo_name"],'w')
	f.write((urllib2.urlopen(post['download_link'])).read())
	f.close()


#print response.read()
#print "\n".join(img )                                                             

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
