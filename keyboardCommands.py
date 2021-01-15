import serial, pygame, time
pygame.init()

port = "COM3"
arduino = serial.Serial(port, 9600)
lx = 0.0
ly = 0.0
rx = 0.0
ry = 0.0

def create_game():
    win = pygame.display.set_mode((500, 500))
    pygame.display.set_caption("PythonRobotArm")
    main_j = pygame.joystick.Joystick(0)
    main_j.init()
create_game()

run = True
while run:
    lx = str(main_j.get_axis(0))
    ly = str(main_j.get_axis(1))
    rx = str(main_j.get_axis(2))
    ry = str(main_j.get_axis(3))
    print("Left x: " + lx, "Left y: " + ly, "Right x: " + rx, "Right y: " + ry)
    data = f"LX{lx}LY{ly}RY{ry}"
    arduino.write(data.encode())
    # mx, my = pygame.mouse.get_pos()
    # mouse_pos = [int(mx  / (500 / 180)), int(my / (500 / 180))]
    # arduino.write(("X" + str(mouse_pos[0]) + "Y" + str(mouse_pos[1])).encode())
    # print("X" + str(mouse_pos[0]) + "Y" + str(mouse_pos[1]))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            run = False
    pygame.time.delay(15)
pygame.quit()