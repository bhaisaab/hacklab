#!/usr/bin/env python

words = []

def checkWord(word):
  if word in words:
    return True
  return False

def checkRule(a):
  #vertical check
  for i in range(len(a)):
    w = ''
    for j in range(len(a)):
      w+= a[j][i]
    if not checkWord(w):
      return False

  #diagonal check
  for t in range(2):
    w = ''
    for i in range(len(a)):
      w+= a[i][i]
    if not checkWord(w):
      return False
    a.reverse()

  return True

def main():
  count = int(raw_input())
  for i in range(count):
    w = raw_input()
    words.append(w)

  wordgroup = {}
  counter = 0
  for i in range(count):
    for j in range(count):
      for k in range(count):
        wordgroup[counter] = [words[i], words[j], words[k]]
        counter = counter + 1

  finalList = {}
  counter = 0
  for i in range(len(wordgroup)):
    if checkRule(wordgroup[i]):
      finalList[counter] = wordgroup[i]
      counter = counter+1

  result = ''
  for i in range(len(finalList)):
    for j in range(3):
      result += finalList[i][j] + '\n'
    result += '\n'
  if result != '':
    print result[:-2],

if __name__ == "__main__":
  main()
