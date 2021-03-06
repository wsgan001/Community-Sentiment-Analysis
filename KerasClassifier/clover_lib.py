# -*- coding: utf-8 -*-
import csv
import codecs
import threading



def load_csv(path):
    with open(path, "rb") as f:
        return [line for line in csv.reader(f)]

def save_csv(data, path):
    with open(path, "wb") as f:
        csv.writer(f).writerows(data)


def load_csv_euc_kr(path):
    with codecs.open(path, "rb", "cp949") as f:
        return [line for line in csv.reader(f)]

def load_csv_utf(path):
    with codecs.open(path, "rb", "utf-8") as f:
        return [line for line in csv.reader(f)]


def save_csv_euc_kr(data, path):
    with codecs.open(path, "wb", 'cp949') as f:
        csv.writer(f).writerows(data)

def save_csv_utf(data, path):
    with codecs.open(path, "wb", 'utf-8') as f:
        csv.writer(f).writerows(data)

def load_list(path):
    with codecs.open(path, "r", 'utf-8') as f:
        list = f.read().splitlines()
        return list

def save_list(data, path):
    import sys
    reload(sys)
    sys.setdefaultencoding('utf-8')

    with codecs.open(path, "wb", 'utf-8') as f:
        for entry in data:
            f.write(entry+"\n")

# if contain any keyword, return the keyword. else, return null string
def contain_any(text, iterable):
    for keyword in iterable:
        if keyword in text:
            return keyword
    return ""



class CaseCounter:
    def __init__(self):
        self.dic = {}

    def add_count(self, id):
        if id in self.dic:
            count = self.dic[id]
            self.dic[id] = count + 1
        else:
            self.dic[id] = 1

    def enum_count(self):
        for key in self.dic.keys():
            print("{} : {}".format(key, self.dic[key]))


class FailCounter:
    def __init__(self):
        self.lock = threading.Lock()
        self.success = 0
        self.failure = 0

    def total(self):
        return self.success + self.failure

    def suc(self):
        self.lock.acquire()
        self.success += 1
        self.lock.release()

    def fail(self):
        self.lock.acquire()
        self.failure += 1
        self.lock.release()

    def add_fail(self, count):
        self.lock.acquire()
        self.failure += count
        self.lock.release()

    def precision(self):
        total = self.success + self.failure
        return float(self.success) / total


def flatten(z):
    return [y for x in z for y in x]


def play_process_completed():
    import playsound
    playsound.playsound("C:\work\complete.mp3")

