import tkinter as tk
from PIL import Image, ImageTk

class AnimatedButton(tk.Button):
    def __init__(self, master, images, *args, **kwargs):
        self.images = images
        self.image_normal = ImageTk.PhotoImage(Image.open(images['normal']))
        self.image_hover = ImageTk.PhotoImage(Image.open(images['hover']))
        self.image_pressed = ImageTk.PhotoImage(Image.open(images['pressed']))
        
        super().__init__(master, image=self.image_normal, *args, **kwargs)
        
        self.bind("<Enter>", self.on_enter)
        self.bind("<Leave>", self.on_leave)
        self.bind("<ButtonPress-1>", self.on_press)
        self.bind("<ButtonRelease-1>", self.on_release)
    
    def on_enter(self, event):
        self.config(image=self.image_hover)
    
    def on_leave(self, event):
        self.config(image=self.image_normal)
    
    def on_press(self, event):
        self.config(image=self.image_pressed)
    
    def on_release(self, event):
        self.config(image=self.image_hover)

# Основное окно
root = tk.Tk()
root.title("Анимированная кнопка")

# Определяем изображения для разных состояний кнопки
images = {
    'normal': 'button_normal.png',
    'hover': 'button_hover.png',
    'pressed': 'button_pressed.png'
}

# Создаем анимированную кнопку
animated_button = AnimatedButton(root, images, command=lambda: print("Кнопка нажата!"))
animated_button.pack(pady=20)

# Запускаем главный цикл обработки событий
root.mainloop()