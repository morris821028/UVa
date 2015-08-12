# by lwc
import requests
import sys
import time

session = '7CC76170FADCB537ADC8868A6E84AE89'

filename = sys.argv[1]
problemID = filename[0:4]
f = open(filename)
code = ''
for line in f:
	code += line

payload = {'action':'SubmitCode','problemid':problemID,'language':'CPP','code':code}
cookies = {'JSESSIONID':session}
r = requests.post('http://zerojudge.tw/Solution.api', cookies=cookies, params=payload)

if r.content == '{"uri":"/Submissions"}':
	print 'Submission OK'
else:
	print 'Fail to submit'
	sys.exit(0)