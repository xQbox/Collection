import tkinter as tk
from tkinter import BOTH, Menu
from PIL import Image, ImageTk
import random
import os
import tkinter as tk
from tkinter import BOTH, Menu
import random
from main import *

####  TODO сделать корректный промт в нейронку (отформатировать строку по маске)
####  TODO доделать автоматическую отправку сообщения в беседу и автоматическое считывание данных из Уведомления Кирилл



class MyApp(tk.Frame):
    def __init__(self, master=None):
        super().__init__(master)
        self.master = master
        self.init_window()

        self.timer_running = False
        self.timer_seconds = 100 # CHANGEBEFORE 120
        self.timer_start_count = 0
        self.move_button_random = False
        self.count = 0
    def init_window(self):
        self.master.title("Kirill and Anastasia Wedding party")
        self.pack(fill=BOTH, expand=1)
       
        path_to_back = os.path.join('background', 'PhotoBack.jpg')  # Replace with your image file path

          # Replace with your image file path
        
        self.bg_image = Image.open(path_to_back)
        self.bg_photo = ImageTk.PhotoImage(self.bg_image)

        self.bg_label = tk.Label(self, image=self.bg_photo)
        self.bg_label.place(x=0, y=0, relwidth=1, relheight=1)

        # Create a button and bind it to the move function
        self.button1 = tk.Button(self, text="Сюрприз", command=self.button1_clicked)
        self.button1.place(x=35, y=35)
        # self.button1.bind("<Enter>", self.move_button)
        



    def move_button(self, event):
        if not self.move_button_random:
            new_x = random.randint(0, (self.master.winfo_width()) - self.button1.winfo_width())
            new_y = random.randint(0, (self.master.winfo_height()) - self.button1.winfo_height())
            self.button1.config(width=random.randint(0, 15), height=random.randint(0, 5))  # Change button size (width and height in text units)
            self.button1.place(x=new_x, y=new_y)
            
        
    def button1_clicked(self):
        
        if self.timer_start_count == 0:
        # Create a label to display the timer
            self.timer_label = tk.Label(self, text="Собираем Поздравления !: 0s", font=("Times New Roman", 24), bg="white")
            self.timer_label.place(x=10, y=10)
            
            if not self.timer_running:
                self.timer_running = True
                self.update_timer()
        else:    
            self.timer_label = tk.Label(self, text="Собираем Поздравления !: 0s", font=("Times New Roman", 24), bg="white")
            self.timer_label.place(x=10, y=10)
            
            if not self.timer_running:
                self.timer_running = True
                self.update_timer()
            print("Button second clicked!")
        

        self.move_button_random = True
        
    def client_exit(self):
        self.master.quit()


    def update_timer(self):
        if self.timer_start_count == 0:    
            if self.timer_running:
                if self.timer_seconds > 0:
                    self.timer_seconds -= 1
                    self.timer_label.config(text=f"ВНИМАНИЕ! БЕСЕДА В ТЕЛЕГРАММ: {self.timer_seconds}s")
                    self.after(100, self.update_timer)  # Schedule the next update in 1 second
                    # self.button1.destroy()
                else:
                    self.timer_running = False
                    self.timer_label.config(text="Следуйте инструкциям!")
                    # self.display_message("Мы собрали всю информацию!")
                    self.timer_start_count = 1
                    self.timer_seconds = 10 # CHANGEBEFORE 120
                    self.button1.place(x=500, y=500)
                    
                    process_wedding(root, self.count)
                    self.count += 1
        else:
            if self.timer_running:
                if self.timer_seconds > 0:
                    self.timer_seconds -= 1
                    self.timer_label.config(text=f"Завершаем собирать Поздравления: {self.timer_seconds}s")
                    self.after(1000, self.update_timer)  # Schedule the next update in 1 second
                else:
                    self.timer_running = False
                    
                    # self.timer_label.destroy()
                    self.timer_label.config(text="Поздравления собраны!")
                    # timer_label.update()
                    # sleep(3)
                    self.button1.destroy()
                    # self.timer_label.destroy()
                    # status_label = tk.Label(root, text="Начало загрузки...", padx=20, pady=20)
                    # status_label.pack()
                    process_wedding(root, self.count)

    def show_text(self):
        print("Show text")

# Create the main window
root = tk.Tk()

 
path_to_back = os.path.join('background', 'PhotoBack.jpg')  # Replace with your image file path


bg_image = Image.open(path_to_back)
width, height = bg_image.size 

root.geometry(f"{width}x{height}")  # Set the window size
root.minsize(width,height)
root.maxsize(width,height)
app = MyApp(master=root)
app.mainloop()

