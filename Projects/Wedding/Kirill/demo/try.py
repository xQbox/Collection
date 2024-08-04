from xmlrpc.client import DateTime
from telethon.sync import TelegramClient

from telethon.tl.functions.messages import GetDialogsRequest
from telethon.tl.types import InputPeerEmpty
from telethon.tl.functions.messages import GetHistoryRequest
from telethon.tl.types import PeerChannel
from telethon import events

import csv
import pandas as pd 
import asyncio
import re 

api_id = 25321656
api_hash = "d9d42113b5293ec59ecff42b3c02f897"
phone = "+79156839136"

client = TelegramClient(phone, api_id, api_hash)

client.start()

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
    groups.append(chat)
#    except:
#         print("Chat_name", chat.title)
#         continue
print("Выберите группу для парсинга сообщений и членов группы:")
i=0
for g in groups:
    print(str(i) + "- " + g.title)
    i+=1

g_index = input("Введите нужную цифру: ")
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
    mask = 'Напиши текст свадебной песни для Кирилла и Анастасии Алмазовых, чтобы включены были следующие слова:\n "' 
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
        # print(f'Last message from Anton: {event.message.message}')
        # if response != 'GPT-4o обрабатывает ваш запрос. Пожалуйста, подождите немного . . .':    
        message_received.set()
    

    print("Listening for new messages from Gpt...")
    await message_received.wait()
    await client.disconnect()
    return response

with client:
    response = client.loop.run_until_complete(get_from_chat())


def extract_text_between_hyphens(s):
    # Находим текст между символами -
    match = re.search(r'—(.*?)—', s)
    if match:
        return match.group(1)
    else:
        return ''


print(response)

response = extract_text_between_hyphens(response)
print(response)
# return response
from suno import Suno, ModelVersions
client = Suno(
  cookie = 'ajs_anonymous_id=7514541a-543d-449c-b996-f9508619ca07; __client=eyJhbGciOiJSUzI1NiIsInR5cCI6IkpXVCJ9.eyJpZCI6ImNsaWVudF8yanBEVVdLS0RTbXNwM2toWEVJTEowWkw1TVYiLCJyb3RhdGluZ190b2tlbiI6IjltdWNocnpqaGhnMDZzNjBreXFnZmRvcnRvdTN2ZHRsN2lsZHh5b3gifQ.YVvFUe9a7WbZzsnLcYUcJnXoLjGxiEG2heyZPFRjMcs0Kp2xdTK_rICNcwN43mbcvWUcTjZrPyaJwaaxOBy4omMMKyIAceJQ0u-byoyNYb0v3zDdcvVBtoAoeL5gtv11muJTA-GBIArsthYtbqNuVqM6ynsARp3sZXEe1MOTYnSViH9NJcbvynP-3UhgudAicef37DNsVA5VZYiuq2nZ9M2kBdumSg6K9Un35UP0BPfGBvALAX0WX1SMgF6iyI5lvfZFV0--DtjcGWUVaINs6vWEHyfZ9qRap41NFMA4PNTJwtZH8ay4iMa6iRCa3dJKRfUA4eo3oZho0l1bp0_eng; __client_uat=1722075144; _cfuvid=.2evy6Jg0BkVTNmzdWTtYXEi0D2EU5TZh1OexDY4AnA-1722178155886-0.0.1.1-604800000; __cf_bm=iop0xX9aTR5k4uEbULORSlyjQ0dtovT8mkBGJ66oXnk-1722182199-1.0.1.1-TyrsXk7ylM9Wv_wu47cp4OHviraZBAyF6IOIW5hyiPvVBFb_Wjg5cmMHs6ZSO2UPg_qAoBs5JmJ_W0bo.cystg; mp_26ced217328f4737497bd6ba6641ca1c_mixpanel=%7B%22distinct_id%22%3A%20%2228498f0c-d70d-461d-aedd-addc381906bf%22%2C%22%24device_id%22%3A%20%22190ede3eef6596-09cd2c32d804ff-26001f51-1fa400-190ede3eef6596%22%2C%22%24initial_referrer%22%3A%20%22https%3A%2F%2Fjournal.tinkoff.ru%2Fhow-to-use-suno-ai%2F%22%2C%22%24initial_referring_domain%22%3A%20%22journal.tinkoff.ru%22%2C%22__mps%22%3A%20%7B%7D%2C%22__mpso%22%3A%20%7B%22%24initial_referrer%22%3A%20%22https%3A%2F%2Fjournal.tinkoff.ru%2Fhow-to-use-suno-ai%2F%22%2C%22%24initial_referring_domain%22%3A%20%22journal.tinkoff.ru%22%7D%2C%22__mpus%22%3A%20%7B%7D%2C%22__mpa%22%3A%20%7B%7D%2C%22__mpu%22%3A%20%7B%7D%2C%22__mpr%22%3A%20%5B%5D%2C%22__mpap%22%3A%20%5B%5D%2C%22%24search_engine%22%3A%20%22google%22%2C%22%24user_id%22%3A%20%2228498f0c-d70d-461d-aedd-addc381906bf%22%7D',
  model_version=ModelVersions.CHIRP_V3_5)
# Generate a song
songs = client.generate(prompt="A serene landscape", is_custom=False, wait_audio=True)

# Download generated songs
for song in songs:
    file_path = client.download(song=song)
    print(f"Song downloaded to: {file_path}")