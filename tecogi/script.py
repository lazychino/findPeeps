from pymongo import MongoClient
import urllib2
import os

posts = MongoClient("mongodb://laikadis:iseasyrae@oceanic.mongohq.com:10025/machuca")['machuca']['post']
path ="images_repository/"
if not os.path.exists(path): os.makedirs(path)

for post in posts.find():
	f = open(path+post["photo_name"],'w')
	f.write((urllib2.urlopen(post['download_link'])).read())
	f.close()
#print response.read()

#print "\n".join(img )                                                             

                                                                                                                                                                                                           
                                                                                                                                                                                                                                                                                                                                               
