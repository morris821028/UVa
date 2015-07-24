import sys
import Image
import codecs

sys.stdout = codecs.getwriter('utf8')(sys.stdout)
for infile in sys.argv[1:]:
	try:
		im = Image.open(infile)
		gray = im.convert('LA')
		width = gray.size[0]
		height = gray.size[1]
		pix = gray.load()
		print height, width
		for i in range(height):
			for j in range(width):
				print pix[j, i][0], 
			print 
	except IOError:
		pass