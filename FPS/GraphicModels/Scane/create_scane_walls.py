
n = int(input())
m = int(input())
xoffset = int(input())
yoffset = int(input())
print('x',xoffset)
print('z',yoffset)
print(n,m)

print('23 '+('10 '*(m-2))+'20')
for _ in range(n-2):
		print('11 '+('00 '*(m-2))+'11')
print('22 '+('10 '*(m-2))+'21')