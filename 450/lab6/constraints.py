# Artifical Intelligence 450
# Due Date: 11/22/19
# By: Andrew Virts
from z3 import *

i = input()
f = Function('f', IntSort(), IntSort())
s = z3.Solver()

committees = 1;

while i != "0 0":
    s.push()

    #Initial first and second input indicating total number of people and pairs that don't get along
    numPeople, numPairsThatDontWork = i.split(" ")

    #If there aren't any pairs that don't get along, you only need one committee
    #This statement checks if there are 0 pairs that don't get along. Returns the number of comittees
        #if this is the case
    if numPairsThatDontWork == 0:
        print(committees)

    #Splits up the pairs of people(firstPerson, secondPerson) that can't work together so we have their number
    #Checks to make sure they aren't assigned to the same committee
    for i in range(int(numPairsThatDontWork)):
        firstPerson, secondPerson = input().split(" ")
        s.add(f(firstPerson) != f(secondPerson))


    for person in range(1, int(numPeople)+1):
        s.push()

        #Checks to make sure theres not more committees than people
        for i in range(1, int(numPeople)+1):
            s.add(f(i) <= person, f(i) >= 1)

        #Checks to see if the model matches the expected output
        if s.check() == z3.sat:
            print(person)
            s.pop()
            break
        s.pop()

    s.pop()
    i = input()
