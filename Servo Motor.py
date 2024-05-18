import tkinter as tk
import serial
import time

# Configura el puerto serial
ser = serial.Serial('COM3', 9600)  # Cambia 'COM3' por el puerto correcto de tu Arduino

def move_right():
    ser.write(b'D')

def move_left():
    ser.write(b'I')

def set_speed():
    new_speed = int(speed_entry.get())
    if 0 <= new_speed <= 100:
        ser.write(b'V')
        time.sleep(0.1)  # Pequeña pausa para asegurarse de que Arduino lea el comando
        ser.write(f"{new_speed}".encode())

def set_angle():
    new_angle = int(angle_entry.get())
    if 0 <= new_angle <= 180:
        ser.write(b'G')
        time.sleep(0.1)
        ser.write(f"{new_angle}".encode())

# Configura la ventana principal
root = tk.Tk()
root.title("Control de Servo")

# Botones para mover a la derecha e izquierda
right_button = tk.Button(root, text="Derecha", command=move_right)
right_button.pack()

left_button = tk.Button(root, text="Izquierda", command=move_left)
left_button.pack()

# Campo de entrada y botón para la velocidad
speed_label = tk.Label(root, text="Velocidad (0-100):")
speed_label.pack()
speed_entry = tk.Entry(root)
speed_entry.pack()
speed_button = tk.Button(root, text="Establecer Velocidad", command=set_speed)
speed_button.pack()

# Campo de entrada y botón para el ángulo
angle_label = tk.Label(root, text="Ángulo (0-180):")
angle_label.pack()
angle_entry = tk.Entry(root)
angle_entry.pack()
angle_button = tk.Button(root, text="Establecer Ángulo", command=set_angle)
angle_button.pack()

root.mainloop()

# Cierra el puerto serial al salir
ser.close()