import time
import threading
import socket
import datetime


def str_to_hex(s):
    return ''.join([hex(ord(c)).replace('0x','') for c in s])

def function():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    host = "198.216.5.53"
    port = 6666
    ADDR = (host, port)
    s.connect(ADDR)

    data = "00370000000000000000D3060001111111111111111101002068656C6C6F776F7268656C6C6F776F7268656C6C6F776F7268656C6C6F776F72"
    hex_string = data.decode('hex')
    s.sendall(hex_string)
    data_len = s.recv(75)
    hexdata = str_to_hex(data_len)
    if data_len[10] == 'A':
        print('ok')
        pass
    else:
        f.writable('FAIL\n')
    s.close()
	
class MyThread(threading.Thread):
    def run(self):
        for i in range(10):
            function()
            #time.sleep(0.1)
            time.sleep(0.05)


def main():
    print "start main threading....."
    threads = [MyThread() for i in range(1000)]

    for t in threads:
        t.start()
    for t in threads:
        t.join()

    print "end main threading....."

if __name__=='__main__':
    f=open('11','w')
    t1=datetime.datetime.now()
    main()
    t2=datetime.datetime.now()
    print "cost time:%f" % (t2-t1).total_seconds()
    f.close()
