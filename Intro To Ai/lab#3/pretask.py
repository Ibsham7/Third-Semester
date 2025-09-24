percept = ['Hamza','ALi','Ahmed','Saad', 'ibsham'] 
states = ['happy','sad','angry','Normal' ,'energetic'] 
rules = ['smile','cry','shouting','Coding', 'excited']  
def getState(precept_value):
    index = -1
    for x in percept:
        index = index+1
        if x==precept_value:
            return states[index]

def getRules(state_value):
    index = -1
    for i in states:
        index = index+1
        if i==state_value:
            return rules[index]

def simpleReflexAgent(percept): return getRules(getState(percept)) 
print("Select the person")
print("0: Hamza\n","1: ALi\n", "2: Ahmad\n","3: Saad\n" , "4: Ibsham")   
num = int(input("Enter the mood"))
rule = simpleReflexAgent(percept[num]) 
print(rule) 
