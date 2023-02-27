import sys


def main(argv):
	with open(".env", 'r+') as fp:
		lines = fp.readlines()
		fp.seek(0)
		fp.truncate()
		if lines[0].__contains__("POST=") == True:
			lines[0] = "POST=" + argv + '\n'
		else:
			fp.writelines("POST=" + argv + '\n')
		for l in lines :
			fp.writelines(l)
		fp.close()

if __name__ == "__main__":
	main(sys.argv[1])