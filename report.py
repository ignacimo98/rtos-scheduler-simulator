import tkinter as tk
from alien import Alien
import struct
import sys



aliens = []
with open(sys.argv[1]+"/aliensinfo.bin", "rb") as f:

    bin_int = f.read(4)
    alien_info = []
    while bin_int != b"":
        # Do stuff with byte.
        
        alien_info.append(struct.unpack('i', bin_int))
        if len(alien_info) == 6:
          aliens.append(Alien(0, alien_info[0][0], alien_info[1][0], alien_info[2][0], alien_info[3][0], alien_info[4][0], alien_info[5][0]))
          alien_info = []
  
        bin_int = f.read(4)

    f.close()

timeline = []

with open(sys.argv[1]+"/timeline.bin", "rb") as f:

    bin_int = f.read(4)

    while bin_int != b"":
        # Do stuff with byte.
        
        timeline.append(struct.unpack('i', bin_int)[0])

        bin_int = f.read(4)

    f.close()

# alien1 = Alien(1, 0, 3, 10, 0x10, 0xff, 0x80)
# alien2 = Alien(2, 0, 2, 15, 0xff, 0x10, 0x80)
# alien3 = Alien(3, 3, 3, 18, 0x80, 0x10, 0xff)
# timeline = [2, 2, 1, 1, 3, 3, 3, 0, 0, 1, 1, 1, 0, 0, 2, 2, 0, 0, 3, 3, 3]
# aliens = [alien1, alien2, alien3]

square_side = 40
spacing_between_aliens = 40

alien_amount = len(aliens)
time_steps = len(timeline)
time_between_divisions = 3

bottom_line = {
  "y": 20 + square_side*(alien_amount+1) + spacing_between_aliens*alien_amount,
  "x_start": 20,
  "x_end": 20 + square_side*(time_steps + 2)}


base_vertical_line = {
  "x": 20,
  "y_start": 20,
  "y_end": 20 + square_side*(alien_amount + 1) + spacing_between_aliens*alien_amount}
  
window_height = min(620, base_vertical_line["y_end"] + 40)
window_width = min(920, bottom_line["x_end"]+20)

top = tk.Tk()

top.minsize(window_width, window_height)
top.resizable(width=tk.NO, height=tk.NO)
top.title("Scheduling report - " +sys.argv[2])


frame = tk.Frame(top, bg = "#FAFAFA")



canvas = tk.Canvas(frame, width=window_width-20, height=window_height-20)



  
vertical_line = base_vertical_line.copy()

canvas.create_line(bottom_line["x_start"], bottom_line["y"], bottom_line["x_end"], bottom_line["y"])
canvas.create_line(vertical_line["x"], vertical_line["y_start"], vertical_line["x"], vertical_line["y_end"])
canvas.create_text(vertical_line["x"], vertical_line["y_end"], anchor = tk.N, text="0")


for i in range(1, time_steps // time_between_divisions):
  vertical_line["x"] += square_side * time_between_divisions
  canvas.create_line(vertical_line["x"], vertical_line["y_start"], vertical_line["x"], vertical_line["y_end"], dash=(2, 2))
  canvas.create_text(vertical_line["x"], vertical_line["y_end"], anchor = tk.N, text=str(i*time_between_divisions))


for i in range(time_steps):
  if timeline[i] > 0:
    current_alien = aliens[timeline[i]-1]
    color = "#"+format(current_alien.r,'02x')+format(current_alien.g, '02x')+format(current_alien.b, "02x")
    canvas.create_rectangle(bottom_line["x_start"]+square_side*i, bottom_line["y"]-square_side, bottom_line["x_start"]+square_side*(i+1), bottom_line["y"], fill = color)

  for j in range(alien_amount):
    if aliens[j].recent_deadline(i):
      color = "#" + format(aliens[j].r, '02x') + format(aliens[j].g, '02x') + format(aliens[j].b, "02x")
      canvas.create_rectangle(base_vertical_line["x"]+square_side*i, base_vertical_line["y_start"]+square_side*j+spacing_between_aliens*j, base_vertical_line["x"]+square_side*(i+1), base_vertical_line["y_start"]+square_side*(j+1)+spacing_between_aliens*j, fill = color)


canvas.grid(row=0, column=0)

scroll_x = tk.Scrollbar(frame, orient="horizontal", command=canvas.xview)
scroll_x.grid(row=1, column=0, sticky="ew")

scroll_y = tk.Scrollbar(frame, orient="vertical", command=canvas.yview)
scroll_y.grid(row=0, column=1, sticky="ns")



canvas.configure(yscrollcommand=scroll_y.set, xscrollcommand=scroll_x.set)
canvas.configure(scrollregion=canvas.bbox("all"))
frame.pack()
top.mainloop()