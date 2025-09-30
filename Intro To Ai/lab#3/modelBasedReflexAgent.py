light_level = ['bright', 'dark']
actions = ['turn off light', 'turn on light']
memory = None  # remember last state

def modelBasedReflexAgent(current_percept):
    global memory
    if current_percept is not None:
        memory = current_percept  # take input from user/sensor and update the current percept
    elif memory is None:
        memory = 'dark'  # by default memory is set to dark if no percept 
    
    if memory == 'dark':
        return actions[1]
    else:
        return actions[0]

print("Smart Home Light System (Model-Based Reflex Agent)")
print("0: bright\n1: dark\n-1 to exit")

while True:
    user_input = input("Enter current light condition: ")
    if user_input == '-1':
        print("Exiting...")
        break
    

    if user_input == '':
        percept = None  # if no condition is given then model based agent comes to action and uses memory to asses decission
    else:
        percept = light_level[int(user_input)]
    
    action = modelBasedReflexAgent(percept)
    print("Action:", action)
    print("---")
