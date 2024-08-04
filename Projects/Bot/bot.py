import telebot
from telebot import types
import numpy as np
import pandas as pn

bot = telebot.TeleBot('6892429336:AAGFYqfJUJMxB7JqcNQysYbYmb-UIBYMgaQ')



@bot.message_handler(commands=['start'])
def printHelloMessage(message):
    bot.send_message(message.chat.id, '*Пожалуйста, выберите язык.\nKindly, choose your language.*'
    ,parse_mode='Markdown')
    if :
    # bot.send_message(message.chat.id, '*Добро пожаловать в EmiratesExpant!*\n Я помогу заполнить документы и избежать штраф.\n I will help you fill out the documents and avoid a fine'
    # ,parse_mode='Markdown')
    else : 
@bot.message_handler(commands=['help'])
def printHelpMessage(message):
    bot.reply_to(message, "Help try")


@bot.message_handler(func=lambda message: True)
def echo_all(message):
	bot.reply_to(message, message.text)
bot.polling(none_stop=True, interval=0)
# bot.infinity_polling()