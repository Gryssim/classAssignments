10 rem
12 input x1, y
13 if x1 < y then goto 15
14 zee = x1 - y
11 goto 16
15 zee = x1 + 2 *y
16 print x1, y, zee
17 for i = 1 to 16 step 5
18 print i
19 next i
20 input st%
21 print "$", st%
22 input x
23 if y >= x1 then x = y^3
24 print x1, #
25 end