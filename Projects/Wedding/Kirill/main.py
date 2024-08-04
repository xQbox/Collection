from xmlrpc.client import DateTime
from telethon.sync import TelegramClient

from telethon.tl.functions.messages import GetDialogsRequest
from telethon.tl.types import InputPeerEmpty
from telethon.tl.functions.messages import GetHistoryRequest
from telethon.tl.types import PeerChannel
from telethon import events

from PIL import Image, ImageTk

import time
import csv
import pandas as pd 
import asyncio
import tkinter as tk
import re
import os
from suno import Suno, ModelVersions

def process_wedding(root, count):
    
    api_id = 
    api_hash = ""
    phone = ""

    if count == 0:
        # Создайте клиент
        client = TelegramClient('session_name', api_id, api_hash)

        # Авторизуйтесь
        client.start()

        # Вставьте ваш ID чата или имя пользователя группы/чата
        chat_id = '@Sofia_Kriukova'

        # Отправьте сообщение
        message = 'Предлагаю каждому поучавствовать в сюрпризе! Переходите в бота и следуйте инструкция \n https://t.me/KirillWeddingBot'

        client.send_message(chat_id, message)

        print("Сообщение отправлено!")
       
        return 




##### HERE

    path_to_back = os.path.join('background', 'kiss.JPG')  # Replace with your image file path

    tmp = Image.open(path_to_back)
    tmp_photo = ImageTk.PhotoImage(tmp)

    tmp_label = tk.Label(root, image=tmp_photo)
    tmp_label.place(x=0, y=0, relwidth=1, relheight=1)
    

    status_label = tk.Label(root, text="Начало загрузки...", padx=20, pady=20)
    status_label.pack()
    status_label.update()
    
    
    time.sleep(10)


 
##### HERE   
    path_to_back = os.path.join('background', 'trip.JPG')  # Replace with your image file path

    tmp = Image.open(path_to_back)
    tmp_photo = ImageTk.PhotoImage(tmp)

    tmp_label.config(image=tmp_photo)
    tmp_label.image = tmp_photo  
    
    status_label.config(text="Форматирую данные...")
    status_label.update()

    time.sleep(10)

    client = TelegramClient(phone, api_id, api_hash)
    
    client.start()
    

    
    # # Вставьте ваш ID чата или имя пользователя группы/чата
    # chat_id = '@Sofia_Kriukova'

    # # Отправьте сообщение
    # message = 'Предлагаю каждому поучавствовать в этом сюрпризе! Заходите в бота и следуйте инструкция https://t.me/KirillWeddingBot'

    # client.send_message(chat_id, message)


    chats = []
    last_date = None
    chunk_size = 200
    groups=[]
    result = client(GetDialogsRequest(
                offset_date=last_date,
                offset_id=0,
                offset_peer=InputPeerEmpty(),
                limit=chunk_size,
                hash = 0
            ))
    chats.extend(result.chats)
    
    
    for chat in chats:
    #    try:
    #        if chat.megagroup== True:
        if chat.title == 'Уведомления от KirillWedding':
            groups.append(chat)
    #    except:
    #         print("Chat_name", chat.title)
    #         continue
    # print("Выберите группу для парсинга сообщений и членов группы:")
    # i=0
    # for g in groups:
    #     print(str(i) + "- " + g.title)
    #     i+=1

    # g_index = input("Введите нужную цифру: ")
    g_index = 0
    target_group = groups[int(g_index)]

    # print("Узнаём пользователей...")
    # all_participants = []
    # all_participants = client.get_participants(target_group)
    # print("Сохраняем данные в файл...")
    # with open("members.csv", "w", encoding="UTF-8") as f:
    #    writer = csv.writer(f,delimiter=",",lineterminator="\n")
    #    writer.writerow(["username", "name","group"])
    #    for user in all_participants:
    #        if user.username:
    #            username= user.username
    #        else:
    #            username= ""
    #        if user.first_name:
    #            first_name= user.first_name
    #        else:
    #            first_name= ""
    #        if user.last_name:
    #            last_name= user.last_name
    #        else:
    #            last_name= ""
    #        name= (first_name + ' ' + last_name).strip()
    #        writer.writerow([username,name,target_group.title])     
    # print("Парсинг участников группы успешно выполнен.")
    
    offset_id = 0
    limit = 100
    all_messages = []
    total_messages = 0
    total_count_limit = 0
    
    while True:
        history = client(GetHistoryRequest(
            peer=target_group,
            offset_id=offset_id,
            offset_date=None,
            add_offset=0,
            limit=limit,
            max_id=0,
            min_id=0,
            hash=0
        ))
        if not history.messages:
            break
        messages = history.messages
        for message in messages:
            all_messages.append(message.message)
        offset_id = messages[len(messages) - 1].id
        if total_count_limit != 0 and total_messages >= total_count_limit:
            break
    
    # print(all_messages)
    # for message in all_messages:
    #     print("Object \n", message, " type", type(message))
    #     print("Array \n", [message], " type", type(message))


    fields = ["Username", "Congratulations"]

    # data_list = "Username:Okey"
    # value, line = data_list.split(':')
    # print(line)
    parsed_data_list = []

    for message in all_messages:
        # Split the string into lines
        try:
            lines = message.split('\n')
        except AttributeError:
            print("Прочитан конец файла")
            break
        # Initialize a dictionary to store the parsed data
        parsed_data = {}
        
        # # Iterate over each line and split by the colon
        for line in lines:
            try:
                key, value = line.split(':')
            except ValueError:
                print("This is the Error line-> ", line)
            parsed_data[key] = value
        
        # # Append the parsed data to the list
        parsed_data_list.append(parsed_data)

    print("Сохраняем данные в файл...")
    with open("chats.csv", 'w', encoding="UTF-8") as csvfile:
        # Creating a csv dict writer object
        csvwriter = csv.DictWriter(csvfile, fieldnames=fields)
        
        # Writing the headers (field names)
        csvwriter.writeheader()
        
        # Writing the data rows
        csvwriter.writerows(parsed_data_list)


    print('Парсинг сообщений группы успешно выполнен.')


    df = pd.read_csv("chats.csv")
    df = df.groupby('Username')['Congratulations'].agg(lambda x: ' '.join(x)).reset_index()


    filename = 'result.txt'

    # Write the DataFrame to a text file
    df.to_csv(filename, sep=' ', index=False, header=False, quoting=csv.QUOTE_NONE, escapechar=' ')

    print(f"Data successfully written to {filename}")



##### HERE

    path_to_back = os.path.join('background', 'graduate.JPG')  # Replace with your image file path

    tmp = Image.open(path_to_back)
    tmp_photo = ImageTk.PhotoImage(tmp)
    
    tmp_label.config(image=tmp_photo)
    tmp_label.image = tmp_photo  

    status_label.config(text="Аккумулирую пожелания...")
    status_label.update()
    
    time.sleep(10)

    result_text = ''
    with open('result.txt', "r", encoding='UTF-8') as fres:
        result_text = fres.read()

    result_text = result_text.rstrip('\n')
    print(result_text)
    # Create the client and connect



    async def send_to_chat():
        # # Log in as the user
        # await client.start(phone)

        # The ID or username of the target chat or user
        target = '@GPT4Telegrambot'  # e.g., '@username' or chat ID
        mask = 'Напиши текст свадебной песни для Кирила и Анастасии Алмазовых с интро, чтобы включены были следующие слова:\n "' 
        mask_end = '"'
        message = f"{mask}{result_text}{mask_end}"
        # Send the message
        await client.send_message(target, message)

    with client:
        client.loop.run_until_complete(send_to_chat())


    async def get_from_chat():
        # await client.start(phone)
        
        # Find Anton's user ID
        sender = await client.get_entity('@GPT4Telegrambot')
        response = None
        message_received = asyncio.Event()
        @client.on(events.NewMessage(from_users=sender.id))
        async def handler(event):
            # text_from_gpt.append(event.message.message)
            nonlocal response 
            response = event.message.message
            if response != 'GPT-4o обрабатывает ваш запрос. Пожалуйста, подождите немного . . .':
                message_received.set()
            # print(f'Last message from Anton: {event.message.message}')
            

        print("Listening for new messages from Gpt...")
        await message_received.wait()
        await client.disconnect()
        return response

    with client:
        response = client.loop.run_until_complete(get_from_chat())



##### HERE
    path_to_back = os.path.join('background', 'top_N.JPG')  # Replace with your image file path

    tmp = Image.open(path_to_back)
    tmp_photo = ImageTk.PhotoImage(tmp)
    
    tmp_label.config(image=tmp_photo)
    tmp_label.image = tmp_photo  
    status_label.config(text="Генерирую текст...")
    status_label.update()
    time.sleep(15)

    def extract_text_between_first_and_last_em_dash(s):
        first_index = s.find('—')
        last_index = s.rfind('—')
        
        if first_index != -1 and last_index != -1 and first_index != last_index:
            return s[first_index + 1:last_index].strip()
        return ''


    def replace_sections(text):
        # Словарь с заменами
        replacements = {
            'Припев': '[Chorus]',
            'Куплет 1': '[Verse 1]',
            'Куплет 2': '[Verse 2]',
            'Куплет 3': '[Verse 3]',
            'Куплет 4': '[Verse 4]',
            'Куплет 5': '[Verse 5]',
            'Куплет 6': '[Verse 6]',
            'Бридж': '[Bridge]',
            'Финал': '[Outro]',
            'Интро': '[Intro]',
            'Заключение': '[Outro]'
        }
        
        # Функция замены
        def replace_match(match):
            return replacements[match.group(0)]
        
        # Регулярное выражение для поиска слов
        pattern = re.compile('|'.join(re.escape(key) for key in replacements.keys()))
        
        # Замена
        return pattern.sub(replace_match, text)


    response = extract_text_between_first_and_last_em_dash(response)
    



##### HERE


    path_to_back = os.path.join('background', 'top_K.JPG')  # Replace with your image file path

    tmp = Image.open(path_to_back)
    tmp_photo = ImageTk.PhotoImage(tmp)
    
    tmp_label.config(image=tmp_photo)
    tmp_label.image = tmp_photo  

    status_label.config(text="Накладываю голос...")
    status_label.update()
    # time.sleep(10)

    response = replace_sections(response)

    # print(response)G
    # return response
    client = Suno(
      cookie='',
      model_version=ModelVersions.CHIRP_V3_5)
    # Generate a song
    songs = client.generate(
    prompt=response,
    tags="Energetic, pop",
    title="Свадьба Кирилла и Анастасии",
    make_instrumental= False,
    is_custom=True,
    wait_audio=True
    )
    # # Download generated songs
    for song in songs:
        file_path = client.download(song=song)
        print(f"Song downloaded to: {file_path}")


##### HERE

##### CHANGEBEFORE
    path_to_back = os.path.join('background', 'together.JPG')  # Replace with your image file path

    tmp = Image.open(path_to_back)
    tmp_photo = ImageTk.PhotoImage(tmp)
    
    tmp_label.config(image=tmp_photo)
    tmp_label.image = tmp_photo  

    status_label.config(text="Записываю результат...")
    status_label.update()
    time.sleep(10)



    folder_path = 'downloads'
    i = 0
    for filename in os.listdir(folder_path):
        old_file_path = os.path.join(folder_path, filename)
       
        # Проверка, является ли это файл (а не папка)
        if os.path.isfile(old_file_path):
            new_filename = str(i) + "WeddingSong.mp3" 
            new_file_path = os.path.join(folder_path, new_filename)
            
            # Переименование файла
            os.rename(old_file_path, new_file_path)
            print(f"Файл {filename} успешно переименован в {new_filename}")
        i += 1





##### HERE

    path_to_back = os.path.join('background', 'together.JPG')  # Replace with your image file path

    tmp = Image.open(path_to_back)
    tmp_photo = ImageTk.PhotoImage(tmp)
    
    tmp_label.config(image=tmp_photo)
    tmp_label.image = tmp_photo  


    status_label.config(text="Результат получен!!!")
    status_label.update()
    