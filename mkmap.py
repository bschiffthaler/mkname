from sys import argv

inf = open(argv[1], 'r')

d = {}

for line in inf.readlines():
    s = line[0].upper()
    if s in d:
        if not line.strip() in d[s]:
            d[s].append(line.strip())
    else:
        d[s] = [line.strip()]

print('std::map<char, std::vector<std::string> > ', argv[2],' = { ',sep='')

lkey = sorted(d.keys())[-1]

for k in sorted(d.keys()):
    print("{ '",k,"', { ", sep = '', end = '')
    endl = '} }\n};\n' if k == lkey else '} },\n'
    llength = 11
    for i in range(0, len(d[k])):
        llength += ( 3 + len(d[k][i]) )
        if llength > 80:
            print('\n',end='')
            llength = 11 + 3 + len(d[k][i])
        if i == len(d[k]) - 1:
            print('"',d[k][i],'"', sep='', end=endl)
        else:   
            print('"',d[k][i],'"', sep='', end=',')
