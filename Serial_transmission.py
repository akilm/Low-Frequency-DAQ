def main():
    import serial
    import csv
    import sys
    s = serial.Serial('COM4',9600)
    x=list()
    i=0
    for i in range(500):
        high = ord(s.read(1))
        low = ord(s.read(1))
        d = high*100+low         
        x.append(d)
        ++i
        print(d)
    print("hello")
    with open("D:\data.csv", "a") as fp:
        wr = csv.writer(fp, dialect='excel')
        wr.writerow(x)
if __name__== "__main__":
    main()
