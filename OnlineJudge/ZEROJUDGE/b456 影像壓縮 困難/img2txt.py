import sys
import Image
import codecs

sys.stdout = codecs.getwriter('utf8')(sys.stdout)
for infile in sys.argv[1:]:
	try:
		im = Image.open(infile)
		width = im.size[0]
		height = im.size[1]
		pix = im.load()
		print height, width
		for i in range(height):
			for j in range(width):
				print pix[j, i][0], pix[j, i][1], pix[j, i][2],
			print 
	except IOError:
		pass