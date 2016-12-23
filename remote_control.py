import sys
import serial

# Serial Constants
COM_PORT = '/dev/cu.usbmodem1411'
BAUD_RATE = 9600

# Protocol Constants
DATA_PACKET_SIZE = 6
GRIPPER = 0
WRIST = 1
ELBOW = 2
SHOULDER = 3
BASE = 4
STAT = 5
DATA_PACKET_NAMES = {
    GRIPPER: "gripper angle",
    WRIST: "wrist angle",
    ELBOW: "elbow angle",
    SHOULDER: "shoulder angle",
    BASE: "base angle",
    STAT: "status"
}

class RobotArmController:
    """
    Allows the user to pass coordinates to the robot arm
    """
    
    def __init__(self):
        pass
    
    def connect(self):
        try:
            self.controller = serial.Serial(COM_PORT, BAUD_RATE)
        except:
            print('Could not connect to robot arm controller')
    
    def write(self, data_packet):
        upper_base = chr((data_packet[BASE] >> 8) & 0xFF)
        lower_base = chr(data_packet[BASE] & 0xFF)
        # Debug
        print chr(data_packet[GRIPPER])
        print chr(data_packet[WRIST])
        print chr(data_packet[ELBOW])
        print chr(data_packet[SHOULDER])
        print lower_base
        print upper_base
        print chr(data_packet[STAT])
        try:
            # self.controller.write(chr(data_packet[GRIPPER]));
            # self.controller.write(chr(data_packet[WRIST]));
            # self.controller.write(chr(data_packet[ELBOW]));
            # self.controller.write(chr(data_packet[SHOULDER]));
            # self.controller.write(upper_base);
            # self.controller.write(lower_base);
            # self.controller.write(chr(data_packet[STAT]));
            pass
        except:
            print('Could not find Arduino')
            
    def get_user_input(self):
        data_packet = []
        for item in range(DATA_PACKET_SIZE):
            data_packet.append(int(input("Enter " + DATA_PACKET_NAMES[item] + ": ")))
        return data_packet
    
    #def check_data_packet(data_packet)
   
robot_arm = RobotArmController()
while True:
    data_packet = robot_arm.get_user_input()
    robot_arm.write(data_packet)
