import socket
import threading
import time


class globalVars():
    pass


global host
global port
global s1
global s2
global c1
global c2
global controllerSamplingTime
host = '169.254.103.134'  # change according to ur computer by running ipconfig
port1 = 12000
port2 = 10000
controllerSamplingTime = 2  # in seconds
s1 = socket.socket()
s2 = socket.socket()
g = globalVars()
g.lock = threading.Lock()
g.value = 0
g.send = 0


def con1():
    s1.bind((host, port1))
    s1.listen(2)
    print("conn1 listening")
    c1, ad1 = s1.accept()
    print(ad1)

    while True:
        # d1=c1.recv(1024)
        # print(d1.decode("utf-8")+"\n")
        # time.sleep(1)
        if g.send:
            c1.send(g.value.encode("utf-8"))
            if g.value == "out":
                # c1.send(g.value.encode("utf-8"))
                time.sleep(1)
                s1.close()
                break
            print((c1.recv(1024)).decode()+"\n")
            # print(codecs.decode((c1.recv(1024)))+"\n")
            with g.lock:
                g.send = 0


def con2():
    a = 0
    s2.bind((host, port2))
    s2.listen(2)
    print("conn2 listening")
    c2, ad2 = s2.accept()
    print(ad2)
    while True:

        if g.value == "out":
            c2.send(g.value.encode("utf-8"))
            time.sleep(1)
            s2.close()
            break
        c2.send(str(a).encode("utf-8"))
        a = a+1
        time.sleep(controllerSamplingTime)


def askinput():
    l = input()
    with g.lock:
        g.value = l
        g.send = 1
    if l == "out":
        # print(l)
        time.sleep(2)
        return 0

    return 1


t1 = threading.Thread(target=con1)
t1.daemon = True
t2 = threading.Thread(target=con2)
t2.daemon = True

t1.start()
t2.start()


while askinput():
    pass
