import sys

path1 = sys.argv[1]
path2 = sys.argv[2]
raw = []

with open(path1, 'rb' ) as f1:
	data1 = f1.read()

	with open(path2, 'rb' ) as f2:
		data2 = f2.read()

		for i in range(len(data1)):
			chr = data1[i] or data2[i]
#			if chr == data1[i]:
#				print( chr )

			with open('tileset.chr', 'ab' ) as f3:
				f3.write(chr.to_bytes(1,"big"))
