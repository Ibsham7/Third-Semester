rooms = ['living room', 'kitchen', 'bedroom']
room_status = ['clean', 'dirty', 'untidy'] 
goal = "clean all rooms"

def getRoomStatus(room_index):
    return room_status[room_index]

def goalBasedVacuum(room_index):
    status = getRoomStatus(room_index)
    if status == 'dirty' or status == 'untidy':
        room_status[room_index] = 'clean' 
        return f"{rooms[room_index]} was {status} → cleaning done!"
    else:
        return f"{rooms[room_index]} is already clean → nothing to do."

print("Robot Vacuum Cleaner (Goal-Based Agent)")
print("0: living room\n1: kitchen\n2: bedroom\n-1 to exit")

while True:
    user_input = input("Choose room to clean: ")
    if user_input == '-1':
        print("Exiting...")
        break
    
    room_index = int(user_input)
    action = goalBasedVacuum(room_index)
    print(action)
    print("---")
